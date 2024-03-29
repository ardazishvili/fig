#include "Terrain.h"

#include <glm/gtc/type_ptr.hpp>
#include <memory>

namespace fig {

Terrain::Terrain(Shader& shader, Camera& camera, float bottomLeftX,
                 float bottomLeftY, float topRightX, float topRightY,
                 int divisions, float zScale)
    : _shader(shader), _camera(camera), _zScale(zScale) {
  _mainMesh.init(0, 0, topRightX - bottomLeftX, topRightY - bottomLeftY,
                 divisions, zScale, TerrainType::Main);
  _subMesh.init(0, 0, topRightX - bottomLeftX, topRightY - bottomLeftY,
                divisions * 3, zScale, TerrainType::Sub);
  _maxX = topRightX;
  _maxY = topRightY;
}

void Terrain::render() {
  _shader.use();
  _shader.configure();
  auto model = glm::mat4(1.0f);
  _shader.setTransformation("model", glm::value_ptr(model));
  _shader.setBool("animated", false);
  _mainMesh.render();
}

void Terrain::renderSub() {
  _shader.use();
  _shader.configure();
  glEnable(GL_BLEND);
  glDepthMask(GL_FALSE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  auto model = glm::mat4(1.0f);
  _shader.setTransformation("model", glm::value_ptr(model));
  _shader.setBool("animated", false);
  _subMesh.render();
  glDisable(GL_BLEND);
  glDepthMask(GL_TRUE);
}

glm::vec3 Terrain::getXYZ(glm::vec2 xy) const {
  return glm::vec3(xy.x, xy.y, _mainMesh.getZ(xy.x, xy.y));
}

glm::vec3 Terrain::getRgbColor(float x, float y) const {
  return _mainMesh.getRgbColor(x, y);
}

std::unique_ptr<LivingArea> Terrain::addLivingArea(CircularRegion region,
                                                   glm::vec4 rgba) {
  return _subMesh.addLivingArea(region, rgba);
}

void Terrain::updateLivingArea(LivingArea* area) {
  _subMesh.updateLivingArea(area);
}

std::pair<float, float> Terrain::getMaxXy() const { return {_maxX, _maxY}; }

void Terrain::growLivingArea(LivingArea* area, float radius) {
  _subMesh.growLivingArea(area, radius);
}
void Terrain::getSegmentVertices(glm::vec2 bottomLeft, glm::vec2 topRight,
                                 std::vector<VertexColor>& v,
                                 SegmentDimensions* sd) {
  _mainMesh.getSegmentVertices(bottomLeft, topRight, v, sd);
}

void Terrain::getSegmentObstaclesMap(glm::vec2 bottomLeft, glm::vec2 topRight,
                                     std::vector<bool>& m,
                                     SegmentDimensions* sd) {
  _mainMesh.getSegmentObstaclesMap(bottomLeft, topRight, m, sd);
}
}  // namespace fig
