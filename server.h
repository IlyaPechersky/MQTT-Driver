#include <string>

#include <grpcpp/grpcpp.h>
#include "myServer.grpc.pb.h"

#include<unistd.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <thread>	
#include <atomic>
#include <list>
#include <chrono>
#include <cstring>
#include "mqtt/client.h"
#include "mqtt/properties.h"

vector <string> Brokers_List;
vector <string> Clients_List;
int serverState=0;

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
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


// Message table function signature
using handler_t = std::function<bool(const mqtt::message&)>;

// Handler for data messages (i.e. topic "data/#")
bool data_handler(const mqtt::message& msg);

// Handler for command messages (i.e. topic "command")
// Return false to exit the application
bool command_handler(const mqtt::message& msg);


class ServerServiceImplementation final : public MqttServer::Service {
};
