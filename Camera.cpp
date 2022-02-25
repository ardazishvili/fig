#include "Camera.h"

#include <GL/glew.h>

#include <chrono>
#include <iostream>

#include "globals.h"

namespace fig {
Camera::Camera(glm::vec3 position, glm::vec3 lookAt, glm::vec3 up)
    : _position(position), _lookAt(lookAt), _up(up) {
  auto config = CONFIG.get();
  _moveSpeed = config.moveSpeed;
  _rotationSpeed = config.rotationSpeed;
  initAngles();
  updateFront();
}

void Camera::updateSpeed() {
  float currentFrame =
      std::chrono::duration_cast<std::chrono::seconds>(_timer.elapsed())
          .count();
  _deltaTime = currentFrame - _lastFrame;
  _lastFrame = currentFrame;
  _speed = 10.5f * _deltaTime;  // adjust accordingly
}

void Camera::zoomIn() { _position += _speed * _front; }

void Camera::zoomOut() { _position -= _speed * _front; }

void Camera::rotateLeft() {
  _yaw -= _rotationSpeed;
  updatePosition();
}

void Camera::rotateRight() {
  _yaw += _rotationSpeed;
  updatePosition();
}

void Camera::rotateUp() {
  _pitch += _rotationSpeed;
  updatePosition();
}

void Camera::rotateDown() {
  _pitch -= _rotationSpeed;
  updatePosition();
}

void Camera::moveForward() {
  _position.x += _front.x * _moveSpeed;
  _position.y += _front.y * _moveSpeed;
  _lookAt.x += _front.x * _moveSpeed;
  _lookAt.y += _front.y * _moveSpeed;
}

void Camera::moveBackward() {
  _position.x -= _front.x * _moveSpeed;
  _position.y -= _front.y * _moveSpeed;
  _lookAt.x -= _front.x * _moveSpeed;
  _lookAt.y -= _front.y * _moveSpeed;
}

void Camera::moveLeft() {
  _position -= glm::normalize(glm::cross(_up, -_front)) * _moveSpeed;
  _lookAt -= glm::normalize(glm::cross(_up, -_front)) * _moveSpeed;
}

void Camera::moveRight() {
  _position += glm::normalize(glm::cross(_up, -_front)) * _moveSpeed;
  _lookAt += glm::normalize(glm::cross(_up, -_front)) * _moveSpeed;
}

void Camera::zoom(double factor) {
  if (_fov >= 1.0f && _fov <= 45.0f) _fov -= factor;
  if (_fov <= 1.0f) _fov = 1.0f;
  if (_fov >= 45.0f) _fov = 45.0f;
}

float Camera::fov() const { return _fov; }

glm::vec3 Camera::eye() const { return _position; }

glm::vec3 Camera::reference() const { return _position + _front; }

glm::vec3 Camera::up() const { return _up; }

void Camera::updateFront() {
  glm::vec3 front;
  front.x = ::cos(glm::radians(_pitch)) * ::cos(glm::radians(_yaw));
  front.y = ::cos(glm::radians(_pitch)) * ::sin(glm::radians(_yaw));
  front.z = ::sin(glm::radians(_pitch));
  _front = glm::normalize(front);
}

float Camera::getPitch() const { return _pitch; }

float Camera::getYaw() const { return _yaw; }

void Camera::updatePosition() {
  _position.x = _lookAt.x - ::sin(glm::radians(_yaw + 90)) * _camRadius;
  _position.y = _lookAt.y + ::cos(glm::radians(_yaw + 90)) * _camRadius;
  updateFront();
}

void Camera::setEye(glm::vec3 p) { _position = p; }

void Camera::initAngles() {
  float a = ::abs(_position.z - _lookAt.z);
  auto rCamPosition = ::sqrt(::pow(_position.x, 2) + ::pow(_position.y, 2));
  auto rLookAt = ::sqrt(::pow(_lookAt.x, 2) + ::pow(_lookAt.y, 2));
  float b = ::abs(rCamPosition - rLookAt);

  _pitch = -glm::degrees(::atan(a / b));
  _camRadius = b;
}
}  // namespace fig
