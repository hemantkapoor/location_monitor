#include "ros/ros.h"
#include "location_monitor/Landmark.h"
#include "LandmarkMonitor.h"

LandmarkPositions::LandmarkPositions(std::string name, double x, double y): m_name(name), m_x(x), m_y(y)
{}

LandmarkMonitor::LandmarkMonitor(const ros::Publisher& publisher) : m_landmarkVector(), 
m_publish(publisher)
{
    init();
}

void LandmarkMonitor::init()
{
    m_landmarkVector.push_back(LandmarkPositions("Block1",0.6,0.6));
    m_landmarkVector.push_back(LandmarkPositions("Block2",0.6,-0.6));
    m_landmarkVector.push_back(LandmarkPositions("Block3",-0.6,-0.6));
    m_landmarkVector.push_back(LandmarkPositions("Block4",-0.6,0.6));
}

void LandmarkMonitor::odomCallBack(const nav_msgs::Odometry::ConstPtr &msg)
{
    //ROS_INFO("Current x = %f,y = %f", msg->pose.pose.position.x, msg->pose.pose.position.y);
    auto near = findNearestLandmard(msg);
    m_publish.publish(near);
}

location_monitor::Landmark LandmarkMonitor::findNearestLandmard(const nav_msgs::Odometry::ConstPtr &msg)
{
    location_monitor::Landmark landmark;
    landmark.distance = -1;
    for(auto element : m_landmarkVector)
    {
        auto currDistX = msg->pose.pose.position.x - element.m_x;
        auto currDistY = msg->pose.pose.position.y - element.m_y;
        auto currentDistance = sqrt( (currDistX*currDistX) + (currDistY * currDistY));
        if(landmark.distance == -1 | currentDistance < landmark.distance)
        {
            landmark.distance = currentDistance;
            landmark.landMark = element.m_name;
        }
    }
    
    if(landmark.distance <= 0.3)
    {
        ROS_INFO("Nearest Location is %s and distance is %f",landmark.landMark.c_str(), landmark.distance);
    }
    return landmark;
}