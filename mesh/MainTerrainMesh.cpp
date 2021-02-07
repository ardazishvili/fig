#include <algorithm>
#include <iostream>
#include <map>
#include <string>

#include "../math/Noise.h"
#include "MainTerrainMesh.h"
#include "TerrainMeshSegment.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

namespace fig
{
struct RgbColor
{
  float r;
  float g;
  float b;
};

using HeightPart = float;
std::map<HeightPart, RgbColor> colorMapping = { { 0.0f, { 113.0f / 255, 128.0f / 255, 143.0f / 255 } },
                                                { 0.5f, { 237.0f / 255, 227.0f / 255, 143.0f / 255 } },
                                                { 1.0f, { 242.0f / 255, 127.0f / 255, 115.0f / 255 } } };

void MainTerrainMesh::calculateHeights(unsigned int width, float bottomLeftX, float bottomLeftY)
{
  auto noise = Noise(777);

  static float waterCoefLongitude = 2.0f / 8;
  static float waterCoefLatitude = 2.0f / 8;
  for (unsigned int i = 0; i < width; ++i) {
    for (unsigned int j = 0; j < width; ++j) {
      VertexColor vertex;
      vertex.p.x = bottomLeftX + i * _xStep;
      vertex.p.y = bottomLeftY + j * _yStep;

      auto nv = noise.fractal(glm::vec2(vertex.p.x, vertex.p.y),
                              Noise::Params{ .frequency = 0.204, .frequencyFactor = 2.0, .amplitudeFactor = 0.6 });
      auto nonPlain = nv * _zScale;
      auto plain = noise.fractal(glm::vec2(vertex.p.x, vertex.p.y),
                                 Noise::Params{ .frequency = 0.077, .frequencyFactor = 4.0, .amplitudeFactor = 0.366 });
      auto water = -0.3f;

      auto widthFactor = (vertex.p.x - bottomLeftX) / _width;
      auto heightFactor = (vertex.p.y - bottomLeftY) / _height;
      auto differentiate_heights = [](float& nonPlain, float& plain, float mult) {
        float npf = 1;
        nonPlain = nonPlain * mult - (npf - mult);
        plain = plain * mult - std::pow((npf - mult), 2);
      };

      auto nearTheBorderWidthFactor = std::min(widthFactor, 1.0f - widthFactor);
      if (nearTheBorderWidthFactor < waterCoefLongitude) {
        differentiate_heights(nonPlain, plain, nearTheBorderWidthFactor / waterCoefLongitude);
      }
      auto nearTheBorderHeightFactor = std::min(heightFactor, 1.0f - heightFactor);
      if (nearTheBorderHeightFactor < waterCoefLatitude) {
        differentiate_heights(nonPlain, plain, nearTheBorderHeightFactor / waterCoefLatitude);
      }

      vertex.p.z = std::max(std::max(plain, nonPlain), water);
      vertex.p.y -= _halfHeight;
      vertex.p.x -= _halfWidth;
      vertex.normal = glm::vec3(0.0f);

      _obstaclesMap.push_back(nonPlain > plain);
      _v.push_back(vertex);
      if (j != 0 && j != (width - 1)) {
        _v.push_back(vertex);
      }
    }
  }
}

void MainTerrainMesh::calculateColors(unsigned int width, unsigned int augmentedWidth)
{
  auto [min, max] = std::minmax_element(_v.begin(), _v.end(), [](const auto& lhs, const auto& rhs) {
    return lhs.p.z < rhs.p.z;
  });
  auto amplitude = max->p.z - min->p.z;
  for (unsigned int i = 0; i < width; ++i) {
    for (unsigned int j = 0; j < augmentedWidth; ++j) {
      auto z = _v[augmentedWidth * i + j].p.z;
      RgbColor a, b;
      auto h = (z - min->p.z) / amplitude;
      if (h <= amplitude * 0.2) {
        a = colorMapping[0.0f];
        b = colorMapping[0.5f];
        h *= 2;
      } else {
        a = colorMapping[0.5f];
        b = colorMapping[1.0f];
        h = (h - 0.5) * 2;
      }
      _v[augmentedWidth * i + j].color.x = glm::lerp(a.r, b.r, h);
      _v[augmentedWidth * i + j].color.y = glm::lerp(a.g, b.g, h);
      _v[augmentedWidth * i + j].color.z = glm::lerp(a.b, b.b, h);
      _v[augmentedWidth * i + j].color.w = 1.0;
    }
  }
}

float MainTerrainMesh::getZ(float x, float y) const
{
  x += _halfWidth;
  y += _halfHeight;
  auto i = ::floor(x / _xStep);
  auto j = ::floor(y / _yStep);
  auto mappedJ = (j == 0) ? 0 : 2 * j - 1;
  assert(_v.size() >= i * _latticeAugmentedWidth + mappedJ);
  return _v.at(i * _latticeAugmentedWidth + mappedJ).p.z;
}

glm::vec3 MainTerrainMesh::getRgbColor(float x, float y) const
{
  x += _halfWidth;
  y += _halfHeight;
  auto i = ::floor(x / _xStep);
  auto j = ::floor(y / _yStep);
  auto mappedJ = (j == 0) ? 0 : 2 * j - 1;
  assert(_v.size() >= i * _latticeAugmentedWidth + mappedJ);
  auto c = _v.at(i * _latticeAugmentedWidth + mappedJ).color;
  return glm::vec3(c.x, c.y, c.z);
}

void MainTerrainMesh::getSegmentObstaclesMap(glm::vec2 bottomLeft,
                                             glm::vec2 topRight,
                                             std::vector<bool>& m,
                                             SegmentDimensions* sd)
{
  sd->divisionsX = (topRight.x - bottomLeft.x) / _xStep;
  sd->divisionsY = (topRight.y - bottomLeft.y) / _yStep;
  sd->latticeWidth = sd->divisionsY + 1;
  sd->xStep = _xStep;
  sd->yStep = _yStep;

  bottomLeft.x += _halfWidth;
  topRight.x += _halfWidth;
  bottomLeft.y += _halfHeight;
  topRight.y += _halfHeight;

  unsigned int startI = _latticeHeight * bottomLeft.x / _width;
  unsigned int startJ = _latticeWidth * bottomLeft.y / _height;

  for (unsigned int i = startI; i < startI + sd->divisionsX + 1; ++i) {
    for (unsigned int j = startJ; j < startJ + sd->divisionsY + 1; ++j) {
      m.push_back(_obstaclesMap.at(_latticeWidth * i + j));
    }
  }
}

void MainTerrainMesh::calculateIndices(int divisionsX, int divisionsY, unsigned int latticeWidth)
{
  _indices.reserve(divisionsX * divisionsY * 2 * 3);
  for (int i = 0; i < divisionsX; ++i) {
    for (int j = 0; j < divisionsY; ++j) {
      auto j2 = j * 2;
      if (((i % 2) + j) % 2 == 0) {
        _indices.push_back(i * latticeWidth + j2);
        _indices.push_back(i * latticeWidth + j2 + latticeWidth);
        _indices.push_back(i * latticeWidth + j2 + latticeWidth + 1);

        _indices.push_back(i * latticeWidth + j2 + 1);
        _indices.push_back(i * latticeWidth + j2);
        _indices.push_back(i * latticeWidth + j2 + latticeWidth + 1);
      } else {
        _indices.push_back(i * latticeWidth + j2);
        _indices.push_back(i * latticeWidth + j2 + latticeWidth);
        _indices.push_back(i * latticeWidth + j2 + 1);

        _indices.push_back(i * latticeWidth + j2 + 1);
        _indices.push_back(i * latticeWidth + j2 + latticeWidth);
        _indices.push_back(i * latticeWidth + j2 + latticeWidth + 1);
      }
    }
  }
}

}
