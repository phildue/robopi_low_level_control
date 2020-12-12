//
// Created by phil on 22.03.20.
//

#ifndef ACTUATOR_INTERFACE_VELOCITY_H
#define ACTUATOR_INTERFACE_VELOCITY_H

#include <hardware_interface/joint_state_interface.h>
#include <hardware_interface/joint_command_interface.h>
#include <hardware_interface/robot_hw.h>
#include <joint_limits_interface/joint_limits_interface.h>
#include <joint_limits_interface/joint_limits.h>
#include <joint_limits_interface/joint_limits_urdf.h>
#include <joint_limits_interface/joint_limits_rosparam.h>
#include <controller_manager/controller_manager.h>
#include <boost/scoped_ptr.hpp>
#include <ros/ros.h>
#include <robopi_drivers/robopi_drivers.h>
#include <thread>
using namespace hardware_interface;
using joint_limits_interface::JointLimits;
using joint_limits_interface::SoftJointLimits;
using joint_limits_interface::PositionJointSoftLimitsHandle;
using joint_limits_interface::PositionJointSoftLimitsInterface;

class ActuatorInterfaceVelocity : public hardware_interface::RobotHW{
public:
    explicit ActuatorInterfaceVelocity(ros::NodeHandle& nh);
    ~ActuatorInterfaceVelocity() = default;
    void init();
    void update(const ros::TimerEvent& e);
    void read();
    void write(ros::Duration elapsed_time);

protected:
    std::map<std::string,robopi::MotorLn298> _wheels;
    std::vector<double> _jointEffort,_jointPosition,_jointVelocity;
    std::vector<double> _jointVelocityCommand;
    ros::NodeHandle _nh;
    ros::Timer _nonRealTimeLoop;
    ros::Duration control_period_;
    ros::Duration _elapsedTime;
    JointStateInterface _jointStateInterface;
    VelocityJointInterface _velocityJointInterface;
    joint_limits_interface::VelocityJointSoftLimitsInterface _velocityJointSoftLimitInterface;
    int _numJoints;
    std::vector<std::string> _wheelNames;
    double _loopHz;
    std::shared_ptr<controller_manager::ControllerManager> _ctrlManager;
    double p_error_, v_error_, e_error_;

};


#endif //ACTUATOR_INTERFACE_VELOCITY_H
