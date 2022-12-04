#ifndef SRC_HITTABLE_LIST_H
#define SRC_HITTABLE_LIST_H

#include <memory>
#include <vector>

#include "src/hittable.h"
#include "src/ray.h"

class HittableList : public Hittable {
 public:
  HittableList() {}
  HittableList(std::shared_ptr<Hittable> object) { add(object); }

  void clear() { objects.clear(); }
  void add(std::shared_ptr<Hittable> object) { objects.push_back(object); }

  virtual bool Hit(const Ray& r, double t_min, double t_max,
                   HitRecord& rec) const override;

 public:
  std::vector<std::shared_ptr<Hittable>> objects;
};

bool HittableList::Hit(const Ray& r, double t_min, double t_max,
                        HitRecord& rec) const {
  HitRecord temp_rec;
  bool hit_anything = false;
  auto closest_so_far = t_max;

  for (const auto& object : objects) {
    if (object->Hit(r, t_min, closest_so_far, temp_rec)) {
      hit_anything = true;
      closest_so_far = temp_rec.t;
      rec = temp_rec;
    }
  }

  return hit_anything;
}

#endif  // SRC_HITTABLE_LIST
