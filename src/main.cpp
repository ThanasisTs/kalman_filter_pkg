#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/PointStamped.h>
#include <keypoint_3d_matching_msgs/Keypoint3d_list.h>

#include <vector>
#include <string>
#include <cmath>

#include <kalman_filter/KalmanFilterObj.h>

ros::Subscriber sub;

template <typename T>
void subscriber_definition(ros::NodeHandle& n, std::string& keypoint_topic, KalmanFilterObj<T>& kf_obj){
	sub = n.subscribe(keypoint_topic, 1, &KalmanFilterObj<T>::KalmanFilterCallback, &kf_obj);
}

int main(int argc, char** argv){

	ros::init(argc, argv, "kalmanFilter");

	ros::NodeHandle nh;

	std::string keypoint_topic;
	int freq;
	bool online;

	nh.param("kalmanFilter/keypoint_topic", keypoint_topic, std::string("/raw_points_online"));
	nh.param("kalmanFilter/frequency", freq, 30);
	nh.param("kalmanFilter/online", online, false);


	ROS_INFO("keypoint topic: %s", keypoint_topic.c_str());

	KalmanFilterObj<keypoint_3d_matching_msgs::Keypoint3d_list> kf_obj(freq, online);
	subscriber_definition(nh, keypoint_topic, kf_obj);

	ros::spin();

	return 0;
}
