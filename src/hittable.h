#ifndef SRC_HITTABLE_H
#define SRC_HITTABLE_H

#include "src/ray.h"
#include "src/vec.h"

struct HitRecord {
  Point p;
  Vec3 normal;
  double t;
  bool front_face;

  inline void SetFaceNormal(const Ray& r, const Vec3& outward_normal) {
    front_face = dot(r.direction(), outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
  }
};

class Hittable {
 public:
  virtual bool Hit(const Ray& r, double t_min, double t_max,
                   HitRecord& rec) const = 0;
  virtual ~Hittable() = default;
};

#endif  // SRC_HITTABLE_H