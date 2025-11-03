#include "World.h"
#include "Painter.h"
#include <fstream>

// Длительность одного тика симуляции.
// Подробнее см. update()
// Изменять не следует
static constexpr double timePerTick = 0.001;

/**
 * Конструирует объект мира для симуляции
 * @param worldFilePath путь к файлу модели мира
 */
World::World(const std::string& worldFilePath) {

    std::ifstream stream(worldFilePath);
    stream >> topLeft.x >> topLeft.y >> bottomRight.x >> bottomRight.y;
    physics.setWorldBox(topLeft, bottomRight);

    Point pos;
    Velocity vel;
    Color color;
    double radius;
    bool isCollidable;

    while (stream >> pos >> vel >> color >> radius >> std::boolalpha >>
           isCollidable) {
        balls.emplace_back(pos, radius, vel, color, isCollidable);
    }
}

/// @brief Отображает состояние мира
void World::show(Painter& painter) const {
    // Рисуем белый прямоугольник, отображающий границу
    // мира
    painter.draw(topLeft, bottomRight, Color(1, 1, 1));

    for (const Dust& dust : physics.dusts) {
        dust.draw(painter);
    }

    // Вызываем отрисовку каждого шара
    for (const Ball& ball : balls) {
        ball.draw(painter);
    }
}

/// @brief Обновляет состояние мира
void World::update(double time) {
    /**
     * В реальном мире время течет непрерывно. Однако
     * компьютеры дискретны по своей природе. Поэтому
     * симуляцию взаимодействия шаров выполняем дискретными
     * "тиками". Т.е. если с момента прошлой симуляции
     * прошло time секунд, time / timePerTick раз обновляем
     * состояние мира. Каждое такое обновление - тик -
     * в physics.update() перемещаем шары и обрабатываем
     * коллизии - ситуации, когда в результате перемещения
     * один шар пересекается с другим или с границей мира.
     * В общем случае время не делится нацело на
     * длительность тика, сохраняем остаток в restTime
     * и обрабатываем на следующей итерации.
     */

    // учитываем остаток времени, который мы не "доработали" при прошлом update
    time += restTime;
    const auto ticks = static_cast<size_t>(std::floor(time / timePerTick));
    restTime = time - double(ticks) * timePerTick;

    physics.update(balls, ticks);
    for (size_t i = 0; i < ticks; ++i) {
        std::vector<Dust> alive{};
        for (Dust& dust : physics.dusts) {
            dust.lifetime_ -= timePerTick;
            if (dust.lifetime_ > 0) {
                dust.setCenter(dust.getCenter() +
                               dust.getVelocity().vector() * timePerTick);
                alive.push_back(dust);
            }
        }
        physics.dusts = alive;
    }
}