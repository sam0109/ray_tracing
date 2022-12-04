#ifndef SRC_RAY_H
#define SRC_RAY_H

#include "src/vec.h"

class Ray {
 public:
  Ray() {}
  Ray(const Point& origin, const Vec3& direction)
      : orig(origin), dir(direction) {}

  Point origin() const { return orig; }
  Vec3 direction() const { return dir; }

  Point at(double t) const { return orig + t * dir; }

 private:
  Point orig;
  Vec3 dir;
};

#endif  // SRC_RAY_H