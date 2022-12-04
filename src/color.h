#ifndef SRC_COLOR_H
#define SRC_COLOR_H

#include <iostream>

#include "src/vec.h"

void write_color(std::ostream &out, Color pixel_color) {
  // Write the translated [0,255] value of each color component.
  out << static_cast<int>(255.999 * pixel_color.R()) << ' '
      << static_cast<int>(255.999 * pixel_color.G()) << ' '
      << static_cast<int>(255.999 * pixel_color.B()) << '\n';
}

#endif  // SRC_COLOR_H