#include "square.hpp"
#include <stdexcept>
#include "baseTypes.hpp"

agarkov::Square::Square(agarkov::point_t left_bottom, double length):
  left_bottom_(left_bottom),
  length_(length)
{
  if (!isCorrectSquare())
  {
    throw std::invalid_argument("Incorrect square argument");
  }
}

double agarkov::Square::getArea() const
{
  return (length_ * length_);
}

agarkov::rectangle_t agarkov::Square::getFrameRectangle() const
{
  point_t center = {left_bottom_.x_ + length_ / 2, left_bottom_.y_ + length_ / 2};
  return {center, length_, length_};
}

void agarkov::Square::move(double dx, double dy)
{
  left_bottom_.move(dx, dy);
}

void agarkov::Square::move(point_t position)
{
  double dx = position.x_ - (left_bottom_.x_ + length_ / 2);
  double dy = position.y_ - (left_bottom_.y_ + length_ / 2);
  move(dx, dy);
}

void agarkov::Square::scale(double k)
{
  if (k <= 0)
  {
    throw std::invalid_argument("Incorrect scale coefficient");
  }
  point_t center = getFrameRectangle().pos_;
  left_bottom_.unsaveScale(center, k);
  length_ *= k;
}

bool agarkov::Square::isCorrectSquare()
{
  return length_ > 0;
}
