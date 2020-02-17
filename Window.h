#ifndef WINDOW_H
#define WINDOW_H

#include <functional>
#include <memory>

#include "WindowBackground.h"

class Event;

/**
 * @brief Basic abstraction of a Window
 *
 * This class have to be subclassed to implement window
 * handling in different frameworks such as GLFW or SFML
 */
class Window
{
public:
  /**
   * @brief Window paramaters
   */
  struct Param
  {

    /**
     * @brief Width
     */
    int width;

    /**
     * @brief Height
     */
    int height;
  };

  /**
   * @brief Ctor
   *
   * @param param
   */
  Window(const Param& param);
  Window(const Window&) = delete;
  Window(Window&&) = delete;
  Window& operator=(const Window&) = delete;
  Window& operator=(Window&&) = delete;
  virtual ~Window() = default;

  /**
   * @brief Width getter
   *
   * @return
   */
  virtual float width() const = 0;

  /**
   * @brief Height getter
   *
   * @return
   */
  virtual float height() const = 0;

  /**
   * @brief Get current position of cursor
   *
   * @param[in,out] xpos
   * @param[in,out] ypos
   */
  virtual void getCursorPos(double* xpos, double* ypos) const = 0;

  /**
   * @brief Handler of events
   *
   * @param onEvent
   */
  virtual void setOnEvent(
    std::function<void(std::unique_ptr<Event> event)> onEvent) = 0;

  /**
   * @brief Code that must be called to update window, e.g. clear the window and
   * poll events
   */
  virtual void update() = 0;

  /**
   * @brief Code that must be called to show updated window, e.g. just swap
   * buffers
   */
  virtual void show() = 0;

  /**
   * @brief Check if the window should be closed, e.g. at shutdown
   *
   * @return true if the window must be closed
   */
  virtual bool shouldClose() = 0;

  /**
   * @brief Close the window
   */
  virtual void close() = 0;

  /**
   * @brief Set background color
   *
   * @param color
   */
  void setBackgroundColor(const Color& color);

protected:
  /**
   * @brief Parameters of the window
   */
  Param _param;
  Color _color{ 1, 1, 1, 1 };
};

#endif
