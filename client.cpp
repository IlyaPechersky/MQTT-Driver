#include "client.h"

using namespace std;

string ClientSide::showBrokersRequest(string req) {
    ShowBrokersRequest request;
    ShowBrokersReply reply;

    request.set_req(req);

    ClientContext context;

    Status status = stub_->showBrokersRequest(&context, request, &reply);
    if (status.ok()) {
            return reply.response();
    }
    else {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        return "None";
    }
}

string ClientSide::showClientsRequest(string req) {
    ShowClientsRequest request;
    ShowClientsReply reply;

    request.set_req(req);

    ClientContext context;

    Status status = stub_->showClientsRequest(&context, request, &reply);
    if (status.ok()) {
            return reply.response();
    }
    else {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        return "None";
    }
}
    
string ClientSide::connectionRequest(string adrs, string clientID) {
    ConnectRequest request;
    DisconnectRequest disc_request;
    
    request.set_adrs(adrs);
    request.set_clientid(clientID);
    disc_request.set_adrs(adrs);
    
    ConnectReply reply;
    DisconnectReply disc_reply;
    cout<<"Connecting to broker: "+adrs+" /id: "+clientID+" ..."<<endl; 
    ClientContext context;
    ClientContext context1;

    Status status = stub_->connectionRequest(&context, request, &reply);
    
    if (status.ok()) {
        cout<<reply.response()<<endl;
        cout<<"Type exit to quit !"<<endl;
        string v;
        cin>>v;
        string response;
        while(v!="exit"){
            cin>>v;
        }
        Status status1 = stub_->disconnectionRequest(&context1, disc_request, &disc_reply);
        
        if(status1.ok()){
            return disc_reply.response();
        }
        else {
        std::cout << status1.error_code() << ": " << status1.error_message() << std::endl;
        return "None";
        }
    } else {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        return "None";
    }
}

string ClientSide::disconnectionRequest(string adrs, string clientID) {
    DisconnectRequest request;

    request.set_adrs(adrs);
    request.set_clientid(clientID);

    DisconnectReply reply;

    ClientContext context;

    Status status = stub_->disconnectionRequest(&context, request, &reply);

    if (status.ok()) {
        return reply.response();
    } else {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        return "None";
    }
}

string ClientSide::subscribeRequest(string adrs, string topic, string clientID) {
    SubscribeRequest request;

    
    request.set_adrs(adrs);
    request.set_topic(topic);
    request.set_clientid(clientID);
    

    SubscribeReply reply;

    ClientContext context;

    Status status = stub_->subscribeRequest(&context, request, &reply);

    if(status.ok()){
        return reply.response();
    } else {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        return "None";
    }
}

string ClientSide::publishRequest(string adrs, string topic,string msg, string clientID) {
    PublishRequest request;

    request.set_adrs(adrs);
    request.set_topic(topic);
    request.set_message(msg);
    request.set_clientid(clientID);
    

    PublishReply reply;

    ClientContext context;

    Status status = stub_->publishRequest(&context, request, &reply);

    if (status.ok()) {
        return reply.response();
    } else {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        return "None";
    }   
}