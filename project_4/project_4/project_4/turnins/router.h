#ifndef ROUTER_H
#define ROUTER_H

#include "geodb.h"
#include "base_classes.h"

#include <vector>
#include <unordered_map>

class Router: public RouterBase {
public:
    Router(const GeoDatabaseBase& geo_db) : m_db(&geo_db) {}
    virtual ~Router() = default;
    virtual std::vector<GeoPoint> route(const GeoPoint& pt1, const GeoPoint& pt2) const;
private:
    const GeoDatabaseBase* m_db;
    
    void makeRoute(const std::string& cur, int size, const std::unordered_map<std::string, std::string>& map, std::vector<GeoPoint>& route) const;
};

#endif
