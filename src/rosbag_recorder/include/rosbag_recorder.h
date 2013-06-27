#ifndef ROSBAG_RECORDER_H
#define ROSBAG_RECORDER_H

#include <ros/ros.h>
#include <rosbag/bag.h>
#include <tf/transform_listener.h>
#include <tf/tfMessage.h>
#include <string>

class RosbagRecorder {
	public:
		RosbagRecorder();
		void record(void);
		//void stop(void);
		
	private:
		const std::string currentDateTime(void);
		void recordRaw(void);
		void recordRotations(void);
		void recordCallback(const tf::tfMessage::ConstPtr& msg);
		
		ros::NodeHandle n;
		tf::TransformListener listener;
		ros::Rate rate;
		rosbag::Bag *raw_bag;
		rosbag::Bag *rotations_bag;
};

#endif
