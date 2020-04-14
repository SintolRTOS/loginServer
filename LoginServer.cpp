
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

#include "include/LoginServer.h"

Status LoginServiceImp::Login(::grpc::ServerContext* context, const ::sintol::LoginRequest* request, ::sintol::LoginReply* response)
{
    if(NULL != msg_handle)
    {
        msg_handle->disPatch(context,request,response);
    }
    return Status::OK;
}

LoginServiceImp::LoginServiceImp()
{
    msg_handle = new MsgHandle();
}

LoginServiceImp::~LoginServiceImp()
{
    if (NULL != msg_handle)
    {
        delete msg_handle;
        msg_handle = NULL;
    }
}