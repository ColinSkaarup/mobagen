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

    //cat is potentially in tunnel
    if (path.size() > 6) {
      spot = *(path.end() - 1);
    }
    else if (distX > 2 && distY > 2) {
      spot = *(path.begin() + 1);
    }

    if (world->catcherCanMoveToPosition(spot)) {
      world->lastMove = spot;
      return spot;
    }
  }

  //cat is caught
  Point2D randomPoint = {Random::Range(-side, side), Random::Range(-side, side)};
  do {
    if (world->catcherCanMoveToPosition(randomPoint)) {
      return randomPoint;
    }
    randomPoint = {Random::Range(-side, side), Random::Range(-side, side)};
  } while (!world->catCanMoveToPosition(randomPoint));
}
