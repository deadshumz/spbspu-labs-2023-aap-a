#include <iostream>
#include <string>
#include <cmath>
#include "base-types.hpp"
#include "shape.hpp"
#include "rectangle.hpp"
#include "ring.hpp"
#include "regular.hpp"
#include "circle.hpp"
#include "freeshapes.hpp"

int main()
{
  petuhov::Shape *shapes[1000] = {};
  size_t shapeCount = 0;
  std::string command;
  bool errorFlag = false;

  while (std::cin >> command && command != "SCALE")
  {
    try
    {
      if (command == "RECTANGLE")
      {
        double x1 = 0;
        double y1 = 0;
        double x2 = 0;
        double y2 = 0;
        std::cin >> x1 >> y1 >> x2 >> y2;
        double centerX = (x1 + x2) / 2;
        double centerY = (y1 + y2) / 2;
        double width = x2 - x1;
        double height = y2 - y1;
        shapes[shapeCount++] = new petuhov::Rectangle({centerX, centerY}, width, height);
      }
      else if (command == "RING")
      {
        double x = 0;
        double y = 0;
        double innerRadius = 0;
        double outerRadius = 0;
        std::cin >> x >> y >> outerRadius >> innerRadius;
        shapes[shapeCount++] = new petuhov::Ring({x, y}, outerRadius, innerRadius);
      }
      else if (command == "REGULAR")
      {
        double x = 0;
        double y = 0;
        double radius = 0;
        int vertexCount;
        std::cin >> x >> y >> radius >> vertexCount;
        if (radius <= 0 || vertexCount <= 2)
        {
          throw std::invalid_argument("Invalid parameters for REGULAR.");
        }
        shapes[shapeCount++] = new petuhov::Regular({x, y}, radius, vertexCount);
      }
      else if (command == "CIRCLE")
      {
        double x = 0;
        double y = 0;
        double radius = 0;
        std::cin >> x >> y >> radius;
        shapes[shapeCount++] = new petuhov::Circle({x, y}, radius);
      }
    }
    catch (const std::invalid_argument &e)
    {
      errorFlag = true;
    }
  }

  if (command == "SCALE")
  {
    double scale_factor = 0;
    petuhov::point_t scale_center = {0, 0};
    std::cin >> scale_center.x >> scale_center.y >> scale_factor;

    double totalAreaBefore = 0;
    double totalAreaAfter = 0;

    std::cout << std::fixed;
    std::cout.precision(1);

    // Вывод до масштабирования
    for (size_t i = 0; i < shapeCount; i++)
    {
      totalAreaBefore += shapes[i]->getArea();
      if (i == 0) {
        std::cout << totalAreaBefore;
      }
      petuhov::rectangle_t frame = shapes[i]->getFrameRect();
      std::cout << " " << frame.pos.x - frame.width / 2 << " " << frame.pos.y - frame.height / 2;
      std::cout << " " << frame.pos.x + frame.width / 2 << " " << frame.pos.y + frame.height / 2;
    }

    // Масштабирование
    std::cout << "\n";
    for (size_t i = 0; i < shapeCount; i++)
    {
      shapes[i]->scale(scale_factor);
      totalAreaAfter += shapes[i]->getArea();
    }

    // Вывод после масштабирования
    std::cout << totalAreaAfter;
    for (size_t i = 0; i < shapeCount; i++)
    {
      petuhov::rectangle_t frame = shapes[i]->getFrameRect();
      std::cout << " " << frame.pos.x - frame.width / 2 << " " << frame.pos.y - frame.height / 2;
      std::cout << " " << frame.pos.x + frame.width / 2 << " " << frame.pos.y + frame.height / 2;
    }
    std::cout << "\n";

    if (errorFlag)
    {
      std::cerr << "Errors were found in the description of some shapes." << std::endl;
    }
  }
  else
  {
    petuhov::freeShapes(shapes, shapeCount);
    std::cerr << "SCALE command is missing or invalid." << std::endl;
    return 2;
  }

  petuhov::freeShapes(shapes, shapeCount);

  return 0;
}
