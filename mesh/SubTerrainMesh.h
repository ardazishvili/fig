#pragma once

#include <future>
#include <glm/glm.hpp>
#include <memory>
#include <vector>

#include "mesh/TerrainMesh.h"

namespace fig {
struct RectangleRegion {
  float x;
  float y;
  float width;
  float height;
};

struct CircularRegion {
  float x;
  float y;
  float r;
};

using Cells = std::vector<std::pair<unsigned int, unsigned int>>;
using AreaPlants = std::vector<glm::vec2>;
struct LivingArea {
  Cells cells;
  AreaPlants plants;
  CircularRegion region;
  glm::vec4 initRgba;
  std::future<void> future;
};

using LivingAreas = std::vector<std::shared_ptr<LivingArea>>;
class SubTerrainMesh : public TerrainMesh {
 public:
  void calculateHeights(unsigned int width, float bottomLeftX,
                        float bottomLeftY) override;
  void calculateColors(unsigned int width,
                       unsigned int augmentedWidth) override;
  std::shared_ptr<LivingArea> addLivingArea(CircularRegion region,
                                            glm::vec4 rgba);
  void growLivingArea(std::shared_ptr<LivingArea> area, float radius);
  void updateLivingArea(std::shared_ptr<LivingArea> area);

  const static glm::vec4 SELECTION_COLOR;
  const static glm::vec4 DESELECTION_COLOR;

 protected:
  void calculateIndices(int divisionsX, int divisionsY,
                        unsigned int latticeWidth) override;

 private:
  void reloadLivingArea(std::shared_ptr<LivingArea> area);
  void selectSubTerrainRegion(CircularRegion region, glm::vec4 rgba);

  LivingAreas _livingAreas;
};
}  // namespace fig
