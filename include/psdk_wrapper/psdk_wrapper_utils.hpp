/*
 * Copyright (C) 2023 Unmanned Life
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

/**
 * @file psdk_wrapper_utils.hpp
 *
 * @brief Header file containing utility functions and constants
 *
 * @authors Bianca Bendris
 * Contact: bianca@unmanned.life
 *
 */
#ifndef PSDK_WRAPPER_INCLUDE_PSDK_WRAPPER_PSDK_WRAPPER_UTILS_HPP_
#define PSDK_WRAPPER_INCLUDE_PSDK_WRAPPER_PSDK_WRAPPER_UTILS_HPP_

#include <dji_fc_subscription.h>
#include <dji_flight_controller.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <tf2/LinearMath/Quaternion.h>

#include <map>
#include <string>
#include <vector>
#define IMU_TOPIC_MAX_FREQ 400
#define ATTITUDE_TOPICS_MAX_FREQ 100
#define ACCELERATION_TOPICS_MAX_FREQ 200
#define VELOCITY_TOPICS_MAX_FREQ 50
#define ANGULAR_VELOCITY_TOPICS_MAX_FREQ 200
#define POSITION_TOPICS_MAX_FREQ 50
#define ALTITUDE_TOPICS_MAX_FREQ 50
#define GPS_FUSED_POSITION_TOPICS_MAX_FREQ 50
#define GPS_DATA_TOPICS_MAX_FREQ 5
#define RTK_DATA_TOPICS_MAX_FREQ 5
#define MAGNETOMETER_TOPICS_MAX_FREQ 100
#define RC_CHANNELS_TOPICS_MAX_FREQ 50
#define GIMBAL_DATA_TOPICS_MAX_FREQ 50
#define FLIGHT_STATUS_TOPICS_MAX_FREQ 50
#define BATTERY_STATUS_TOPICS_MAX_FREQ 50
#define CONTROL_DATA_TOPICS_MAX_FREQ 50
#define ESC_DATA_TOPICS_FREQ 50

#define GOOD_GPS_SIGNAL_LEVEL 5

