#include <stdio.h>
#include "cbb/config/osconfig.h"
#include "arab/arabserver.h"
#include "arab/types.pb.h"
#include "arab/tunnelmsgmaker.h"
#include "echo.pb.h"

using namespace Arab;
using namespace std;

class EchoServiceImpl : public echo::EchoService
{
public:
    EchoServiceImpl()
    {
    };

    virtual void Echo(::google::protobuf::RpcController* controller,
                    const ::echo::EchoRequest* request,
                    ::echo::EchoResponse* response,
                    ::google::protobuf::Closure* done)
    {
        printf("receive: %s\n", request->message().c_str());
        response->set_response("hello, this is a response from server\n");
        if (done)
        {
            done->Run();
        }
    }
    virtual void EchoTunnelMsg(::google::protobuf::RpcController* controller,
                       const ::echo::EmptyMessage* request,
                       ::Arab::TunnelMsg* response,
                       ::google::protobuf::Closure* done)
    {
        echo::EchoResponse echo_response;
        echo_response.set_response("hello, this is a tunnel response from server\n");
        Arab::TunnelMsg* pResponse = Arab::CTunnelMsgMaker::MakeMsg(echo_response);
        response->CopyFrom(*pResponse);
        delete pResponse;
        pResponse = 0;
        if (done)
        {
            done->Run();
        }
    }

};

int main(int argc, char *argv[])
{
  Arab::CServer rpc_server("127.0.0.1", 5555);
  google::protobuf::Service *service = new EchoServiceImpl();
  rpc_server.RegisterService(service);
  rpc_server.Start();
  return 0;
}
