#ifndef WINDOW_H
#define WINDOW_H

#include <functional>
#include <memory>

class Event;
class Window
{
public:
  struct Param
  {
    int width;
    int height;
  };

  Window(const Param& param);
  Window(const Window&) = delete;
  Window(Window&&) = delete;
  Window& operator=(const Window&) = delete;
  Window& operator=(Window&&) = delete;
  virtual ~Window() = default;

  virtual float width() const = 0;
  virtual float height() const = 0;
  virtual void getCursorPos(double* xpos, double* ypos) const = 0;
  virtual void setOnEvent(
    std::function<void(std::unique_ptr<Event> event)> onEvent) = 0;
  virtual void update() = 0;
  virtual void show() = 0;

  virtual bool shouldClose() = 0;
  virtual void close() = 0;

protected:
  Param _param;
};

#endif
