#include "Agent.h"
#include <climits>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include "World.h"
#include <utility>

//std::priority_queue<std::pair<float, Point2D>, std::vector<std::pair<float, Point2D>>, std::greater<std::pair<float, Point2D>>>;

using namespace std;

static vector<Point2D> getVisitableNeighbors(const CatWorld* w, const Point2D cat, unordered_map<Point2D, bool>& visited, const unordered_set<Point2D>& frontierSet) {
  vector<Point2D> neighbors;

  for (const Point2D point : CatWorld::neighbors(cat)) {
    if (!w->isValidPosition(point)) continue;
    if (point == cat) continue;
    if (w->getContent(point)) continue;
    if (visited[point]) continue;
    if (frontierSet.count(point) == 1) continue;
    neighbors.push_back(point);
  }
  return neighbors;
}

inline int heuristic(Point2D p1, int sideSize) {
  return min((sideSize/2 - abs(p1.x)), (sideSize/2 - abs(p1.y)));
}

std::vector<Point2D> Agent::generatePath(CatWorld* w) {
  //based on https://www.redblobgames.com/pathfinding/a-star/implementation.html
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  unordered_map<Point2D, float> accumCost;

  priority_queue<
    pair<float ,Point2D>,
    vector<pair<float,Point2D>>,
    greater<pair<float,Point2D>>
  > frontier;                   // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results

  // bootstrap state
  Point2D catPos = w->getCat();
  frontier.emplace(0, catPos);
  frontierSet.insert(catPos);
  cameFrom[catPos] = catPos;
  accumCost[catPos] = 0;

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

    Point2D current = frontier.top().second;
    frontier.pop();
    frontierSet.erase(current);
    visited[current] = true;

    vector<Point2D> neighbors = getVisitableNeighbors(w, current, visited, frontierSet);

    for (Point2D neigh : neighbors) {
      cameFrom[neigh] = current;

      //neighbor is border, early exit
      if (w->catWinsOnSpace(neigh)) {
        borderExit = neigh;
        break;
      }

      float newCost = accumCost[current] + 1; //each cell has weight 1
      if (accumCost.find(neigh) == accumCost.end() || newCost < accumCost[neigh]) {
        accumCost[neigh] = newCost;
        float priority = newCost + heuristic(neigh, w->getWorldSideSize());
        frontier.emplace(priority, neigh);
        frontierSet.insert(neigh);
      }

    }
    if (borderExit.x != INT32_MAX)
      break;
    }


  if (borderExit.x == INT32_MAX) return {};
  // if the border is not infinity, build the path from border to the cat using the camefrom map
  // if there isnt a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
  //if (borderExit != infinity) {
    vector<Point2D> path;
    Point2D current = borderExit;
    while (current != catPos) {
      path.push_back(current);
      current = cameFrom.at(current);
    }

    return path;
}
