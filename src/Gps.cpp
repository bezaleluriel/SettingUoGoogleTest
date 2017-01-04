#include "Gps.h"
#include <stack>
#include <cmath>
#include "Grid.h"
#include "GridNode.h"
/**
 * constructor
 * @return
 */
Gps::Gps(){}
/**
 * constructor
 * @param map - our Structure*.
 * @return
 */
Gps::Gps(Structure *map) {
    Gps::map = map;
    bfs = Bfs(map);
}

std::stack<Point> Gps::findeShortersRoute(Point start, Point end) {
    bfs.setStart(start);
    bfs.setEnd(end);
    std::vector<Point> vec;
    vec = bfs.run();
    //todo this line get the hell the 0,0 point
    vec.erase(vec.begin());
    while(vec.size()) {
    gpsStack.push(vec.back());
    vec.pop_back();
      //  gpsStack.push(vec.front());
      //  vec.erase(vec.begin());
    }
    return gpsStack;
}
