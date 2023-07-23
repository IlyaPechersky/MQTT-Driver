#include <string>
#include <cstring>
#include <grpcpp/grpcpp.h>
#include "protos/myServer.grpc.pb.h"

#include<unistd.h>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using myserver::MqttServer;
using myserver::ConnectRequest;
using myserver::ConnectReply;
using myserver::DisconnectRequest;
using myserver::DisconnectReply;
using myserver::PublishRequest;
using myserver::PublishReply;
using myserver::SubscribeRequest;
using myserver::SubscribeReply;
using myserver::ShowBrokersRequest;
using myserver::ShowBrokersReply;
using myserver::ShowClientsRequest;
using myserver::ShowClientsReply;

class ClientSide {
public:
    
    ClientSide(std::shared_ptr<Channel> channel) : stub_(MqttServer::NewStub(channel)) {}

    string showBrokersRequest(string req);

    string showClientsRequest(string req);

    string connectionRequest(string adrs, string clientID);
    
    string disconnectionRequest(string adrs, string clientID);

    string subscribeRequest(string adrs, string topic, string clientID);

    string publishRequest(string adrs, string topic,string msg, string clientID);

private:

    std::unique_ptr<MqttServer::Stub> stub_;
};

