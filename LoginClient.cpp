// Copyright 2015 gRPC authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ****************************
// author: wangjingyi
// data : 2020-04-14
// ****************************

#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include "loginserver.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using sintol::LoginRequest;
using sintol::LoginReply;
using sintol::LoginServer;


class LoginClient{
public:
    LoginClient(std::shared_ptr<Channel> channel)
      : stub_(LoginServer::NewStub(channel)) {}
    
    std::string Login(const std::string& username, const std::string& password)
    {
        LoginRequest loginRequest;
        LoginReply loginReply;
        loginRequest.set_username(username);
        loginRequest.set_password(password);
        ClientContext clientContext;
        Status status = stub_->Login(&clientContext, loginRequest, &loginReply);
        if (status.ok())
        {
          return loginReply.message();
        }
        else
        {
          std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
          return "RPC failed";
        }
        
    }

private:
    std::unique_ptr<LoginServer::Stub> stub_;
};

int main(int argc, char** argv)
{
  std::string target_str = "localhost:10001";
  LoginClient loginCLient(grpc::CreateChannel(
      target_str, grpc::InsecureChannelCredentials()));
  std::string username("sintol");
  std::string password("rtos1233214");
  std::string reply = loginCLient.Login(username,password);
  std::cout << "Login received: " << reply << std::endl;
  return 0;
}