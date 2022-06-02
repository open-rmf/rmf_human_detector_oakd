/*
 * Copyright (C) 2022 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#ifndef SRC__HUMANDETECTOR_HPP
#define SRC__HUMANDETECTOR_HPP

#include <rmf_obstacle_ros2/Detector.hpp>

namespace rmf_human_detector_oakd {
//==============================================================================
class OakDHumanDetector : public rmf_obstacle_ros2::Detector
{
public:
  using Obstacles = rmf_obstacle_ros2::Detector::Obstacles;
  using DetectorCallback = rmf_obstacle_ros2::Detector::DetectorCallback;

  /// Documentation inherited
  void initialize(
    const rclcpp::Node& node,
    DetectorCallback cb) final;

  /// Documentation inherited
  std::string name() const final;

private:
  DetectorCallback _cb;
  std::string _name = "rmf_human_detector_oakd";

};

} // namespace rmf_human_detector_oakd

#endif // SRC__HUMANDETECTOR_HPP