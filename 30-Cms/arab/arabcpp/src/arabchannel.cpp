/*
 * Copyright(C) kedacom, based on lichuang's work
 *
 */
#include <sstream>
#include <zmq.h>
#include <google/protobuf/descriptor.h>
#include "cbb/config/osconfig.h"
#include "arab/arabchannel.h"

using namespace std;
namespace Arab {
    CChannel::CChannel(const string &host, u16 wPort, void* pZMQContext)
        : m_pZMQContext(pZMQContext),
        m_pZMQSocket(0),
        m_bInitByMe(false)
    {
        if(!m_pZMQContext)
        {
            m_pZMQContext = zmq_init(1);
            m_bInitByMe = true;
        }

        m_pZMQSocket = zmq_socket(m_pZMQContext, ZMQ_REQ);
        ostringstream oss;
        oss<<"tcp://"<<host<<":"<<wPort;
        zmq_connect(m_pZMQSocket, oss.str().c_str());
    }

    CChannel::~CChannel()
    {
        Close();
    }

    void CChannel::CallMethod(const google::protobuf::MethodDescriptor* method,
        google::protobuf::RpcController* controller,
        const google::protobuf::Message* request,
        google::protobuf::Message* response,
        google::protobuf::Closure* done)
    {
        zmq_msg_t zmq_msg_;
        const std::string opcode = method->full_name();
        size_t opcode_len = opcode.length()+1;
        zmq_msg_init_size(&zmq_msg_, request->ByteSize() + opcode_len);
        memcpy(zmq_msg_data(&zmq_msg_),opcode.c_str(),opcode_len);
        request->SerializeToArray(
            (char*)zmq_msg_data(&zmq_msg_)+opcode_len,
            request->ByteSize());
        zmq_send(m_pZMQSocket, &zmq_msg_, 0);
        zmq_msg_close(&zmq_msg_);

        zmq_msg_init(&zmq_msg_);
        zmq_recv(m_pZMQSocket, &zmq_msg_, 0);
        response->ParseFromString(((char*)zmq_msg_data(&zmq_msg_)));
        zmq_msg_close(&zmq_msg_);
    }

    void CChannel::Close()
    {
        if(m_pZMQSocket)
        {
            int nZero = 0;
            zmq_setsockopt(m_pZMQSocket,ZMQ_LINGER,&nZero,sizeof(nZero));
            zmq_close(m_pZMQSocket);
            m_pZMQSocket = 0;
        }

        if(m_bInitByMe && m_pZMQContext)
        {
            zmq_term(m_pZMQContext);
            m_bInitByMe = false;
        }
        m_pZMQContext = 0;
    }
}
