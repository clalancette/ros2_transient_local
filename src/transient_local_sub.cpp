#include <functional>
#include <memory>

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

void cb(const std_msgs::msg::String::SharedPtr msg)
{
  fprintf(stderr, "Got message: %s\n", msg->data.c_str());
}

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  auto node = rclcpp::Node::make_shared("transient_local_sub");

  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub = node->create_subscription<std_msgs::msg::String>("/latched", rclcpp::QoS(10).transient_local(), std::bind(&cb, std::placeholders::_1));

  rclcpp::spin(node);

  rclcpp::shutdown();

  return 0;
}
