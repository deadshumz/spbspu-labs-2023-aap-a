#ifndef INPUTSHAPESRC_HPP
#define INPUTSHAPESRC_HPP

#include <cstddef>
#include <istream>

#include "shape.hpp"

using shapeInputFunc = zhalilov::Shape *(*)(const char string[]);
namespace zhalilov
{
  Shape **inputShapesSource(point_t &point, double &ratio, size_t &length, size_t &size, std::istream &input);
  Shape **increaseLength(Shape **shapes, size_t size, size_t delta);
  void freeMemory(Shape **shapes, size_t size, const char string[]);
  shapeInputFunc identifyShape(const char string[]);
  bool inputScale(point_t &point, double &ratio, const char string[]);
  Shape *inputRectangle(const char string[]);
  Shape *inputCircle(const char string[]);
  Shape *inputPolygon(const char string[]);
}

#endif
