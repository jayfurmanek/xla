/* Copyright 2023 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef XLA_SERVICE_PROFILE_GUIDED_LATENCY_ESTIMATOR_H_
#define XLA_SERVICE_PROFILE_GUIDED_LATENCY_ESTIMATOR_H_

#include <memory>
#include <string>
#include <utility>

#include "absl/container/flat_hash_map.h"
#include "xla/service/latency_hiding_scheduler.h"
#include "xla/xla.pb.h"

namespace xla {

// Implementation of LatencyEstimator using a profile to estimate HLO cost and
// latencies between instructions. If a cost is not known, it will forward to
// an underlying model-based estimator.
class ProfileGuidedLatencyEstimator : public LatencyEstimator {
 public:
  TimeCost GetLatencyBetween(const HloGraphNode& from,
                             const HloGraphNode& target) const override;
  TimeCost NodeCost(const HloInstruction* instr) const override;
  int CyclesPerMicrosecond() const override;

  ProfileGuidedLatencyEstimator(
      const SchedulerConfig& config,
      std::unique_ptr<LatencyEstimator> latency_estimator,
      const ProfiledInstructionsProto& proto);

 private:
  const SchedulerConfig config_;
  std::unique_ptr<LatencyEstimator> latency_estimator_;
  // Maps HLO instruction name to timestamp and duration.
  absl::flat_hash_map<std::string, std::pair<TimeCost, TimeCost>> instr_map_;
};

}  // namespace xla

#endif  // XLA_SERVICE_PROFILE_GUIDED_LATENCY_ESTIMATOR_H_
