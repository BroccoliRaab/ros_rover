#include <stdio>
#include <stdint>
#include <cmath>

#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <std_msgs/Float64.h>

void send_command_to_arduino(double, double);

void twist_callback(const geometry_msgs::Twist&);

int main( int argc, char** argv ){
    ros::init(argc, argv, "motor_base");
    ros::NodeHandle node_handle;
    ros::Subscriber twist_subscriber = node_handle.subscribe("cmd_vel", 10, twist_callback);
}

void twist_callback( const geometry_msgs::Twist& twist_msg ){
    std_msgs::Float64 linear_v = twist_msg->linear.x;
    std_msgs::Float64 angular_v = twist_msg->angular.z;

    double left_analog_speed;
    double right_analog_speed;
    
    double track =0.3; //needs to be determined by measuring the physical robot. Will be obtained from the udrf. In m. 
    double max_speed = .5; //max speed of the robot in m/s. Will be obtained fom the udrf
    double left_wheel_v = linear_v - (track*angular_v)/2;
    double right_wheel_v = linear_v +i (track*angular_v)/2;

    left_analog_speed = 255*(left_wheel_v/max_speed);
    right_analog_speed = 255*(right_wheel_v/max_speed);

    send_command_to_arduino(left_analog_speed,right_analog_speed);
    
}
void send_command_to_arduino(double left_analog_speed, double right_analog_speed){
    //construct serial packet
    char forward_byte = 0; 
    char left_speed_byte;
    char right_speed_byte;
    char packet[3];
    if (left_analog_speed>0){
        left_forward = 1;
    }
    if (right_analog_speed>0){
        forward_byte += 2;
    }
    left_speed_byte= (char) abs(left_analog_speed);
    right_speed_byte= (char) abs(right_analog_speed);
    packet = {forward_byte,left_speed_byte,right_speed_byte};

    //send serialpacket
    //TODO
}

