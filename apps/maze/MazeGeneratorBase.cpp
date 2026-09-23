#include "MazeGeneratorBase.h"
#include "World.h"

int MazeGeneratorBase::CoordsToIndex(const World* w, const int x, const int y) const {
  return ((y * w->GetWidth()) + x);
}
