#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera
{
public:
  Camera() = delete;
  Camera(glm::vec3 positionVector, glm::vec3 lookAtVector, glm::vec3 upVector);
  void updateSpeed();
  void zoomIn();
  void zoomOut();
  void rotateLeft();
  void rotateRight();
  void rotateUp();
  void rotateDown();
  void moveForward();
  void moveBackward();
  void moveLeft();
  void moveRight();
  void zoom(double factor);
  float fov() const;
  glm::vec3 eye() const;
  glm::vec3 reference() const;
  glm::vec3 up() const;
  float getPitch() const;
  float getYaw() const;
  void setEye(glm::vec3 p);

private:
  void updatePosition();
  void updateFront();
  void initAngles();

  glm::vec3 _position;
  glm::vec3 _lookAt;
  glm::vec3 _front;
  glm::vec3 _up;
  float _yaw{ 90.0f };
  float _pitch;
  float _speed;
  float _deltaTime{ 0.0 };
  float _lastFrame{ 0.0 };
  float _fov{ 45.0f };
  float _lastX{ 400 };
  float _lastY{ 300 };
  bool _firstMouse{ true };
  float _camRadius;
  float _rotationSpeed{ 1.0 };
  float _moveSpeed{ 1.0f };
};

#endif
