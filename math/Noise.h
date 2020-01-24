#ifndef NOISE_H
#define NOISE_H

#include <vector>

#include <glm/glm.hpp>

class Noise
{
public:
  Noise(unsigned int seed);
  float eval(glm::vec2 p, glm::vec2& derivs);
  float fractal(glm::vec2 p,
                glm::vec2& derivs,
                float frequency,
                float frequencyFactor,
                float amplitudeFactor,
                unsigned int numLayers = 1);

private:
  uint8_t hash(const int& x, const int& y) const;

  static const unsigned int PERIOD{ 256 };
  unsigned int _mask;
  glm::vec2 _gradients[PERIOD];
  int _pTable[PERIOD * 2];
};

#endif
