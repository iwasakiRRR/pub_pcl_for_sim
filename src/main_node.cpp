#include <iostream>
#include <math.h>
#include <ros/ros.h>
#include <sensor_msgs/Image.h>

//PCL
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

class Hoge{
 public:
  ros::NodeHandle nh;
  ros::Publisher pub;
  Hoge();
  void HogeCallBack(const sensor_msgs::PointCloud2::ConstPtr& _msg);
 private:
  ros::Subscriber sub;
};

Hoge::Hoge(){
  pub = nh.advertise<sensor_msgs::PointCloud2>("/pcl_for_sim",10);
  sub = nh.subscribe<sensor_msgs::PointCloud2>("/camera/depth_registered/points",5,&Hoge::HogeCallBack,this);
}
void Hoge::HogeCallBack(const sensor_msgs::PointCloud2::ConstPtr& msg){
  pcl::PointCloud<pcl::PointXYZ> cloud;
  sensor_msgs::PointCloud2 output;
  pcl::fromROSMsg(*msg,cloud);
  pcl::toROSMsg(cloud,output);
  output.header.frame_id = "pcl_for_sim_frame";
  output.header.stamp = ros::Time::now();
  pub.publish(output);
  std::cout<<"publish!"<<std::endl;
  
}

int main(int argc,char** argv){
  ros::init(argc,argv,"pub_pcl_for_sim");
  Hoge hoge;
  ros::spin();
}