namespace psdk_ros2
{
namespace psdk_utils
{

struct DJITopic
{
  E_DjiFcSubscriptionTopic label;
  int max_frequency;
};

enum DisplayMode
{
  DISPLAY_MODE_MANUAL_CTRL = 0,
  DISPLAY_MODE_ATTITUDE = 1,
  DISPLAY_MODE_P_GPS = 6,
  DISPLAY_MODE_HOTPOINT_MODE = 9,
  DISPLAY_MODE_ASSISTED_TAKEOFF = 10,
  DISPLAY_MODE_AUTO_TAKEOFF = 11,
  DISPLAY_MODE_AUTO_LANDING = 12,
  DISPLAY_MODE_NAVI_GO_HOME = 15,
  DISPLAY_MODE_NAVI_SDK_CTRL = 17,
  DISPLAY_MODE_FORCE_AUTO_LANDING = 33,
  DISPLAY_MODE_SEARCH_MODE = 40,
  DISPLAY_MODE_ENGINE_START = 41
};

enum GPSFixState
{
  GPS_FIX_STATE_NO_FIX = 0,
  GPS_FIX_STATE_DEAD_RECKONING_ONLY = 1,
  GPS_FIX_STATE_2D_FIX = 2,
  GPS_FIX_STATE_3D_FIX = 3,
  GPS_FIX_STATE_GPS_PLUS_DEAD_RECKONING = 4,
  GPS_FIX_STATE_TIME_ONLY_FIX = 5
};

enum RTKSolutionState
{
  RTK_SOLUTION_STATE_NOT_AVAILABLE = 0,
  RTK_SOLUTION_STATE_FIX_POSITION = 1,
  RTK_SOLUTION_STATE_FIX_HEIGHT_AUTO = 2,
  RTK_SOLUTION_STATE_INSTANTANEOUS_DOPPLER_COMPUTE_VELOCITY = 8,
  RTK_SOLUTION_STATE_SINGLE_PNT_SOLUTION = 16,
  RTK_SOLUTION_STATE_PSEUDORANGE_DIFFERENTIAL_SOLUTION = 17,
  RTK_SOLUTION_STATE_SBAS_CORRECTION_CALCULATED = 18,
  RTK_SOLUTION_STATE_KALMAN_FILTER_WITHOUT_OBSERVATION_PROPAGATED = 19,
  RTK_SOLUTION_STATE_OMNISTAR_VBS_POSITION = 20,
  RTK_SOLUTION_STATE_FLOAT_L1_AMBIGUITY = 32,
  RTK_SOLUTION_STATE_FLOAT_IONOSPHERIC_FREE_AMBIGUITY = 33,
  RTK_SOLUTION_STATE_FLOAT_SOLUTION = 34,
  RTK_SOLUTION_STATE_L1_AMBIGUITY_INT = 48,
  RTK_SOLUTION_STATE_WIDE_LANE_AMBIGUITY_INT = 49,
  RTK_SOLUTION_STATE_NARROW_INT = 50,
};

enum FlightStatus
{
  FLIGHT_STATUS_STOPED = 0, /* Aircraft is on ground and motors are still. */
  FLIGHT_STATUS_ON_GROUND =
      1,                   /* Aircraft is on ground but motors are rotating. */
  FLIGHT_STATUS_IN_AIR = 2 /* Aircraft is in air. */
};

/**
 * @todo (Bianca) Implement the remaining/ commented DJI topics
 */
const std::vector<DJITopic> topics_to_subscribe{
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_HARD_SYNC, IMU_TOPIC_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_QUATERNION, ATTITUDE_TOPICS_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_ACCELERATION_GROUND,
             ACCELERATION_TOPICS_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_ACCELERATION_BODY,
             ACCELERATION_TOPICS_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_ACCELERATION_RAW,
             ACCELERATION_TOPICS_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_VELOCITY, VELOCITY_TOPICS_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_ANGULAR_RATE_FUSIONED,
             ANGULAR_VELOCITY_TOPICS_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_ANGULAR_RATE_RAW,
             ANGULAR_VELOCITY_TOPICS_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_POSITION_VO, POSITION_TOPICS_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_ALTITUDE_FUSED,
             ALTITUDE_TOPICS_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_ALTITUDE_BAROMETER,
             ALTITUDE_TOPICS_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_POSITION_FUSED,
             GPS_FUSED_POSITION_TOPICS_MAX_FREQ},
    // DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_GPS_DATE, GPS_DATA_TOPICS_MAX_FREQ},
    // DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_GPS_TIME, GPS_DATA_TOPICS_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_GPS_POSITION, GPS_DATA_TOPICS_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_GPS_VELOCITY, GPS_DATA_TOPICS_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_GPS_DETAILS, GPS_DATA_TOPICS_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_GPS_SIGNAL_LEVEL,
             GPS_DATA_TOPICS_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_GPS_CONTROL_LEVEL,
             GPS_DATA_TOPICS_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_RTK_POSITION, RTK_DATA_TOPICS_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_RTK_VELOCITY, RTK_DATA_TOPICS_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_RTK_YAW, RTK_DATA_TOPICS_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_RTK_POSITION_INFO,
             RTK_DATA_TOPICS_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_RTK_YAW_INFO, RTK_DATA_TOPICS_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_RTK_CONNECT_STATUS,
             RTK_DATA_TOPICS_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_COMPASS, MAGNETOMETER_TOPICS_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_RC, RC_CHANNELS_TOPICS_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_RC_WITH_FLAG_DATA,
             RC_CHANNELS_TOPICS_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_GIMBAL_ANGLES,
             GIMBAL_DATA_TOPICS_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_GIMBAL_STATUS,
             GIMBAL_DATA_TOPICS_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_STATUS_FLIGHT,
             FLIGHT_STATUS_TOPICS_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_STATUS_DISPLAYMODE,
             FLIGHT_STATUS_TOPICS_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_STATUS_LANDINGGEAR,
             FLIGHT_STATUS_TOPICS_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_STATUS_MOTOR_START_ERROR,
             FLIGHT_STATUS_TOPICS_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_FLIGHT_ANOMALY,
             FLIGHT_STATUS_TOPICS_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_BATTERY_INFO,
             BATTERY_STATUS_TOPICS_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_BATTERY_SINGLE_INFO_INDEX1,
             BATTERY_STATUS_TOPICS_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_BATTERY_SINGLE_INFO_INDEX2,
             BATTERY_STATUS_TOPICS_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_HEIGHT_FUSION,
             CONTROL_DATA_TOPICS_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_CONTROL_DEVICE,
             CONTROL_DATA_TOPICS_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_HOME_POINT_INFO,
             CONTROL_DATA_TOPICS_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_HOME_POINT_SET_STATUS,
             CONTROL_DATA_TOPICS_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_AVOID_DATA,
             CONTROL_DATA_TOPICS_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_ALTITUDE_OF_HOMEPOINT,
             CONTROL_DATA_TOPICS_MAX_FREQ},
    DJITopic{DJI_FC_SUBSCRIPTION_TOPIC_ESC_DATA, ESC_DATA_TOPICS_FREQ}};

