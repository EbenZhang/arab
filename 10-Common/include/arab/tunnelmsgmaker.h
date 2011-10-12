#ifndef _TUNNEL_MSG_MAKER_H_
#define _TUNNEL_MSG_MAKER_H_

#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
namespace Arab{
    class CTunnelMsgMaker
    {
    public:
        static TunnelMsg* MakeMsg(google::protobuf::Message& org_msg)
        {
            TunnelMsg* pTunnel = new TunnelMsg;
            pTunnel->set_message_type(org_msg.GetDescriptor()->full_name());
            std::string buff;
            org_msg.SerializeToString(&buff);
            pTunnel->set_message_content(buff);
            return pTunnel;
        }
    };
}


#endif

//end of file


