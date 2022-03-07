#pragma once

#include <memory>

#include "LinesObject.h"
#include "math/AStar.h"

namespace fig {
class Path : public LinesObject {
 public:
  Path(Shader& shader, AStar& router);
  void render();
  APath route() const;
  bool init(glm::vec3 s, glm::vec3 e);
  void popLine();

 private:
  unsigned int indicesToRender() override;
  AStar& _router;
  APath _route;
  unsigned int _indicesToRender;
  static constexpr float Z_OFFSET = 0.1;
};

std::optional<std::unique_ptr<Path>> makePath(Shader& shader, AStar& router,
                                              glm::vec3 s, glm::vec3 e);
}  // namespace fig
