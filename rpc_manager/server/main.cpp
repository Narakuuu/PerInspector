#include <iostream>
#include <grpc/grpc.h>
#include <grpcpp/server_builder.h>
#include "rpc_manager.h"

// accept all ip address , 50051 port
constexpr char kServerPortInfo[] = "0.0.0.0:50051";
void InitServer() {
  grpc::ServerBuilder builder;

  // listen
  builder.AddListeningPort(kServerPortInfo, grpc::InsecureServerCredentials());

  // create grpc_server
  monitor::GrpcManagerImpl grpc_server;
  // register
  builder.RegisterService(&grpc_server);

  // start
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  // block
  server->Wait();

  return;
}

int main() {
  InitServer();
  return 0;
}