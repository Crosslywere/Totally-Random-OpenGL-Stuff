#include <window.hpp>
#include <iostream>
#include <functional>
#include <glad/glad.h>
using namespace trogs;

class Test {
public:
  Test(Window &window) {
    window.SetMousePosCallback(std::bind(&Test::MousePosFunc, this, std::placeholders::_1));
    window.SetMouseButtonCallback(std::bind(&Test::MouseButtonFunc, this, std::placeholders::_1, std::placeholders::_2));
    float vertices[] = {
      -.5f, .5f,
      -.5f,-.5f,
      .5f, -.5f,
      .5f, -.5f,
      .5f,  .5f,
      -.5f, .5f,
    };
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(0);
    shader = glCreateProgram();
    unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
    const char *vsource = R"(#version 330 core
    layout (location = 0) in vec2 aPos;
    out vec2 vTexCoord;
    void main() {
    vTexCoord = aPos + vec2(0.5);
    gl_Position = vec4(aPos, 0.0, 1.0);
    })";
    glShaderSource(vs, 1, &vsource, nullptr);
    glCompileShader(vs);
    glAttachShader(shader, vs);
    glDeleteShader(vs);
    unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fsource = R"(#version 330 core
    in vec2 vTexCoord;
    void main() {
    gl_FragColor = vec4(vTexCoord, 0.0, 1.0);
    })";
    glShaderSource(fs, 1, &fsource, nullptr);
    glCompileShader(fs);
    glAttachShader(shader, fs);
    glDeleteShader(fs);
    glLinkProgram(shader);
  }
  void MousePosFunc(const Window& window) {
    if (currentMousePos != window.GetMousePos()) {
      currentMousePos = window.GetMousePos();
      std::printf("[%.0f, %.0f]     \r", currentMousePos.x, currentMousePos.y);
    }
  }
  void MouseButtonFunc(bool isPressed, int button) {
    if (isPressed && button == 0) std::cout << "\nClick!" << std::endl;
  }
  void Draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(vao);
    glUseProgram(shader);
    glDrawArrays(GL_TRIANGLES, 0, 6);
  }
private:
  glm::vec2 currentMousePos = {};
  unsigned int vao{}, vbo{};
  unsigned int shader{};
};

int main() {
  Window::Init();
  Window window{1280, 720};
  Test test(window);
  while(window.IsOpen()) {
    test.Draw();
    window.SwapAndPoll();
  }
  Window::Deinit();
}
