#include "HuntAndKillExample.h"
#include "../World.h"
#include "../SeededRandom.h"
#include "Random.h"
#include <climits>
bool HuntAndKillExample::Step(World* w) {
  // todo: code this


  Point2D nothing = {INT_MAX, INT_MAX};
  for (auto point : stack) {
    if (point == nothing) {
      return false;
    }
  }


  if (stack.empty()) { return false; }

  Point2D current = stack.back();

  visited[CoordsToIndex(w, current.x, current.y)] = true;
  w->SetNodeColor(current, Color::Purple);

  std::vector<Point2D> neighbors = getVisitables(w, current);

  if (neighbors.empty()) {
    stack.pop_back();
    stack.push_back(randomStartPoint(w));
    return true;
  }
  //if only one neighbor, pick that one
  Point2D newPoint = neighbors[0];

  if (neighbors.size() > 1) {
    newPoint = neighbors[SeededRandom::next() % neighbors.size()];
  }

  int deltaX = newPoint.x - current.x;
  int deltaY = newPoint.y - current.y;

  if (deltaY < 0) { //North
    w->SetNorth(current, false);
  }
  else if (deltaX > 0) { //East
    w->SetEast(current, false);
  }
  else if (deltaY > 0) { //South
    w->SetSouth(current, false);
  }
  else if (deltaX < 0) { //West
    w->SetWest(current, false);
  }

  w->SetNodeColor(newPoint, Color::Green);

  stack.push_back(newPoint);

  return !stack.empty();
}
void HuntAndKillExample::Clear(World* world) {
  visited.clear();
  stack.clear();

  visited.assign(world->GetWidth() * world->GetHeight(), false);
  stack.push_back({0, 0});
}
Point2D HuntAndKillExample::randomStartPoint(World* world) {
  // Todo: improve this if you want
  for (int y = 0; y < world->GetHeight(); y++)
    for (int x = 0; x < world->GetWidth(); x++)
      if (!visited[CoordsToIndex(world, x, y)]) return {x, y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> HuntAndKillExample::getVisitables(World* w, const Point2D& p) {
  std::vector<Point2D> visitables;
  std::vector<Point2D> deltas = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

  // todo: code this
  for (uint8_t i = 0; i < 4; i++) {
    Point2D potentialPoint = p + deltas[i];

    if (potentialPoint.x >= 0 && potentialPoint.x < w->GetWidth()
      && potentialPoint.y >= 0 && potentialPoint.y < w->GetHeight()
      && !visited[CoordsToIndex(w, potentialPoint.x, potentialPoint.y)]) {
      visitables.push_back(potentialPoint);
      }
  }

  return visitables;
}
std::vector<Point2D> HuntAndKillExample::getVisitedNeighbors(World* w, const Point2D& p) {
  std::vector<Point2D> deltas = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
  std::vector<Point2D> neighbors;

  // todo: code this

  for (uint8_t i = 0; i < 4; i++) {
    Point2D potentialPoint = p + deltas[i];

    if (potentialPoint.x >= 0 && potentialPoint.x < w->GetWidth()
      && potentialPoint.y >= 0 && potentialPoint.y < w->GetHeight()
      && visited[CoordsToIndex(w, potentialPoint.x, potentialPoint.y)]) {
      neighbors.push_back(potentialPoint);
      }
  }

  return neighbors;
}
