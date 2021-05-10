#pragma once
#include <vector>
#include <string>
#include "location_monitor/Landmark.h"
#include "nav_msgs/Odometry.h"

namespace LandmarkName
{

};

class LandmarkPositions
{
public:
    LandmarkPositions() = delete;
    LandmarkPositions(std::string name, double x, double y);
    std::string m_name;
    double m_x;
    double m_y;   

private:

};

class LandmarkMonitor
{
public:
    LandmarkMonitor() = delete;
    LandmarkMonitor(const ros::Publisher& publisher);
    void odomCallBack(const nav_msgs::Odometry::ConstPtr &msg);
    location_monitor::Landmark findNearestLandmard(const nav_msgs::Odometry::ConstPtr &msg);
private:
    std::vector<LandmarkPositions> m_landmarkVector;
    ros::Publisher m_publish;
    void init();
};
