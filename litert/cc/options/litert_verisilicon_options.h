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
#ifndef THIRD_PARTY_ODML_LITERT_LITERT_CC_OPTIONS_LITERT_VERISILICON_OPTIONS_H_
#define THIRD_PARTY_ODML_LITERT_LITERT_CC_OPTIONS_LITERT_VERISILICON_OPTIONS_H_

#include <string>
#include "absl/strings/string_view.h"  // from @com_google_absl
#include "litert/c/litert_common.h"
#include "litert/c/litert_opaque_options.h"
#include "litert/c/options/litert_verisilicon_options.h"
#include "litert/cc/litert_expected.h"
#include "litert/cc/litert_opaque_options.h"

namespace litert::verisilicon {

// Wraps a LiteRtVerisiliconOptions object for convenience.
class VerisiliconOptions : public OpaqueOptions {
 public:
  using OpaqueOptions::OpaqueOptions;

  VerisiliconOptions() = delete;

  static const char* Discriminator();

  static Expected<VerisiliconOptions> Create(OpaqueOptions& options);

  static Expected<VerisiliconOptions> Create();


  Expected<void> SetDeviceIndex(uint32_t device_index);
  Expected<uint32_t> GetDeviceIndex() const;

  Expected<void> SetCoreIndex(uint32_t core_index);
  Expected<uint32_t> GetCoreIndex() const;

  Expected<void> SetVivanteSDKDir(const std::string& viv_sdk_dir);

  Expected<absl::string_view> GetVivanteSDKDir() const;

 private:
  Expected<LiteRtVerisiliconOptions> Data() const;
};

}  // namespace litert::verisilicon

#endif  // THIRD_PARTY_ODML_LITERT_LITERT_CC_OPTIONS_LITERT_VERISILICON_OPTIONS_H_
