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
#include "litert/c/options/litert_verisicon_options.h"

#include <cstdint>

#include <gtest/gtest.h>
#include "litert/c/litert_common.h"
#include "litert/c/litert_opaque_options.h"
#include "litert/cc/options/litert_verisilicon_options.h"
#include "litert/test/matchers.h"

namespace litert::verisilicon {
namespace {
TEST(LiteRtVersiliconOptionsTest, CreateAndGet) {
  LiteRtOpaqueOptions options;
  LITERT_ASSERT_OK(LiteRtVersiliconOptionsCreate(&options));
  LiteRtVersiliconOptions options_data;
  LITERT_ASSERT_OK(LiteRtVersiliconOptionsGet(options, &options_data));
  LiteRtDestroyOpaqueOptions(options);
}

TEST(LiteRtVersiliconOptionsTest, DeviceIndex) {
  LiteRtOpaqueOptions options;
  LITERT_ASSERT_OK(LiteRtVersiliconOptionsCreate(&options));
  LiteRtVersiliconOptions options_data;
  LITERT_ASSERT_OK(LiteRtVersiliconOptionsGet(options, &options_data));

  unsigned int  device_index;
  LITERT_ASSERT_OK(LiteRtVersiliconOptionsGetDeviceIndex(
      options_data, &device_index));
  ASSERT_EQ(device_index,0);

  LITERT_ASSERT_OK(LiteRtVersiliconOptionsSetDeviceIndex(
      options_data, 0));
  LITERT_ASSERT_OK(LiteRtVersiliconOptionsGetDeviceIndex(
      options_data, &device_index));
  ASSERT_EQ(device_index,0);

  LiteRtDestroyOpaqueOptions(options);
}

TEST(LiteRtVersiliconOptionsTest, CoreIndex) {
  LiteRtOpaqueOptions options;
  LITERT_ASSERT_OK(LiteRtVersiliconOptionsCreate(&options));
  LiteRtVersiliconOptions options_data;
  LITERT_ASSERT_OK(LiteRtVersiliconOptionsGet(options, &options_data));

  unsigned int  core_index;
  LITERT_ASSERT_OK(LiteRtVersiliconOptionsGetCoreIndex(
      options_data, &core_index));
  ASSERT_EQ(core_index,0);

  LITERT_ASSERT_OK(LiteRtVersiliconOptionsSetCoreIndex(
      options_data, 0));
  LITERT_ASSERT_OK(LiteRtVersiliconOptionsGetCoreIndex(
      options_data, &core_index));
  ASSERT_EQ(core_index,0);

  LiteRtDestroyOpaqueOptions(options);
}

}  // namespace
}  // namespace litert::verisilicon
