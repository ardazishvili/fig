#ifndef LAYER_H
#define LAYER_H

class Layer
{
public:
  Layer() = default;
  Layer(const Layer&) = delete;
  Layer(Layer&&) = delete;
  Layer& operator=(const Layer&) = delete;
  Layer& operator=(Layer&&) = delete;
  virtual ~Layer() = default;

  virtual void init() = 0;
  virtual void update() = 0;
  virtual void render() = 0;
};

#endif
