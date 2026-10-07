#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(CatWorld* world) {
  auto side = world->getWorldSideSize() / 2;

  Point2D start = {0,0};

  if (world->getCat() == start) {
    return {side, side - 1};
  }

  auto path = generatePath(world);

  if (!path.empty()) {
    Point2D spot = path.front();

    float distX = glm::distance((float)world->getCat().x, (float)spot.x);
    float distY = glm::distance((float)world->getCat().y, (float)spot.y);

    if (distX > 2 && distY > 2) {
      spot = *(path.begin() + 3);
    }

    if (world->catcherCanMoveToPosition(spot)) {
      world->lastMove = spot;
      return spot;
    }
  }


  return {Random::Range(0, side), Random::Range(0, side)};
}
