#include "Dust.hpp"

Dust::Dust(const Point& center, const Velocity& velocity)
    : center_{center}, velocity_{velocity} {}
void Dust::setVelocity(const Velocity& velocity) {
    velocity_ = velocity;
}
Velocity Dust::getVelocity() const {
    return velocity_;
}
void Dust::draw(Painter& painter) const {
    painter.draw(center_, radius_, color_);
}
void Dust::setCenter(const Point& center) {
    center_ = center;
}
Point Dust::getCenter() const {
    return center_;
}