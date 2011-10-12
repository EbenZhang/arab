/*
 * Copyright(C) kedacom, based on lichuang's work
 * 
 */
#ifndef __ARAB_CHANNEL_H__
#define __ARAB_CHANNEL_H__
#include <google/protobuf/service.h>
#include <google/protobuf/message.h>
#include <cbb/system/kdvtype.h>
#include <string>

namespace Arab 
{
    class CChannel : public google::protobuf::RpcChannel 
    {
     public:
             CChannel(const std::string &host, u16 wPort,void* pZMQContext);

             virtual ~CChannel();

             virtual void CallMethod(const google::protobuf::MethodDescriptor* method,
                         google::protobuf::RpcController* controller,
                         const google::protobuf::Message* request,
                         google::protobuf::Message* response,
                         google::protobuf::Closure* done);

             void Close();

             void* GetZMQContext()
             {
                 return m_pZMQContext;
             }
    private:
             void *m_pZMQContext;
             void *m_pZMQSocket;
             bool m_bInitByMe;
    };
}
#endif  // __ZRPC_CHANNEL_H__
