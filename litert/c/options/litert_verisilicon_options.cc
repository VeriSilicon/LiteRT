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
#include "litert/c/options/litert_verisilicon_options.h"

#include <cstdint>
#include <memory>
#include <string>

#include "absl/strings/string_view.h"  // from @com_google_absl
#include "litert/c/litert_common.h"
#include "litert/c/litert_opaque_options.h"
#include "litert/cc/litert_macros.h"
#include "litert/core/cache/hash_util.h"

struct LiteRtVerisiliconOptionsT {
  uint32_t device_index = 0;
  uint32_t core_index = 0;
  std::string viv_sdk_dir;
};

LiteRtStatus LiteRtVerisiliconOptionsCreate(LiteRtOpaqueOptions* options) {
  if (options == nullptr) {
    return kLiteRtStatusErrorInvalidArgument;
  }

  auto options_data = std::make_unique<LiteRtVerisiliconOptionsT>();

  LITERT_RETURN_IF_ERROR(LiteRtCreateOpaqueOptions(
      LiteRtVerisiliconOptionsGetIdentifier(), options_data.get(),
      [](void* payload) {
        delete reinterpret_cast<LiteRtVerisiliconOptions>(payload);
      },
      options));

  auto vsi_hash = [](const void* payload) -> uint64_t {
    const LiteRtVerisiliconOptionsT* options =
        reinterpret_cast<const LiteRtVerisiliconOptionsT*>(payload);
    uint64_t ans = 0;
    litert::HashCombine(
        ans, options->device_index, options->core_index);
    return ans;
  };
  LITERT_RETURN_IF_ERROR(LiteRtSetOpaqueOptionsHash(*options, vsi_hash));

  options_data.release();
  return kLiteRtStatusOk;
}
const char* LiteRtVerisiliconOptionsGetIdentifier() { return "verisilicon"; }

LiteRtStatus LiteRtVerisiliconOptionsGet(LiteRtOpaqueOptions options,
                                      LiteRtVerisiliconOptions* options_data) {
  if (options_data == nullptr || options == nullptr) {
    return kLiteRtStatusErrorInvalidArgument;
  }
  const char* identifier;
  LITERT_RETURN_IF_ERROR(
      LiteRtGetOpaqueOptionsIdentifier(options, &identifier));
  if (absl::NullSafeStringView(identifier) !=
      LiteRtVerisiliconOptionsGetIdentifier()) {
    return kLiteRtStatusErrorInvalidArgument;
  }
  void* payload;
  LITERT_RETURN_IF_ERROR(LiteRtGetOpaqueOptionsData(options, &payload));
  *options_data = reinterpret_cast<LiteRtVerisiliconOptionsT*>(payload);
  return kLiteRtStatusOk;
}
// device index ----------------------------------------------------------
LiteRtStatus LiteRtVerisiliconOptionsSetDeviceIndex(
    LiteRtVerisiliconOptions options,
    uint32_t  device_index) {
  if (options == nullptr) {
    return kLiteRtStatusErrorInvalidArgument;
  }
  options->device_index = device_index;
  return kLiteRtStatusOk;
}

LiteRtStatus LiteRtVerisiliconOptionsGetDeviceIndex(
    LiteRtVerisiliconOptions options,
    uint32_t* device_index) {
  if (options == nullptr || device_index == nullptr) {
    return kLiteRtStatusErrorInvalidArgument;
  }
  *device_index = options->device_index;
  return kLiteRtStatusOk;
}

// core index ----------------------------------------------------------
LiteRtStatus LiteRtVerisiliconOptionsSetCoreIndex(
    LiteRtVerisiliconOptions options,
    uint32_t  device_index) {
  if (options == nullptr) {
    return kLiteRtStatusErrorInvalidArgument;
  }
  options->device_index = device_index;
  return kLiteRtStatusOk;
}

LiteRtStatus LiteRtVerisiliconOptionsGetCoreIndex(
    LiteRtVerisiliconOptions options,
    uint32_t* device_index) {
  if (options == nullptr || device_index == nullptr) {
    return kLiteRtStatusErrorInvalidArgument;
  }
  *device_index = options->device_index;
  return kLiteRtStatusOk;
}

// viv_sdk_dir ---------------------------------------------
LiteRtStatus LiteRtVerisiliconOptionsSetVivanteSDKDir(
    LiteRtVerisiliconOptions options,  const char* viv_sdk_dir) {
  if (options == nullptr) {
    return kLiteRtStatusErrorInvalidArgument;
  }

  options->viv_sdk_dir = viv_sdk_dir;

  return kLiteRtStatusOk;
}

LiteRtStatus LiteRtVerisiliconOptionsGetVivanteSDKDir(
    LiteRtVerisiliconOptions options, const char** viv_sdk_dir) {
  if (options == nullptr || viv_sdk_dir == nullptr) {
    return kLiteRtStatusErrorInvalidArgument;
  }

  *viv_sdk_dir = options->viv_sdk_dir.c_str();

  return kLiteRtStatusOk;
}
