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

    frontier.push(pt1);
    cameFrom[pt1.to_string()] = "";
    cost[pt1.to_string()] = 0;

    bool found = false;

    while(!found && !frontier.empty()) {
        GeoPoint cur = frontier.top();
        frontier.pop();

        for(const auto& next : m_db.get_connected_points(cur)) {
            double newCost = cost[cur.to_string()] + distance_earth_miles(cur, next);
            if(cost.find(next.to_string()) == nullptr || newCost < cost[next.to_string()]) {
                cost[next.to_string()] = newCost;
                cameFrom[next.to_string()] = cur.to_string();
                frontier.push(next);
            }

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

void Router::makeRoute(const string& cur, int size, const HashMap<string>& map, vector<GeoPoint>& route) const {
    if(cur == "") return;
    makeRoute(*map.find(cur), size + 1, map, route);
    route.push_back(GeoPoint(cur.substr(0, cur.find(',')), cur.substr(cur.find(',') + 1)));
}
