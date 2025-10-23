#include "pch.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <window.hpp>

namespace trogs {
  void Window::Init() {
    glfwInit();
  }
  void Window::Deinit() {
    glfwTerminate();
  }
  Window::Window(int width, int height, const char* title)
      : m_Width{width}, m_Height{height}, m_Title{title} {
    // Setting the opengl version to 3.3 core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Creating the window based on passed parameters
    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.data(), nullptr, nullptr);
    if (!m_Window) { // If the window was not created
      std::cerr << "Failed to create window!" << std::endl;
      Deinit();
      exit(EXIT_FAILURE);
    }
    // Setting the window to be the current render context
    glfwMakeContextCurrent(m_Window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { // If the functions pointers cannot be loaded
      std::cerr << "Failed to load the proper version of OpenGL ie 3.3 core!" << std::endl;
      Deinit();
      exit(EXIT_FAILURE);
    }
    // Making vsync as on
    glfwSwapInterval(1);
    glfwSetWindowSizeLimits(m_Window, width, height, GLFW_DONT_CARE, GLFW_DONT_CARE);
    // Using this class as the function pointer
    glfwSetWindowUserPointer(m_Window, this);
    // Setting the window resize callback
    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *window, int width, int height) {
      glViewport(0, 0, width, height); // Resizing the viewport
      // Setting this classes dimensions
      auto &w = *(Window*)glfwGetWindowUserPointer(window);
      w.m_Width = width;
      w.m_Height = height;
    });
    // Setting the mouse position callback
    glfwSetCursorPosCallback(m_Window, [](GLFWwindow *window, double xpos, double ypos) {
      auto &w = *(Window*)glfwGetWindowUserPointer(window);
      w.m_MousePos = { xpos, ypos };
      // Using the function callback
      if (w.m_MousePosFunc) w.m_MousePosFunc(w);
    });
    // Setting the mouse button callback
    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
      auto &w = *(Window*)glfwGetWindowUserPointer(window);
      // Using the function callback
      if (w.m_MouseButtonFunc) w.m_MouseButtonFunc(action, button);
    });
  }
  Window::~Window() {
    glfwDestroyWindow(m_Window);
  }
  bool Window::IsOpen() const {
    return !glfwWindowShouldClose(m_Window);
  }
  void Window::SwapAndPoll() const {
    glfwSwapBuffers(m_Window);
    glfwPollEvents();
  }
  void Window::Quit() const {
    glfwSetWindowShouldClose(m_Window, true);
  }
} //namespace trogs
