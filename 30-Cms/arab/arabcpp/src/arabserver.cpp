/*
 * Copyright(C) kedacom, based on lichuang's work
 *
 */
#include <stdio.h>
#include <sstream>
#include "cbb/config/osconfig.h"

#include <google/protobuf/service.h>
#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/stubs/common.h>
#include <zmq.hpp>
#include "arab/arabserver.h"
#include "arab/types.pb.h"
using namespace std;

const char* ARAB_SERVER_STOP_SOCKET = "inproc://arabserverstop";
namespace Arab {
    class CRpcMethod
    {
    public:
        CRpcMethod(google::protobuf::Service *service,
            const google::protobuf::Message *request,
            const google::protobuf::Message *response,
            const google::protobuf::MethodDescriptor *method)
            : service_(service),
            request_(request),
            response_(response),
            method_(method)
        {
        }

        google::protobuf::Service *service_;
        const google::protobuf::Message *request_;
        const google::protobuf::Message *response_;
        const google::protobuf::MethodDescriptor *method_;
    };

    CServer::CServer(const string &host, u16 wPort,
        zmq::context_t* pZMQContext,int io_threads)
        : m_pZMQContext(pZMQContext),
        m_pZMQSocket(0),
        m_pZMQSocket4StopServer(0),
        m_zmqInitedByMe(false)
    {
        if(!m_pZMQContext)
        {
            m_pZMQContext = new zmq::context_t(io_threads);
            m_zmqInitedByMe = true;
        }

        std::ostringstream oss;
        oss<<"tcp://"<<host<<":"<<(int)wPort;
        m_szListeningAddr =  oss.str();
    }

    CServer::~CServer()
    {
        Stop();
        if (m_pZMQSocket4StopServer)
        {
            delete m_pZMQSocket4StopServer;
            m_pZMQSocket4StopServer = 0;
        }
        if (m_pZMQSocket)
        {
            m_pZMQSocket->close();
            m_pZMQSocket = 0;
        }
        if (m_zmqInitedByMe && m_pZMQContext)
        {
            zmq_term(m_pZMQContext);
            m_zmqInitedByMe = false;
        }
        m_pZMQContext = 0;

        RpcMethodMap::iterator iter = m_rpcMethodTable.begin();
        for (;iter != m_rpcMethodTable.end();++iter)
        {
            CRpcMethod *rpc_method = iter->second;
            delete rpc_method;
        }
        m_rpcMethodTable.clear();
    }

    void CServer::RegisterService(google::protobuf::Service* pService)
    {
        const google::protobuf::ServiceDescriptor *descriptor = pService->GetDescriptor();
        for (int i = 0; i < descriptor->method_count(); ++i)
        {
            const google::protobuf::MethodDescriptor *method = descriptor->method(i);
            const google::protobuf::Message *request =
                &pService->GetRequestPrototype(method);
            const google::protobuf::Message *response =
                &pService->GetResponsePrototype(method);
            CRpcMethod *rpc_method = new CRpcMethod(pService, request,
                response, method);
            m_rpcMethodTable[method->full_name()] = rpc_method;
        }
    }

    void CServer::OnRPCMessage()
    {
        zmq::message_t recvMsg;
        m_pZMQSocket->recv(&recvMsg, 0);  // 0 means no flags, block recv
        std::string rpc_name((const char*)recvMsg.data());
        RpcMethodMap::const_iterator iter = m_rpcMethodTable.find(rpc_name);
        if (iter == m_rpcMethodTable.end())
        {
            Arab::ErrResp errResp;
            Arab::ErrorCode* pErr = errResp.mutable_error();
            pErr->set_error_code(Arab::ErrorCode::NOT_IMPL);
            zmq::message_t msg4Err(errResp.ByteSize());
            errResp.SerializeToArray((char*)msg4Err.data(),errResp.ByteSize());
            m_pZMQSocket->send(msg4Err, 0);
            printf("Method NOT IMPL\n");
            return;
        }
        CRpcMethod *rpc_method = iter->second;
        const google::protobuf::MethodDescriptor *method = rpc_method->method_;
        google::protobuf::Message *request = rpc_method->request_->New();
        google::protobuf::Message *response = rpc_method->response_->New();
        request->ParseFromString((char*)recvMsg.data() + rpc_name.length() + 1);

        rpc_method->service_->CallMethod(method,
            NULL,
            request, response, NULL);

        size_t msg_len = response->ByteSize();
        zmq::message_t sendMsg(msg_len);
        response->SerializeToArray((char*)sendMsg.data(), msg_len);
        m_pZMQSocket->send(sendMsg, 0);
        delete request;
        delete response;
    }

    void CServer::Start()
    {
        m_pZMQSocket = new zmq::socket_t(*m_pZMQContext, ZMQ_REP);
        m_pZMQSocket4StopServer = new zmq::socket_t(*m_pZMQContext, ZMQ_REP);
        m_pZMQSocket->bind(m_szListeningAddr.c_str());
        m_pZMQSocket4StopServer->bind(ARAB_SERVER_STOP_SOCKET);

        zmq::pollitem_t items[] = {
                {*m_pZMQSocket,0,ZMQ_POLLIN,0},
                {*m_pZMQSocket4StopServer,0,ZMQ_POLLIN,0}
        };
        size_t lenOfItem = sizeof(items)/sizeof(items[0]);
        while (1)
        {
            zmq::poll(items,lenOfItem,-1);
            if(items[0].revents & ZMQ_POLLIN)
            {
                OnRPCMessage();
            }
            if(items[1].revents & ZMQ_POLLIN)
            {
                OnStopServer();
            }
        }
    }
    void CServer::Stop()
    {
        if(!m_pZMQSocket)
        {
            return;
        }
        zmq::socket_t socket4Stop(*m_pZMQContext,ZMQ_REQ);
        socket4Stop.connect(ARAB_SERVER_STOP_SOCKET);
        zmq::message_t msg4Send;
        socket4Stop.send(msg4Send);
        zmq::message_t msg4Recv;
        socket4Stop.recv(&msg4Recv);
    }

    void CServer::OnStopServer()
    {
        zmq::message_t msg4Recv;
        m_pZMQSocket4StopServer->recv(&msg4Recv);
        zmq::message_t msg4Send;
        m_pZMQSocket4StopServer->send(msg4Send);
    }
}
