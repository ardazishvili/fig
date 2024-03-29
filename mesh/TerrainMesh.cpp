#include "mesh/TerrainMesh.h"

#include <algorithm>

#include "Core.h"
#include "globals.h"
#include "mesh/TerrainMeshSegment.h"

namespace fig {
void TerrainMesh::render() {
  glBindVertexArray(_vao);
  glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

void TerrainMesh::init(float bottomLeftX, float bottomLeftY, float topRightX,
                       float topRightY, int divisions, float zScale,
                       TerrainType type) {
  _v.reserve((divisions + 1) * 2 * divisions);
  _width = topRightX - bottomLeftX;
  _height = topRightY - bottomLeftY;
  _halfWidth = _width / 2;
  _halfHeight = _height / 2;
  _xStep = (topRightX - bottomLeftX) / divisions;
  _yStep = (topRightY - bottomLeftY) / divisions;
  _zScale = zScale;
  int width = divisions + 1;

  calculateHeights(width, bottomLeftX, bottomLeftY);

  _latticeWidth = width;
  _latticeHeight = width;
  unsigned int w;
  if (type == TerrainType::Main) {
    w = divisions + 1 + (divisions + 1 - 2);
  } else {
    w = width;
  }
  _latticeAugmentedWidth = w;
  calculateNormals(width, w);
  calculateColors(width, w);
  calculateIndices(divisions, divisions, w);

  glBindVertexArray(_vao);
  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(VertexColor) * _v.size(), &_v[0],
               GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexColor),
                        (void*)offsetof(VertexColor, p));

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexColor),
                        (void*)offsetof(VertexColor, color));

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexColor),
                        (void*)offsetof(VertexColor, normal));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices[0]) * _indices.size(),
               &_indices[0], GL_STATIC_DRAW);

  glBindVertexArray(0);
}

void TerrainMesh::calculateNormals(int width, unsigned int latticeWidth) {
  for (int i = 0; i < width - 1; ++i) {
    for (unsigned int j = 0; j < latticeWidth; ++j) {
      glm::vec3 p0(0);
      glm::vec3 p1(0);
      glm::vec3 p2(0);
      auto rectangleTypeNum = ((i % 2) * 2 + j) % 4;
      try {
        if (rectangleTypeNum == 0) {
          p1 = _v.at(latticeWidth * i + j + 1 + latticeWidth).p;
          p2 = _v.at(latticeWidth * i + j).p;
          p0 = _v.at(latticeWidth * i + j + latticeWidth).p;
        } else if (rectangleTypeNum == 1) {
          p1 = _v.at(latticeWidth * i + j - 1).p;
          p2 = _v.at(latticeWidth * i + j + latticeWidth).p;
          p0 = _v.at(latticeWidth * i + j).p;
        } else if (rectangleTypeNum == 2) {
          p1 = _v.at(latticeWidth * i + j + latticeWidth).p;
          p2 = _v.at(latticeWidth * i + j + 1).p;
          p0 = _v.at(latticeWidth * i + j).p;
        } else if (rectangleTypeNum == 3) {
          p1 = _v.at(latticeWidth * i + j).p;
          p2 = _v.at(latticeWidth * i + j - 1 + latticeWidth).p;
          p0 = _v.at(latticeWidth * i + j + latticeWidth).p;
        }
      } catch (const std::out_of_range& e) {
        FG_CORE_DEBUG("Out of range while calculating normals");
      }
      _v[latticeWidth * i + j].normal = glm::cross(p1 - p0, p2 - p0);
    }
  }
}

void TerrainMesh::getSegmentVertices(glm::vec2 bottomLeft, glm::vec2 topRight,
                                     std::vector<VertexColor>& v,
                                     SegmentDimensions* sd) {
  sd->divisionsX = (topRight.x - bottomLeft.x) / _xStep;
  sd->divisionsY = (topRight.y - bottomLeft.y) / _yStep;
  sd->latticeWidth = sd->divisionsY + 1;
  sd->xStep = _xStep;
  sd->yStep = _yStep;

  bottomLeft.x += _halfWidth;
  topRight.x += _halfWidth;
  bottomLeft.y += _halfHeight;
  topRight.y += _halfHeight;

  float startI = _latticeHeight * bottomLeft.x / _width;
  float startJ = _latticeAugmentedWidth * bottomLeft.y / _height;
  for (unsigned int i = startI; i < startI + sd->divisionsX; ++i) {
    for (unsigned int j = startJ; j < startJ + sd->divisionsY * 2; j += 2) {
      v.push_back(_v.at(_latticeAugmentedWidth * i + j));
    }
  }
}
}  // namespace fig
