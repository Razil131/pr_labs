#pragma once
#include <iostream>

class Color {
  public:
    Color();
    Color(double red, double green, double blue);
    double red() const;
    double green() const;
    double blue() const;
    inline friend std::istream& operator>>(std::istream& stream, Color& color) {
        return stream >> color.r >> color.g >> color.b;
    }

  private:
    double r{};
    double g{};
    double b{};
};
