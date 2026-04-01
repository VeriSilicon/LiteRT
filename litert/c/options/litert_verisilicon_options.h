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
#ifndef THIRD_PARTY_ODML_LITERT_LITERT_C_OPTIONS_LITERT_VERISILICON_OPTIONS_H_
#define THIRD_PARTY_ODML_LITERT_LITERT_C_OPTIONS_LITERT_VERISILICON_OPTIONS_H_
#include "litert/c/litert_common.h"
#include "litert/c/litert_opaque_options.h"

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

// Create a verisilicon options object that is type erased. The actual option
// data can be accessed from the payload.
LiteRtStatus LiteRtVerisiliconOptionsCreate(LiteRtOpaqueOptions* options);
LITERT_DEFINE_HANDLE(LiteRtVerisiliconOptions);

// The a string identifier that discriminates Verisilicon options within
// type erased options.
const char* LiteRtVerisiliconOptionsGetIdentifier();

// Attempt to retrieve Verisilicon options from the opaque options. Fails
// unless the opaque options are of another type.
LiteRtStatus LiteRtVerisiliconOptionsGet(LiteRtOpaqueOptions options,
                                      LiteRtVerisiliconOptions* options_data);

// COMPILATION OPTIONS /////////////////////////////////////////////////////////


// viplite_adapter_options --------------------------------------------
LiteRtStatus LiteRtVerisiliconOptionsSetDeviceIndex(
    LiteRtVerisiliconOptions options,
    unsigned int device_index);

LiteRtStatus LiteRtVerisiliconOptionsGetDeviceIndex(
    LiteRtVerisiliconOptions options,
    unsigned int* device_index);

LiteRtStatus LiteRtVerisiliconOptionsSetCoreIndex(
    LiteRtVerisiliconOptions options,
    unsigned int core_index);

LiteRtStatus LiteRtVerisiliconOptionsGetCoreIndex(
    LiteRtVerisiliconOptions options,
    unsigned int* core_index);

LiteRtStatus LiteRtVerisiliconOptionsSetVivanteSDKDir(
    LiteRtVerisiliconOptions options,
    const char* viv_sdk_dir);

LiteRtStatus LiteRtVerisiliconOptionsGetVivanteSDKDir(
    LiteRtVerisiliconOptions options,
    const char** viv_sdk_dir);

#ifdef __cplusplus

}  // extern "C"

#endif  // __cplusplus
#endif  // THIRD_PARTY_ODML_LITERT_LITERT_C_OPTIONS_LITERT_VERISILICON_OPTIONS_H_
