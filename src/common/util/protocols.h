/** Copyright 2020 Alibaba Group Holding Limited.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef SRC_COMMON_UTIL_PROTOCOLS_H_
#define SRC_COMMON_UTIL_PROTOCOLS_H_

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "common/memory/payload.h"
#include "common/util/boost.h"
#include "common/util/status.h"
#include "common/util/uuid.h"

namespace vineyard {

enum class CommandType {
  NullCommand = 0,
  ExitRequest = 1,
  ExitReply = 2,
  RegisterRequest = 3,
  RegisterReply = 4,
  GetDataRequest = 5,
  GetDataReply = 6,
  PersistRequest = 8,
  ExistsRequest = 9,
  DelDataRequest = 10,
  ClusterMetaRequest = 11,
  ListDataRequest = 12,
  CreateBufferRequest = 13,
  GetBuffersRequest = 14,
  CreateDataRequest = 15,
  PutNameRequest = 16,
  GetNameRequest = 17,
  DropNameRequest = 18,
  CreateStreamRequest = 19,
  GetNextStreamChunkRequest = 20,
  PullNextStreamChunkRequest = 21,
  StopStreamRequest = 22,
  IfPersistRequest = 25,
  InstanceStatusRequest = 26,
  ShallowCopyRequest = 27,
};

CommandType ParseCommandType(const std::string& str_type);

void WriteErrorReply(Status const& status, std::string& msg);

void WriteRegisterRequest(std::string& msg);

Status ReadRegisterRequest(const ptree& msg);

void WriteRegisterReply(const std::string& ipc_socket,
                        const std::string& rpc_endpoint,
                        const InstanceID instance_id, std::string& msg);

Status ReadRegisterReply(const ptree& msg, std::string& ipc_socket,
                         std::string& rpc_endpoint, InstanceID& instance_id);

void WriteExitRequest(std::string& msg);

void WriteGetDataRequest(const ObjectID id, const bool sync_remote,
                         const bool wait, std::string& msg);

void WriteGetDataRequest(const std::vector<ObjectID>& ids,
                         const bool sync_remote, const bool wait,
                         std::string& msg);

Status ReadGetDataRequest(const ptree& root, std::vector<ObjectID>& ids,
                          bool& sync_remote, bool& wait);

void WriteGetDataReply(const ptree& content, std::string& msg);

Status ReadGetDataReply(const ptree& root, ptree& content);

Status ReadGetDataReply(const ptree& root,
                        std::unordered_map<ObjectID, ptree>& content);

void WriteListDataRequest(std::string const& pattern, bool const regex,
                          size_t const limit, std::string& msg);

Status ReadListDataRequest(const ptree& root, std::string& pattern, bool& regex,
                           size_t& limit);

void WriteCreateDataRequest(const ptree& content, std::string& msg);

Status ReadCreateDataRequest(const ptree& root, ptree& content);

void WriteCreateDataReply(const ObjectID& id, const InstanceID& instance_id,
                          std::string& msg);

Status ReadCreateDataReply(const ptree& root, ObjectID& id,
                           InstanceID& instance_id);

void WritePersistRequest(const ObjectID id, std::string& msg);

Status ReadPersistRequest(const ptree& root, ObjectID& id);

void WritePersistReply(std::string& msg);

Status ReadPersistReply(const ptree& root);

void WriteIfPersistRequest(const ObjectID id, std::string& msg);

Status ReadIfPersistRequest(const ptree& root, ObjectID& id);

void WriteIfPersistReply(bool exists, std::string& msg);

Status ReadIfPersistReply(const ptree& root, bool& persist);

void WriteExistsRequest(const ObjectID id, std::string& msg);

Status ReadExistsRequest(const ptree& root, ObjectID& id);

void WriteExistsReply(bool exists, std::string& msg);

Status ReadExistsReply(const ptree& root, bool& exists);

void WriteDelDataRequest(const ObjectID id, const bool force, const bool deep,
                         std::string& msg);

void WriteDelDataRequest(const std::vector<ObjectID>& id, const bool force,
                         const bool deep, std::string& msg);

Status ReadDelDataRequest(const ptree& root, std::vector<ObjectID>& id,
                          bool& force, bool& deep);

void WriteDelDataReply(std::string& msg);

Status ReadDelDataReply(const ptree& root);

void WriteClusterMetaRequest(std::string& msg);

Status ReadClusterMetaRequest(const ptree& root);

void WriteClusterMetaReply(const ptree& content, std::string& msg);

Status ReadClusterMetaReply(const ptree& root, ptree& content);

void WriteInstanceStatusRequest(std::string& msg);

Status ReadInstanceStatusRequest(const ptree& root);

void WriteInstanceStatusReply(const ptree& content, std::string& msg);

Status ReadInstanceStatusReply(const ptree& root, ptree& content);

void WriteCreateBufferRequest(const size_t size, std::string& msg);

Status ReadCreateBufferRequest(const ptree& root, size_t& size);

void WriteCreateBufferReply(const ObjectID id,
                            const std::shared_ptr<Payload>& object,
                            std::string& msg);

Status ReadCreateBufferReply(const ptree& root, ObjectID& id, Payload& object);

void WriteGetBuffersRequest(const std::unordered_set<ObjectID>& ids,
                            std::string& msg);

Status ReadGetBuffersRequest(const ptree& root, std::vector<ObjectID>& ids);

void WriteGetBuffersReply(const std::vector<std::shared_ptr<Payload>>& objects,
                          std::string& msg);

Status ReadGetBuffersReply(const ptree& root,
                           std::unordered_map<ObjectID, Payload>& objects);

void WritePutNameRequest(const ObjectID object_id, const std::string& name,
                         std::string& msg);

Status ReadPutNameRequest(const ptree& root, ObjectID& object_id,
                          std::string& name);

void WritePutNameReply(std::string& msg);

Status ReadPutNameReply(const ptree& root);

void WriteGetNameRequest(const std::string& name, const bool wait,
                         std::string& msg);

Status ReadGetNameRequest(const ptree& root, std::string& name, bool& wait);

void WriteGetNameReply(const ObjectID& object_id, std::string& msg);

Status ReadGetNameReply(const ptree& root, ObjectID& object_id);

void WriteDropNameRequest(const std::string& name, std::string& msg);

Status ReadDropNameRequest(const ptree& root, std::string& name);

void WriteDropNameReply(std::string& msg);

Status ReadDropNameReply(const ptree& root);

void WriteCreateStreamRequest(const ObjectID& object_id, std::string& msg);

Status ReadCreateStreamRequest(const ptree& root, ObjectID& object_id);

void WriteCreateStreamReply(std::string& msg);

Status ReadCreateStreamReply(const ptree& root);

void WriteGetNextStreamChunkRequest(const ObjectID stream_id, const size_t size,
                                    std::string& msg);

Status ReadGetNextStreamChunkRequest(const ptree& root, ObjectID& stream_id,
                                     size_t& size);

void WriteGetNextStreamChunkReply(std::shared_ptr<Payload>& object,
                                  std::string& msg);

Status ReadGetNextStreamChunkReply(const ptree& root, Payload& object);

void WritePullNextStreamChunkRequest(const ObjectID stream_id,
                                     std::string& msg);

Status ReadPullNextStreamChunkRequest(const ptree& root, ObjectID& stream_id);

void WritePullNextStreamChunkReply(std::shared_ptr<Payload>& object,
                                   std::string& msg);

Status ReadPullNextStreamChunkReply(const ptree& root, Payload& object);

void WriteStopStreamRequest(const ObjectID stream_id, const bool failed,
                            std::string& msg);

Status ReadStopStreamRequest(const ptree& root, ObjectID& stream_id,
                             bool& failed);

void WriteStopStreamReply(std::string& msg);

Status ReadStopStreamReply(const ptree& root);

void WriteShallowCopyRequest(const ObjectID id, std::string& msg);

Status ReadShallowCopyRequest(const ptree& root, ObjectID& id);

void WriteShallowCopyReply(const ObjectID target_id, std::string& msg);

Status ReadShallowCopyReply(const ptree& root, ObjectID& target_id);

}  // namespace vineyard

#endif  // SRC_COMMON_UTIL_PROTOCOLS_H_
