#include <memory>

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  auto node = rclcpp::Node::make_shared("transient_local_pub");

  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub = node->create_publisher<std_msgs::msg::String>("/latched", rclcpp::QoS(10).transient_local());

  auto msg = std::make_unique<std_msgs::msg::String>();
  msg->data = "transient_local";
  pub->publish(std::move(msg));

  rclcpp::spin(node);

  rclcpp::shutdown();

  return 0;
}
