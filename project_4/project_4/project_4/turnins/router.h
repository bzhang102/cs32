#ifndef ROUTER_H
#define ROUTER_H

#include "geodb.h"
#include "base_classes.h"

class Router: public RouterBase {
public:
    Router(const GeoDatabaseBase& geo_db) : m_db(&geo_db) {}
    virtual ~Router() { delete m_db; }
    virtual std::vector<GeoPoint> route(const GeoPoint& pt1, const GeoPoint& pt2) const;
private:
    const GeoDatabaseBase* m_db;
};

#endif
