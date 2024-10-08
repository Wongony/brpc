// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#ifndef BRPC_RPC_PB_MESSAGE_FACTORY_H
#define BRPC_RPC_PB_MESSAGE_FACTORY_H

#include <google/protobuf/service.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>

namespace brpc {

// Inherit this class to customize rpc protobuf messages,
// include request and response.
class RpcPBMessages {
public:
    virtual ~RpcPBMessages() = default;
    virtual google::protobuf::Message* Request() = 0;
    virtual google::protobuf::Message* Response() = 0;
};

// Factory to manage `RpcPBMessages'.
class RpcPBMessageFactory {
public:
    virtual ~RpcPBMessageFactory() = default;
    virtual RpcPBMessages* Get(const ::google::protobuf::Service& service,
                               const ::google::protobuf::MethodDescriptor& method) = 0;
    virtual void Return(RpcPBMessages* protobuf_message) = 0;
};

class DefaultRpcPBMessageFactory : public RpcPBMessageFactory {
public:
    RpcPBMessages* Get(const ::google::protobuf::Service& service,
                       const ::google::protobuf::MethodDescriptor& method) override;
    void Return(RpcPBMessages* messages) override;
};

} // namespace brpc

#endif //BRPC_RPC_PB_MESSAGE_FACTORY_H
