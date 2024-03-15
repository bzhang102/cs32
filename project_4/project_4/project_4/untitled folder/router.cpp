#include "router.h"
#include "geopoint.h"
#include "geotools.h"
#include "hashmap.h"

#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

vector<GeoPoint> Router::route(const GeoPoint& pt1, const GeoPoint& pt2) const {
    HashMap<string> cameFrom;
    HashMap<double> cost;
    
    // Instantiate priority queue with custom comparision struct
    CompareGeoPoint comp(cost, pt2);
    priority_queue<GeoPoint, vector<GeoPoint>, CompareGeoPoint> frontier(comp);
    
    // push initial point on and initialize in maps
    frontier.push(pt1);
    cameFrom[pt1.to_string()] = "";
    cost[pt1.to_string()] = 0;

    bool found = false;

    // while target is not reached and there are still paths to traverse
    while(!found && !frontier.empty()) {
        // get current point
        GeoPoint cur = frontier.top();
        frontier.pop();
        
        // for each of the connected points
        for(const auto& next : m_db.get_connected_points(cur)) {
            // calculate cost of getting to next node using it's current path length plus the heuristic
            double newCost = cost[cur.to_string()] + distance_earth_miles(cur, next);
            // if this point hasn't been visited yet and its new cost is lower than the cost before
            if(cost.find(next.to_string()) == nullptr || newCost < cost[next.to_string()]) {
                // reassign to new cost
                cost[next.to_string()] = newCost;
                // log path
                cameFrom[next.to_string()] = cur.to_string();
                // push point to visit next
                frontier.push(next);
            }

            // if found break
            if(next.to_string() == pt2.to_string()) {
                found = true;
                break;
            }
        }
    }
    vector<GeoPoint> route;
    // if route exists, return route in reverse order
    if(cameFrom.find(pt2.to_string()) != nullptr) {
        makeRoute(pt2.to_string(), 0, cameFrom, route);
    }
    return route;
}

// recursively add waypoints to route starting from the end (map gives points in reverse order)
void Router::makeRoute(const string& cur, int size, const HashMap<string>& map, vector<GeoPoint>& route) const {
    if(cur == "") return;
    makeRoute(*map.find(cur), size + 1, map, route);
    route.push_back(GeoPoint(cur.substr(0, cur.find(',')), cur.substr(cur.find(',') + 1)));
}
