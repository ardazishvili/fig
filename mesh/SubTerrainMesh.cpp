#include "mesh/SubTerrainMesh.h"

#include <memory>

#include "globals.h"
#include "math/Noise.h"

namespace fig {
float lerp(float a, float b, float f) { return (a * (1.0 - f)) + (b * f); }

const glm::vec4 SubTerrainMesh::SELECTION_COLOR{0.0f, 0.0f, 1.0f, 0.3f};
const glm::vec4 SubTerrainMesh::DESELECTION_COLOR{0.0f, 0.0f, 1.0f, 0.0f};

std::unique_ptr<LivingArea> SubTerrainMesh::addLivingArea(CircularRegion region,
                                                          glm::vec4 rgba) {
  RectangleRegion rect = {region.x - region.r, region.y - region.r,
                          2 * region.r, 2 * region.r};
  auto x = region.x;
  auto y = region.y;
  auto r = region.r;

  auto i = ::floor(rect.x / _xStep) + _latticeWidth / 2;
  auto j = ::floor(rect.y / _yStep) + _latticeAugmentedWidth / 2;
  signed int xWidth = rect.width / _xStep;
  signed int yWidth = rect.height / _yStep;
  auto livingArea = std::make_unique<LivingArea>();
  auto center = glm::vec2(x, y);
  for (unsigned int k = i; k <= i + xWidth; ++k) {
    unsigned int index = 0;
    unsigned int stride = 0;
    auto indexIsSet = false;
    for (unsigned int n = j; n < j + yWidth; ++n) {
      auto m = k * _latticeAugmentedWidth + n;
      auto c = _v.at(m);

      auto point = glm::vec2(c.p.x, c.p.y);
      if (glm::distance(point, center) < r) {
        if (!indexIsSet) {
          index = m;
          indexIsSet = true;
        }
        _v.at(m).color = rgba;
        /* _v.at(m).color = glm::vec4(0, 1, 0, 1); */

        ++stride;
      }
    }
    livingArea->cells.push_back(std::make_pair(index, stride));
    livingArea->region = region;
    livingArea->initRgba = rgba;
  }
  reloadLivingArea(livingArea.get());
  _livingAreas.push_back(livingArea.get());
  return livingArea;
}

void SubTerrainMesh::growLivingArea(LivingArea* area, float radius) {
  auto prevRadius = area->region.r;
  area->region.r = radius;
  auto region = area->region;
  RectangleRegion rect = {region.x - region.r, region.y - region.r,
                          2 * region.r, 2 * region.r};
  auto x = region.x;
  auto y = region.y;
  auto r = region.r;

  auto i = ::floor(rect.x / _xStep) + _latticeWidth / 2;
  auto j = ::floor(rect.y / _yStep) + _latticeAugmentedWidth / 2;
  signed int xWidth = rect.width / _xStep;
  signed int yWidth = rect.height / _yStep;
  auto cells = Cells();
  auto center = glm::vec2(x, y);
  for (unsigned int k = i; k <= i + xWidth; ++k) {
    unsigned int index = 0;
    unsigned int stride = 0;
    auto indexIsSet = false;
    for (unsigned int n = j; n < j + yWidth; ++n) {
      auto m = k * _latticeAugmentedWidth + n;
      auto c = _v.at(m);

      auto point = glm::vec2(c.p.x, c.p.y);
      auto distance = glm::distance(point, center);
      if (distance < r) {
        if (!indexIsSet) {
          index = m;
          indexIsSet = true;
        }
        if (distance >= prevRadius - 0.1) {
          _v.at(m).color = area->initRgba;
          /* _v.at(m).color = glm::vec4(0, 1, 0, 1); */
        }

        ++stride;
      }
    }
    cells.push_back(std::make_pair(index, stride));
  }
  area->cells = cells;
  reloadLivingArea(area);
}

void SubTerrainMesh::reloadLivingArea(LivingArea* area) {
  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  for (auto& cell : area->cells) {
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(VertexColor) * (cell.first),
                    sizeof(VertexColor) * cell.second, &_v[cell.first]);
  }
}

void SubTerrainMesh::updateLivingArea(LivingArea* area) {
  logger.log("begin area update");
  logger.log("area->region.r", area->region.r);
  reloadLivingArea(area);
  AreaPlants plants = area->plants;
  area->future = std::async(std::launch::async, [this, plants, area]() {
    for (const auto& plant : plants) {
      for (const auto& cell : area->cells) {
        for (unsigned int i = cell.first; i < cell.first + cell.second; ++i) {
          auto cellX = _v.at(i).p.x;
          auto cellY = _v.at(i).p.y;
          auto cellPos = glm::vec2(cellX, cellY);
          float d = glm::distance(plant, cellPos);
          // norm distance: maximum of d is equal to "2 * radius"
          d /= 2 * area->region.r;
          double g = _v.at(i).color.y;
          auto factor = ::pow(1.0f - d, 30) / 100;
          auto newColor = lerp(g, 1.0, factor);
          _v.at(i).color.y = newColor;
        }
      }
    }
  });
  logger.log("end area update");
}

void SubTerrainMesh::calculateHeights(unsigned int width, float bottomLeftX,
                                      float bottomLeftY) {
  auto noise = Noise(777);
  std::cout << " SubTerrainMesh width: " << width << "\n";
  for (unsigned int i = 0; i < width; ++i) {
    for (unsigned int j = 0; j < width; ++j) {
      VertexColor vertex;
      vertex.p.x = bottomLeftX + i * _xStep;
      vertex.p.y = bottomLeftY + j * _yStep;
      auto nv = noise.fractal(glm::vec2(vertex.p.x, vertex.p.y),
                              Noise::Params{.frequency = 0.077,
                                            .frequencyFactor = 4.0,
                                            .amplitudeFactor = 0.366});
      vertex.p.x -= _halfWidth;
      vertex.p.y -= _halfHeight;
      vertex.p.z = nv + 0.1;
      _v.push_back(vertex);
    }
  }
}

void SubTerrainMesh::calculateIndices(int divisionsX, int divisionsY,
                                      unsigned int latticeWidth) {
  _indices.reserve(divisionsX * divisionsY * 2 * 3);
  for (int i = 0; i < divisionsX; ++i) {
    for (int j = 0; j < divisionsY; ++j) {
      _indices.push_back((i * latticeWidth) + j);
      _indices.push_back((i * latticeWidth) + j + 1);
      _indices.push_back((i * latticeWidth) + j + latticeWidth);

      _indices.push_back((i * latticeWidth) + j + 1);
      _indices.push_back((i * latticeWidth) + j + latticeWidth);
      _indices.push_back((i * latticeWidth) + j + latticeWidth + 1);
    }
  }
}

void SubTerrainMesh::calculateColors(unsigned int width,
                                     unsigned int augmentedWidth) {}
}  // namespace fig
