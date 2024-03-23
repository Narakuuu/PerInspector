#include "rpc_client.h"

namespace monitor {
// initial
RpcClient::RpcClient() {
  // create channel, no encryption
  auto channel = grpc::CreateChannel("localhost:50051",
                                     grpc::InsecureChannelCredentials());

  // creat stub && stub_ptr -> stub obj                     
  stub_ptr_ = monitor::proto::GrpcManager::NewStub(channel);
}
RpcClient::~RpcClient() {}

// client send data to server
void RpcClient::SetMonitorInfo(const monitor::proto::MonitorInfo& monito_info) {
  // create gRPC client context obj
  ::grpc::ClientContext context;
  // reponse data null
  ::google::protobuf::Empty response;
  // send data no response
  ::grpc::Status status =
      stub_ptr_->SetMonitorInfo(&context, monito_info, &response);
  if (status.ok()) {
  } else {
    std::cout << status.error_details() << std::endl;
    std::cout << "falied to connect !!!" << std::endl;
  }
}


// client receive data from server
void RpcClient::GetMonitorInfo(monitor::proto::MonitorInfo* monito_info) {
  ::grpc::ClientContext context;
  // send data null
  ::google::protobuf::Empty request;

  // get data 
  ::grpc::Status status =
      stub_ptr_->GetMonitorInfo(&context, request, monito_info);
  if (status.ok()) {
  } else {
    std::cout << status.error_details() << std::endl;
    std::cout << "falied to connect !!!" << std::endl;
  }
}
}  // namespace monitor
