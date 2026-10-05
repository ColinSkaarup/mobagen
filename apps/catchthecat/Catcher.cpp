#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(CatWorld* world) {
  auto side = world->getWorldSideSize() / 2;

  for (;;) {
    auto path = generatePath(world);

    return path.front();
  }

  // for (;;) {
  //   Point2D p = path.front();
  //   auto cat = world->getCat();
  //   if (cat.x != p.x && cat.y != p.y && !world->getContent(p)) return p;
  // }
}
