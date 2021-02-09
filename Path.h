#ifndef PATH_H
#define PATH_H

#include <optional>

#include "LinesObject.h"
#include "math/AStar.h"

namespace fig
{
class Path : public LinesObject
{
public:
  Path(Shader& shader, APath route, glm::vec3 start);
  void render();
  APath route() const;
  void popLine();

private:
  unsigned int indicesToRender() override;
  static const float Z_OFFSET;
  APath _route;
  unsigned int _indicesToRender;
};

std::optional<Path> makePath(Shader& shader, AStar* router, glm::vec3 s, glm::vec3 e);
}

#endif
