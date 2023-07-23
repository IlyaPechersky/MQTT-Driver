#include <string>
#include <cstring>
#include <grpcpp/grpcpp.h>
#include "myServer.grpc.pb.h"

#include <unistd.h>

#include "client.h"
#include "server.h"

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

void RunServer() {
    std::string address("0.0.0.0:5000");
    ServerServiceImplementation service;

    ServerBuilder builder;

    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on port: " << address << std::endl;

    server->Wait();
}

void RunClient() {
    std::string address("0.0.0.0:5000");
    ClientSide client(
        grpc::CreateChannel(
            address, 
            grpc::InsecureChannelCredentials()
        )
    );
    string adrs="0.0.0.0:1883";
    string topic="test";
    string msg = "Hello Friend !";
    string client_id="client_00";

    int v;
    std::cout<<"Press 1 to connect\nPress 2 to disconnect\nPress 3 to subscribe\nPress 4 to publish\nPress 5 to show brokers connected to the server\nPress 6 to show clients using the server"<<std::endl;
    std::cin>>v;
    string response;
    switch (v)
    {
    case 1:
    {
        std::cout<<"Broker address:"<<std::endl;
        string s0;
        cin>>s0;
        std::cout<<"This device id:"<<std::endl;
        string s1;
        cin>>s1;
        response = client.connectionRequest(s0,s1);
        std::cout<< response<<std::endl;
        break;
    }
    case 2:
    {
        std::cout<<"Broker address:"<<std::endl;
        string s0;
        cin>>s0;
        std::cout<<"This device id:"<<std::endl;
        string s1;
        cin>>s1;
        response = client.disconnectionRequest(s0,s1);
        std::cout<< response<<std::endl;
        break;
    }
    case 3:
    {
        std::cout<<"Broker address:"<<std::endl;
        string s0;
        cin>>s0;
        std::cout<<"This device id:"<<std::endl;
        string s1;
        cin>>s1;
        std::cout<<"write a topic:"<<std::endl;
        string s2;
        cin>>s2;
        std::cout<<"Waiting for messages ..."<<std::endl;
        while(true){
            response = client.subscribeRequest(s0,s2,s1);
            std::cout<< response<<std::endl;
            std::cout<<"Waiting for messages ..."<<std::endl; 
        }
        break;
    }
    case 4:
    {
        std::cout<<"Broker address:"<<std::endl;
        string s0;
        cin>>s0;
        std::cout<<"This device id:"<<std::endl;
        string s1;
        cin>>s1;
        std::cout<<"Write a topic"<<std::endl;
        string s3;
        cin>>s3;
        std::cout<<"Write a message"<<std::endl;
        string s2;
        cin>>s2;
        response = client.publishRequest(s0,s3,s2,s1);
        cout<<"Publishing message ..."<<endl;
        std::cout<< response<<std::endl;
        break;
    }
    case 5:
    {
        response = client.showBrokersRequest("Anything");
        std::cout<< response<<std::endl;
        break;
    }
    case 6:
    {
        response = client.showClientsRequest("Anything");
        std::cout<< response<<std::endl;
        break;
    }
    default:
        cout<<"Not a good choice try again"<<endl;
        break;
    }
    //response = client.connectionRequest(adrs);
    //std::cout  << response << std::endl;  
}

int main(int argc, char* argv[]){
    RunClient();
    return 0;
}