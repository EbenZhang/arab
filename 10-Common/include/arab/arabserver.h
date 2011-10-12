/*
 * Copyright(C) kedacom, based on lichuang's work
 *
 */
#ifndef __ARAB_SERVER_H__
#define __ARAB_SERVER_H__
#include "cbb/system/kdvtype.h"
#include <map>
#include <string>
namespace zmq{
    class socket_t;
    class context_t;
}

namespace google{namespace protobuf{
    class Service;
}}

namespace Arab {
    class CRpcMethod;
    class CServer
    {
    public:
        /**
         *  @param host listening ip
         *  @param wPort listening port
         *  @param pZMQContext zmq's context, if 0, we will create it.
         *  @param io_threads threads for io loop, only available when pZMQContext==0
         */
        CServer(const std::string& host, u16 wPort,
            zmq::context_t* pZMQContext = 0,
            int io_threads = 1);

        ~CServer();

        void Start();

        void Stop();

        void RegisterService(google::protobuf::Service* pService);

        void* GetZMQContext()
        {
            return m_pZMQContext;
        }
    protected:
        void OnRPCMessage();
        void OnStopServer();
    private:
        zmq::context_t* m_pZMQContext;
        zmq::socket_t* m_pZMQSocket;
        zmq::socket_t* m_pZMQSocket4StopServer;
        typedef std::map<std::string, CRpcMethod*> RpcMethodMap;
        RpcMethodMap m_rpcMethodTable;

        bool m_zmqInitedByMe;

        std::string m_szListeningAddr;
    };
}
#endif  // __ARAB_SERVER_H__
