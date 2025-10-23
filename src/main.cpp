#include <window.hpp>
#include <iostream>
#include <functional>
using namespace trogs;

class Test {
public:
  Test(Window &window) {
    window.SetMousePosCallback(std::bind(&Test::MousePosFunc, this, std::placeholders::_1));
    window.SetMouseButtonCallback(std::bind(&Test::MouseButtonFunc, this, std::placeholders::_1, std::placeholders::_2));
  }
  void MousePosFunc(const Window& window) {
    if (currentMousePos != window.GetMousePos()) {
      currentMousePos = window.GetMousePos();
      std::printf("[%.0f, %.0f]\r", currentMousePos.x, currentMousePos.y);
    }
  }
  void MouseButtonFunc(bool isPressed, int button) {
    if (isPressed && button == 0) std::cout << "Click!" << std::endl;
  }
private:
  glm::vec2 currentMousePos = {};
};

int main() {
  Window::Init();
  Window window{1280, 720};
  Test test(window);
  while(window.IsOpen()) {
    window.SwapAndPoll();
  }
  Window::Deinit();
}
