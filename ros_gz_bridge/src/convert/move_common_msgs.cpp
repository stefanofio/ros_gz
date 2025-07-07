// Copyright 2025 HIPERT SRL
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "ros_gz_bridge/convert/move_common_msgs.hpp"
#include "ros_gz_bridge/convert/std_msgs.hpp"

namespace ros_gz_bridge
{

template<>
void
convert_gz_to_ros(
  const tk::sim_msgs::CarState & gz_msg,
  move_common_msgs::msg::VehicleFeedback & ros_msg)
{
  convert_gz_to_ros(gz_msg.header(), ros_msg.header);
  ros_msg.brake = gz_msg.brake();
  ros_msg.throttle = gz_msg.throttle();
  ros_msg.steer_angle = gz_msg.steer_angle();
  ros_msg.wheel_angle = gz_msg.wheel_angle();
  ros_msg.rpm = gz_msg.rpm();
  ros_msg.gear = gz_msg.gear();
  ros_msg.gear_state = gz_msg.gear_state();
  
  // In proto3, fields are always present (no has_ methods needed)
  ros_msg.park_brake = gz_msg.park_brake();
  ros_msg.speed = gz_msg.speed();
  
  // Convert repeated field to vector
  ros_msg.wheel_speeds.clear();
  for (int i = 0; i < gz_msg.wheel_speeds_size(); ++i) {
    ros_msg.wheel_speeds.push_back(gz_msg.wheel_speeds(i));
  }
}

template<>
void
convert_ros_to_gz(
  const move_common_msgs::msg::VehicleFeedback & ros_msg,
  tk::sim_msgs::CarState & gz_msg)
{
  convert_ros_to_gz(ros_msg.header, *gz_msg.mutable_header());
  gz_msg.set_brake(ros_msg.brake);
  gz_msg.set_throttle(ros_msg.throttle);
  gz_msg.set_steer_angle(ros_msg.steer_angle);
  gz_msg.set_wheel_angle(ros_msg.wheel_angle);
  gz_msg.set_rpm(ros_msg.rpm);
  gz_msg.set_gear(ros_msg.gear);
  gz_msg.set_gear_state(ros_msg.gear_state);
  gz_msg.set_park_brake(ros_msg.park_brake);
  gz_msg.set_speed(ros_msg.speed);
  
  // Convert vector to repeated field
  gz_msg.clear_wheel_speeds();
  for (const auto& speed : ros_msg.wheel_speeds) {
    gz_msg.add_wheel_speeds(speed);
  }
}

template<>
void
convert_ros_to_gz(
  const move_common_msgs::msg::VehicleControl & ros_msg,
  tk::sim_msgs::CarControl & gz_msg)
{
  convert_ros_to_gz(ros_msg.header, *gz_msg.mutable_header());
  gz_msg.set_brake(ros_msg.brake);
  gz_msg.set_throttle(ros_msg.throttle);
  gz_msg.set_wheel_angle(ros_msg.wheel_angle);
  gz_msg.set_gear(ros_msg.gear);
  gz_msg.set_gear_state(ros_msg.gear_state);
  gz_msg.set_park_brake(ros_msg.park_brake);
}

template<>
void
convert_gz_to_ros(
  const tk::sim_msgs::CarControl & gz_msg,
  move_common_msgs::msg::VehicleControl & ros_msg)
{
  convert_gz_to_ros(gz_msg.header(), ros_msg.header);
  ros_msg.brake = gz_msg.brake();
  ros_msg.throttle = gz_msg.throttle();
  ros_msg.wheel_angle = gz_msg.wheel_angle();
  ros_msg.gear = gz_msg.gear();
  ros_msg.gear_state = gz_msg.gear_state();
  ros_msg.park_brake = gz_msg.park_brake();
}

}  // namespace ros_gz_bridge
