#ifndef INPUT_HPP
#define INPUT_HPP
#include <iostream>
#include "base-types.hpp"
#include "shape.hpp"
namespace arakelyan
{
  char * inputString(std::istream &input);
  void freeMem(Shape ** shapes, const char * string, const size_t shapesCount);
  void inputScaleParam(const char *string, point_t &point, double &k);
}
#endif
