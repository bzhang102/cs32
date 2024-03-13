#include "router.h"
#include "geopoint.h"
#include "geotools.h"

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>

using namespace std;

vector<GeoPoint> Router::route(const GeoPoint& pt1, const GeoPoint& pt2) const {
    queue<GeoPoint> frontier;
    unordered_map<string, string> cameFrom;
    frontier.push(pt1);
    cameFrom[pt1.to_string()] = "";

    bool found = false;

    // populate map
    while(!found && !frontier.empty()) {
        GeoPoint cur = frontier.front();
        frontier.pop();

        for(const auto& next : m_db->get_connected_points(cur)) {
            if(cameFrom.find(next.to_string()) == cameFrom.end()) {
                frontier.push(next);
                cameFrom[next.to_string()] = cur.to_string();
            }
            if(next.to_string() == pt2.to_string()) {
                found = true;
                break;
            }
        }
    }

    vector<GeoPoint> route;
    // if route exists, return route in reverse order
    if(cameFrom.find(pt2.to_string()) != cameFrom.end()) {
        makeRoute(pt2.to_string(), 0, cameFrom, route);
    }
    return route;
}

void Router::makeRoute(const string& cur, int size, const unordered_map<string, string>& map, vector<GeoPoint>& route) const {
    if(cur == "") return;
    makeRoute(map.find(cur)->second, size + 1, map, route);
    route.push_back(GeoPoint(cur.substr(0, cur.find(',')), cur.substr(cur.find(',') + 1)));
}
