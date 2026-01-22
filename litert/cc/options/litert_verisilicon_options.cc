// Copyright 2025 Google LLC.
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
#include "litert/cc/options/litert_verisilicon_options.h"

#include <memory>
#include <string>

#include "absl/strings/string_view.h"  // from @com_google_absl
#include "litert/c/litert_common.h"
#include "litert/c/litert_opaque_options.h"
#include "litert/c/options/litert_verisilicon_options.h"
#include "litert/cc/internal/litert_detail.h"
#include "litert/cc/internal/litert_handle.h"
#include "litert/cc/litert_expected.h"
#include "litert/cc/litert_macros.h"
#include "litert/cc/litert_opaque_options.h"

// C++ WRAPPERS ////////////////////////////////////////////////////////////////
namespace litert::verisilicon {
const char* VerisiliconOptions::Discriminator() {
  return LiteRtVerisiliconOptionsGetIdentifier();
}
Expected<VerisiliconOptions> VerisiliconOptions::Create(OpaqueOptions& options) {
  const auto id = options.GetIdentifier();
  if (!id || *id != Discriminator()) {
    return Error(kLiteRtStatusErrorInvalidArgument);
  }
  return VerisiliconOptions(options.Get(), OwnHandle::kNo);
}
Expected<VerisiliconOptions> VerisiliconOptions::Create() {
  LiteRtOpaqueOptions options;
  LITERT_RETURN_IF_ERROR(LiteRtVerisiliconOptionsCreate(&options));
  return VerisiliconOptions(options, OwnHandle::kYes);
}

Expected<LiteRtVerisiliconOptions> VerisiliconOptions::Data() const {
  LiteRtVerisiliconOptions options_data;
 LITERT_RETURN_IF_ERROR(LiteRtVerisiliconOptionsGet(Get(), &options_data));
  return options_data;
}

Expected<void> VerisiliconOptions::SetDeviceIndex(
   uint32_t device_index) {
  LiteRtVerisiliconOptions options_data;
  LITERT_RETURN_IF_ERROR(
      LiteRtVerisiliconOptionsGet(Get(), &options_data));
  LITERT_RETURN_IF_ERROR(
      LiteRtVerisiliconOptionsSetDeviceIndex(options_data, device_index));
  return {};
}

Expected<uint32_t>
VerisiliconOptions::GetDeviceIndex() const {
  LiteRtVerisiliconOptions options_data;
  LITERT_RETURN_IF_ERROR(
      LiteRtVerisiliconOptionsGet(Get(), &options_data));
  uint32_t device_index = 0;
  LITERT_RETURN_IF_ERROR(
      LiteRtVerisiliconOptionsGetDeviceIndex(options_data, &device_index));
  return device_index;
}

Expected<void> VerisiliconOptions::SetCoreIndex(
   uint32_t core_index) {
  LiteRtVerisiliconOptions options_data;
  LITERT_RETURN_IF_ERROR(
      LiteRtVerisiliconOptionsGet(Get(), &options_data));
  LITERT_RETURN_IF_ERROR(
      LiteRtVerisiliconOptionsSetCoreIndex(options_data, core_index));
  return {};
}

Expected<uint32_t>
VerisiliconOptions::GetCoreIndex() const{
  uint32_t core_index = 0;;
  LiteRtVerisiliconOptions options_data;
  LITERT_RETURN_IF_ERROR(
      LiteRtVerisiliconOptionsGet(Get(), &options_data));
  LITERT_RETURN_IF_ERROR(
      LiteRtVerisiliconOptionsGetCoreIndex(options_data, &core_index));
  return core_index;
}


Expected<void> VerisiliconOptions::SetVivanteSDKDir(const std::string& viv_sdk_dir) {
  LiteRtVerisiliconOptions options_data;
  LITERT_RETURN_IF_ERROR(
      LiteRtVerisiliconOptionsGet(Get(), &options_data));
  LITERT_RETURN_IF_ERROR(
      LiteRtVerisiliconOptionsSetVivanteSDKDir(options_data, viv_sdk_dir.c_str()));
  return {};
}

Expected<absl::string_view> VerisiliconOptions::GetVivanteSDKDir() const{
  const char* viv_sdk_dir;
  LiteRtVerisiliconOptions options_data;
  LITERT_RETURN_IF_ERROR(
      LiteRtVerisiliconOptionsGet(Get(), &options_data));
  LITERT_RETURN_IF_ERROR(
    LiteRtVerisiliconOptionsGetVivanteSDKDir(options_data,&viv_sdk_dir));
  return absl::string_view(viv_sdk_dir);
}

}  // namespace litert::verisilicon
