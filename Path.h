#ifndef PATH_H
#define PATH_H

#include "LinesObject.h"
#include "math/AStar.h"

class Path : public LinesObject
{
public:
  Path(Shader& shader, AStar* router);
  void render();
  APath route() const;
  bool init(glm::vec3 s, glm::vec3 e);
  void popLine();

private:
  unsigned int indicesToRender() override;
  static const float Z_OFFSET;
  AStar* _router;
  APath _route;
  unsigned int _indicesToRender;
};

std::shared_ptr<Path> makePath(Shader& shader,
                               AStar* router,
                               glm::vec3 s,
                               glm::vec3 e);

#endif
