#pragma once

#include <glm/glm.hpp>

struct Vertex {
  static constexpr unsigned NUM_BONES_PER_VERTEX = 10;

  Vertex();
  void Reset();
  void AddBoneData(unsigned int BoneID, float Weight);

  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 texCoords;
  unsigned int IDs[NUM_BONES_PER_VERTEX];
  float Weights[NUM_BONES_PER_VERTEX];
};
