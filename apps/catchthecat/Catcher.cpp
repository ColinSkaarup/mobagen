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

    //cat is potentially in tunnel
    if (path.size() > 8) {
      spot = *(path.end() - 2);
    }
    else if (path.size() > 6) {
      spot = *(path.begin() + path.size() / 2);
    }
    else if (path.size() > 3) {
      spot = *(path.begin() + 2);
    }

    if (world->catcherCanMoveToPosition(spot)) {
      world->lastMove = spot;
      return spot;
    }
  }

  //cat is caught
  return {Random::Range(-side, side), Random::Range(-side, side)};
}
