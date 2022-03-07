#include "Path.h"

#include <cstddef>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <optional>

#include "../fig/globals.h"
#include "Core.h"

namespace fig {

Path::Path(Shader& shader, AStar& router)
    : LinesObject(shader), _router(router) {
  _v.clear();
  _i.clear();
}

bool Path::init(glm::vec3 s, glm::vec3 e) {
  auto route = _router.getPath(glm::vec2(s.x, s.y), glm::vec2(e.x, e.y));
  if (!route) {
    return false;
  }
  _route = *route;
  try {
    for (unsigned int i = 0; i < _route.size() - 1; ++i) {
      glm::vec3 start{_route.at(i).x, _route.at(i).y, s.z + Z_OFFSET};
      _v.push_back(start);
      _i.push_back(i);
      _i.push_back(i + 1);
    }
    glm::vec3 start{_route.at(_route.size() - 1).x,
                    _route.at(_route.size() - 1).y, s.z + Z_OFFSET};
    _v.push_back(start);
  } catch (const std::out_of_range& e) {
    FG_CORE_DEBUG("Out of range at path init");
  }

  _indicesToRender = _i.size();
  LinesObject::initBuffers();
  return true;
}

APath Path::route() const { return _route; }

void Path::render() {
  _shader.use();
  _shader.configure();
  auto model = glm::mat4(1.0f);
  _shader.setTransformation("model", glm::value_ptr(model));
  _shader.setBool("animated", false);

  LinesObject::render();
}

std::optional<std::unique_ptr<Path>> makePath(Shader& shader, AStar& router,
                                              glm::vec3 s, glm::vec3 e) {
  auto path = std::make_unique<Path>(shader, router);
  if (path->init(s, e)) {
    return path;
  }
  return {};
}

void Path::popLine() { _indicesToRender -= 2; }

unsigned int Path::indicesToRender() { return _indicesToRender; }
}  // namespace fig
