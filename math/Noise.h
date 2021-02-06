#ifndef NOISE_H
#define NOISE_H

#include <glm/glm.hpp>

class Noise
{
public:
  struct Params
  {
    float frequency;
    float frequencyFactor;
    float amplitudeFactor;
  };

  Noise(unsigned int seed);
  float fractal(glm::vec2 p, Params parameters, unsigned int numLayers = 5);

private:
  float eval(glm::vec2 p);

  static const unsigned int PERIOD{ 256 };
  unsigned int _mask;
  glm::vec2 _gradients[PERIOD];
  int _pTable[PERIOD * 2];
};

#endif
