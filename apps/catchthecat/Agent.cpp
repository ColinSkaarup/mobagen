#include "Agent.h"
#include <climits>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include "World.h"

using namespace std;

static vector<Point2D> getVisitableNeighbors(const CatWorld* w, const Point2D cat, const unordered_map<Point2D, bool>& visited, const unordered_set<Point2D>& frontierSet) {
  vector<Point2D> neighbors;

  for (const Point2D point : CatWorld::neighbors(cat)) {
    if (!w->isValidPosition(point)) continue;
    if (point == cat) continue;
    if (w->getContent(point)) continue;
    if (visited.at(point)) continue;
    if (frontierSet.count(point) == 1) continue;
    neighbors.push_back(point);
  }
}

std::vector<Point2D> Agent::generatePath(CatWorld* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  queue<Point2D> frontier;                   // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results

  // bootstrap state
  auto catPos = w->getCat();
  frontier.emplace(catPos);
  frontierSet.insert(catPos);
  Point2D infinity = {INT32_MAX, INT32_MAX};
  Point2D borderExit = infinity;  // sentinel: no border found yet


  while (!frontier.empty()) {
    // get the current from frontier
    // remove the current from frontierset
    // mark current as visited
    // getVisitableNeightbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    // iterate over the neighs:
    // for every neighbor set the cameFrom
    // enqueue the neighbors to frontier and frontierset
    // do this up to find a visitable border and break the loop

    Point2D current = frontier.front();
    frontierSet.erase(current);
    visited.at(current) = true;

    vector<Point2D> neighbors = getVisitableNeighbors(w, current, visited, frontierSet);

    for (Point2D neigh : neighbors) {
      cameFrom.at(neigh) = current;
      frontier.push(neigh);
      frontierSet.insert(neigh);

      //neighbor is border
      if (w->catWinsOnSpace(neigh)) {
        borderExit = neigh;
        break;
      }
    }
  }

  // if the border is not infinity, build the path from border to the cat using the camefrom map
  // if there isnt a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
  if (borderExit != infinity) {
    vector<Point2D> path;
    Point2D current = borderExit;
    while (current != catPos) {
      path.push_back(current);
      current = cameFrom.at(current);
    }

    return path;
  }
  return vector<Point2D>();
}
