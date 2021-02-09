#include <optional>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../fig/globals.h"
#include "Core.h"
#include "Path.h"
#include "math/AStar.h"

namespace fig
{
const float Path::Z_OFFSET = 0.1;

Path::Path(Shader& shader, APath route, glm::vec3 start) : LinesObject(shader), _route(route)
{
  _v.clear();
  _i.clear();

  try {
    for (unsigned int i = 0; i < _route.size() - 1; ++i) {
      glm::vec3 start{ _route.at(i).x, _route.at(i).y, start.z + Z_OFFSET };
      _v.push_back(start);
      _i.push_back(i);
      _i.push_back(i + 1);
    }
    glm::vec3 start{ _route.at(_route.size() - 1).x, _route.at(_route.size() - 1).y, start.z + Z_OFFSET };
    _v.push_back(start);
  } catch (const std::out_of_range& e) {
    FG_CORE_DEBUG("Out of range at path init");
  }

  _indicesToRender = _i.size();
  LinesObject::initBuffers();
}

APath Path::route() const
{
  return _route;
}

void Path::render()
{
  _shader.use();
  _shader.configure();
  auto model = glm::mat4(1.0f);
  _shader.setTransformation("model", glm::value_ptr(model));
  _shader.setBool("animated", false);

  LinesObject::render();
}

std::optional<Path> makePath(Shader& shader, AStar* router, glm::vec3 start, glm::vec3 end)
{
  auto route = router->getPath(glm::vec2(start.x, start.y), glm::vec2(end.x, end.y));
  if (route.has_value()) {
    return std::make_optional<Path>(shader, route.value(), start);
  }
  return std::nullopt;
}

void Path::popLine()
{
  _indicesToRender -= 2;
}

unsigned int Path::indicesToRender()
{
  return _indicesToRender;
}
}
