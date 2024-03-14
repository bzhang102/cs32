#ifndef ROUTER_H
#define ROUTER_H

#include "geodb.h"
#include "base_classes.h"
#include "geotools.h"
#include "hashmap.h"

#include <vector>

class Router: public RouterBase {
public:
    Router(const GeoDatabaseBase& geo_db) : m_db(geo_db) {}
    virtual ~Router() = default;
    virtual std::vector<GeoPoint> route(const GeoPoint& pt1, const GeoPoint& pt2) const;
private:
    const GeoDatabaseBase& m_db;
    void makeRoute(const std::string& cur, int size, const HashMap<std::string>& map, std::vector<GeoPoint>& route) const;
};

class CompareGeoPoint {
public:
    CompareGeoPoint(const HashMap<double>& cost, const GeoPoint& end) : m_cost(cost), m_end(end) {}
    bool operator()(const GeoPoint& pt1, const GeoPoint& pt2) {
        return *m_cost.find(pt1.to_string()) + distance_earth_miles(pt1, m_end) > *m_cost.find(pt2.to_string()) + distance_earth_miles(pt1, m_end);
    }
private:
    const HashMap<double>& m_cost;
    const GeoPoint& m_end;
};
#endif
