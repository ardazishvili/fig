#ifndef TERRAIN_MESH_H
#define TERRAIN_MESH_H

#include <vector>

#include <glm/glm.hpp>

#include "Mesh.h"

enum class TerrainType { Main, Sub };

struct VertexColor
{
  glm::vec3 p;
  glm::vec3 normal;
  glm::vec4 color;
};

struct SegmentDimensions;
class TerrainMesh : public Mesh
{
public:
  virtual void render();
  void init(float bottomLeftX,
            float bottomLeftY,
            float topRightX,
            float topRightY,
            int divisions,
            float zScale,
            TerrainType type);
  virtual void calculateHeights(unsigned int width,
                                float bottomLeftX,
                                float bottomLeftY,
                                float& min,
                                float& max) = 0;
  virtual void calculateColors(float min,
                               float max,
                               unsigned int width,
                               unsigned int augmentedWidth) = 0;
  void getSegmentVertices(glm::vec2 bottomLeft,
                          glm::vec2 topRight,
                          std::vector<VertexColor>& v,
                          SegmentDimensions* sd);
  float halfWidth() const;
  float halfHeight() const;

protected:
  virtual void calculateIndices(int divisionsX,
                                int divisionsY,
                                unsigned int latticeWidth);
  void calculateNormals(int width, unsigned int latticeWidth);

  std::vector<VertexColor> _v;
  std::vector<unsigned int> _indices;
  float _width;
  float _height;
  unsigned int _latticeAugmentedWidth;
  unsigned int _latticeWidth;
  unsigned int _latticeHeight;
  float _xStep;
  float _yStep;
  float _zScale;
};

#endif
