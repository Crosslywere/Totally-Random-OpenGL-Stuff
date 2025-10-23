#pragma once
#include <string_view>
#include <functional>
#include <glm/vec2.hpp>

namespace trogs {
  class Window {
  public:
    typedef void (*MousePosFn)(const Window&);
    /// Intializes the windowing system.
    static void Init();
    /// Deinitializes the windowing system.
    static void Deinit();
    /// Creates a window with specified dimensions and title.
    /// @param width The width of the window to be created. Cannot be 0.
    /// @param height The height of the window to be created. Cannot be 0.
    /// @param title The title of the window to be created.
    Window(int width = 800, int height = 600, const char* title = "Trog!");
    ~Window();
    /// Checks if the window is meant to stay open.
    bool IsOpen() const;
    /// Swaps the buffers and polls events for the window.
    void SwapAndPoll() const;
    /// Sets the window to close upon the next query of IsOpen().
    void Quit() const;
    inline const glm::vec2& GetMousePos() const { return m_MousePos; }
    inline const glm::vec2 GetInvertedMousePos() const { return { m_MousePos.x, m_Height - m_MousePos.y }; }
    inline int GetWidth() const { return m_Width; }
    inline int GetHeight() const { return m_Height; }
    inline void SetMouseButtonCallback(const std::function<void(bool, int)> &mouseButtonFunc) { m_MouseButtonFunc = mouseButtonFunc; }
    inline void SetMousePosCallback(const std::function<void(const Window&)> &mousePosFunc) { m_MousePosFunc = mousePosFunc; }
  private:
    struct GLFWwindow *m_Window{ nullptr };
    int m_Width;
    int m_Height;
    std::string_view m_Title;
    std::function<void(bool, int)> m_MouseButtonFunc = nullptr;
    std::function<void(const Window&)> m_MousePosFunc = nullptr;
    glm::vec2 m_MousePos{};
  };
} //namespace trogs
