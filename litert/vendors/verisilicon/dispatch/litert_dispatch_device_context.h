// Copyright 2025 Vivante Corporation.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef ODML_LITERT_LITERT_VENDORS_VERISILICON_DISPATCH_LITERT_DISPATCH_DEVICE_CONTEXT_H_
#define ODML_LITERT_LITERT_VENDORS_VERISILICON_DISPATCH_LITERT_DISPATCH_DEVICE_CONTEXT_H_

#include <memory>

#include "absl/container/flat_hash_set.h"  // from @com_google_absl
#include "litert/c/litert_tensor_buffer.h"
#include "litert/cc/litert_expected.h"
#include "litert/vendors/c/litert_dispatch.h"
#include "litert/vendors/verisilicon/dispatch/viplite_adapter_api.h"

class LiteRtDispatchDeviceContextT {
 public:
  using Ptr = std::unique_ptr<LiteRtDispatchDeviceContextT>;
  struct VipliteMemoryInfo {
    vip_buffer buffer;
    size_t size;
    size_t offset;
    void* host_addr;
    vip_buffer_create_type_e create_type;
  };

  static constexpr LiteRtTensorBufferType kSupportedTensorBufferTypes[] = {
      kLiteRtTensorBufferTypeHostMemory,
#if LITERT_HAS_DMABUF_SUPPORT
      kLiteRtTensorBufferTypeDmaBuf,
#endif
  };

  ~LiteRtDispatchDeviceContextT() {
    viplite_adapter_api_.api().deinit();
  };

  static litert::Expected<Ptr> Create(
      const litert::verisilicon::VipliteAdapterApi& viplite_adapter_api,
      const litert::verisilicon::VerisiliconOptions* verisilicon_options);

  litert::Expected<LiteRtTensorBufferHandle> RegisterTensorBuffer(
      LiteRtTensorBuffer tensor_buffer);

  litert::Expected<void> UnregisterTensorBuffer(
      LiteRtTensorBufferHandle tensor_buffer_handle) {
    return viplite_memory_registry_.Unregister(tensor_buffer_handle);
  }

  litert::Expected<VipliteMemoryInfo> GetVipliteMemoryInfo(
      LiteRtTensorBufferHandle tensor_buffer_handle) {
    auto record = viplite_memory_registry_.Find(tensor_buffer_handle);
    if (!record) {
      return record.Error();
    } else {
      return VipliteMemoryInfo(**record);
    }
  }
const uint32_t& GetDeviceIndex() const {
    return device_index_;
  }
const uint32_t& GetCorendex() const {
    return core_index_;
  }

 private:
  class VipliteMemoryRegistry {
   public:
    explicit VipliteMemoryRegistry(
        const litert::verisilicon::VipliteAdapterApi& viplite_adapter_api)
        : viplite_adapter_api_(viplite_adapter_api) {}
    ~VipliteMemoryRegistry();
    LiteRtTensorBufferHandle Register(vip_buffer buffer, size_t size,
                                      size_t offset, void* host_addr, vip_buffer_create_type_e create_type);
    litert::Expected<void> Unregister(
        LiteRtTensorBufferHandle tensor_buffer_handle);
    litert::Expected<VipliteMemoryInfo*> Find(
        LiteRtTensorBufferHandle tensor_buffer_handle);
   private:
    const litert::verisilicon::VipliteAdapterApi& viplite_adapter_api_;
    std::vector<VipliteMemoryInfo> records_;
  };

  explicit LiteRtDispatchDeviceContextT(
      const litert::verisilicon::VipliteAdapterApi& viplite_adapter_api,
      const litert::verisilicon::VerisiliconOptions* verisilicon_options)
      : viplite_adapter_api_(viplite_adapter_api),
        viplite_memory_registry_(viplite_adapter_api),
        device_index_(0),
        core_index_(0) {
          uint32_t deviceCount = 0;
          std::vector<uint32_t> core_count;
          viplite_adapter_api_.api().init();
          if (auto device_index = verisilicon_options->GetDeviceIndex(); device_index) {
                device_index_ = *device_index;
              }
          if (auto core_index = verisilicon_options->GetCoreIndex(); core_index) {
                core_index_ = *core_index;
              }
          viplite_adapter_api_.api().query_hardware(VIP_QUERY_HW_PROP_DEVICE_COUNT,
                                                    sizeof(uint32_t), &deviceCount);
          if(device_index_ >= deviceCount) {
            device_index_ = 0;
          }
          core_count.resize(deviceCount);
          viplite_adapter_api_.api().query_hardware(VIP_QUERY_HW_PROP_DEVICE_COUNT,
                                                    sizeof(uint32_t) * core_count.size(), core_count.data());
          if(core_index_ >= core_count[device_index_])  {
             core_index_ = 0;
          }
        }

  const litert::verisilicon::VipliteAdapterApi& viplite_adapter_api_;
  uint32_t device_index_;
  uint32_t core_index_;
  VipliteMemoryRegistry viplite_memory_registry_;
};

#endif  // ODML_LITERT_LITERT_VENDORS_VERISILICON_DISPATCH_LITERT_DISPATCH_DEVICE_CONTEXT_H_
