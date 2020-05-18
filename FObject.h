#ifndef F_OBJECT_H
#define F_OBJECT_H

class FObject
{
public:
  virtual void render() = 0;
  FObject() = default;
  FObject(const FObject&) = delete;
  FObject(FObject&&) = delete;
  FObject& operator=(const FObject&) = delete;
  FObject& operator=(FObject&&) = delete;
  ~FObject() = default;
};

#endif
