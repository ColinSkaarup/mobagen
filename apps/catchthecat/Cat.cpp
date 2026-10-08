#include "Cat.h"
#include "World.h"
#include <stdexcept>

Point2D Cat::Move(CatWorld* world) {

  auto path = generatePath(world);
  if (!path.empty()) {
    const Point2D spot = path.back();
    if (world->catCanMoveToPosition(spot)) {
      world->lastMove = spot;
      return spot;
    }
  }

  //trapped
  auto rand = Random::Range(0, 5);
  auto pos = world->getCat();
  switch (rand) {
    case 0:
      if (world->catCanMoveToPosition(CatWorld::NE(pos)))
        return CatWorld::NE(pos);
    case 1:
      if (world->catCanMoveToPosition(CatWorld::NW(pos)))
        return CatWorld::NW(pos);
    case 2:
      if (world->catCanMoveToPosition(CatWorld::E(pos)))
        return CatWorld::E(pos);
    case 3:
      if (world->catCanMoveToPosition(CatWorld::W(pos)))
        return CatWorld::W(pos);
    case 4:
      if (world->catCanMoveToPosition(CatWorld::SW(pos)))
        return CatWorld::SW(pos);
    case 5:
      if (world->catCanMoveToPosition(CatWorld::SE(pos)))
        return CatWorld::SE(pos);
    default:
      return CatWorld::SW(pos);
  }
}