const std::map<E_DjiCameraType, std::string> camera_type_str = {
    {DJI_CAMERA_TYPE_UNKNOWN, "Unkown"},
    {DJI_CAMERA_TYPE_Z30, "Zenmuse Z30"},
    {DJI_CAMERA_TYPE_XT2, "Zenmuse XT2"},
    {DJI_CAMERA_TYPE_PSDK, "Payload Camera"},
    {DJI_CAMERA_TYPE_XTS, "Zenmuse XTS"},
    {DJI_CAMERA_TYPE_H20, "Zenmuse H20"},
    {DJI_CAMERA_TYPE_H20T, "Zenmuse H20T"},
    {DJI_CAMERA_TYPE_P1, "Zenmuse P1"},
    {DJI_CAMERA_TYPE_L1, "Zenmuse L1"},
    {DJI_CAMERA_TYPE_H20N, "Zenmuse H20N"},
    {DJI_CAMERA_TYPE_M30, "M30 Camera"},
    {DJI_CAMERA_TYPE_M30T, "M30T Camera"},
    {DJI_CAMERA_TYPE_M3E, "M3E Camera"},
    {DJI_CAMERA_TYPE_M3T, "M3T Camera"},
};

const std::map<E_DjiLiveViewCameraSource, std::string> camera_source_str = {
    {DJI_LIVEVIEW_CAMERA_SOURCE_DEFAULT, "default_optical_link"},
    {DJI_LIVEVIEW_CAMERA_SOURCE_H20_WIDE, "h20_wide_optical_link"},
    {DJI_LIVEVIEW_CAMERA_SOURCE_H20_ZOOM, "h20_zoom_optical_link"},
    {DJI_LIVEVIEW_CAMERA_SOURCE_H20T_WIDE, "h20t_wide_optical_link"},
    {DJI_LIVEVIEW_CAMERA_SOURCE_H20T_ZOOM, "h20t_zoom_optical_link"},
    {DJI_LIVEVIEW_CAMERA_SOURCE_H20T_IR, "h20t_ir_optical_link"},
    {DJI_LIVEVIEW_CAMERA_SOURCE_H20N_WIDE, "h20n_wide_optical_link"},
    {DJI_LIVEVIEW_CAMERA_SOURCE_H20N_ZOOM, "h20n_zoom_optical_link"},
    {DJI_LIVEVIEW_CAMERA_SOURCE_H20N_IR, "h20n_ir_optical_link"},
    {DJI_LIVEVIEW_CAMERA_SOURCE_M30_ZOOM, "m30_zoom_optical_link"},
    {DJI_LIVEVIEW_CAMERA_SOURCE_M30_WIDE, "m30_wide_optical_link"},
    {DJI_LIVEVIEW_CAMERA_SOURCE_M30T_ZOOM, "m30t_zoom_optical_link"},
    {DJI_LIVEVIEW_CAMERA_SOURCE_M30T_WIDE, "m30t_wide_optical_link"},
    {DJI_LIVEVIEW_CAMERA_SOURCE_M30T_IR, "m30t_ir_optical_link"},
    {DJI_LIVEVIEW_CAMERA_SOURCE_M3E_VIS, "m3e_vis_optical_link"},
    {DJI_LIVEVIEW_CAMERA_SOURCE_M3T_VIS, "m3t_vis_optical_link"},
    {DJI_LIVEVIEW_CAMERA_SOURCE_M3T_IR, "m3t_ir_optical_link"},
};

const tf2::Matrix3x3 R_NED2ENU{0, 1, 0, 1, 0, 0, 0, 0, -1};
const tf2::Matrix3x3 R_FLU2FRD{1, 0, 0, 0, -1, 0, 0, 0, -1};
const tf2::Quaternion Q_FLU2OPTIC{-0.500000, 0.500000, -0.500000, 0.500000};
const float C_GRAVITY_CONSTANT = 9.8;
const float C_PI = 3.141592653589793;
const float SHIFT_N2E = 1.571;

// Transforms
// @todo Add transforms for other aircraft/payloads
const tf2::Vector3 T_M300_BASE_GIMBAL{0.1262, 0.0, -0.146};
const tf2::Vector3 T_M300_GIMBAL_H20{0.0466, 0.0, -0.1037};
const tf2::Vector3 T_H20_ZOOM{0.0, 0.0, 0.0};
const tf2::Vector3 T_H20_WIDE{0.0, -0.0187, -0.0244};
const tf2::Quaternion Q_NO_ROTATION{0.0, 0.0, 0.0, 1.0};
double inline rad_to_deg(const double radians)
{
  return (radians * 180) / C_PI;
};

double inline deg_to_rad(const double degrees)
{
  return (degrees * C_PI) / 180;
};
};  // namespace psdk_utils
}  // namespace psdk_ros2

#endif  // PSDK_WRAPPER_INCLUDE_PSDK_WRAPPER_PSDK_WRAPPER_UTILS_HPP_
