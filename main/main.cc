#include <iostream>

#include "src/color.h"
#include "src/hittable_list.h"
#include "src/ray.h"
#include "src/rtweekend.h"
#include "src/sphere.h"
#include "src/vec.h"

Color ray_color(const Ray& r, const Hittable& world) {
  HitRecord rec;
  if (world.Hit(r, 0, infinity, rec)) {
    return Color(0.5 * (rec.normal + Vec3(1.0, 1.0, 1.0)));
  }
  Vec unit_direction = unit_vector(r.direction());
  auto t = 0.5 * (unit_direction.Y() + 1.0);
  return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

int main() {
  // Image
  const auto aspect_ratio = 16.0 / 9.0;
  const int image_width = 400;
  const int image_height = static_cast<int>(image_width / aspect_ratio);

  // World
  HittableList world;
  world.add(std::make_shared<Sphere>(Point(0.0, 0.0, -1.0), 0.5));
  world.add(std::make_shared<Sphere>(Point(0.0, -100.5, -1.0), 100));

  // Camera
  auto viewport_height = 2.0;
  auto viewport_width = aspect_ratio * viewport_height;
  auto focal_length = 1.0;

  auto origin = Point(0.0, 0.0, 0.0);
  auto horizontal = Vec3(viewport_width, 0.0, 0.0);
  auto vertical = Vec3(0.0, viewport_height, 0.0);
  auto lower_left_corner =
      origin - horizontal / 2 - vertical / 2 - Vec3(0.0, 0.0, focal_length);

  // Render
  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (int j = image_height - 1; j >= 0; --j) {
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < image_width; ++i) {
      auto u = double(i) / (image_width - 1);
      auto v = double(j) / (image_height - 1);
      Ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
      Color pixel_color = ray_color(r, world);
      write_color(std::cout, pixel_color);
    }
  }
  std::cerr << "\nDone.\n";
}
