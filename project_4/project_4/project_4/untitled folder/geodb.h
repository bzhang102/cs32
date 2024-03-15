#ifndef GEODB_H
#define GEODB_H

#include "base_classes.h"
#include "geopoint.h"
#include "hashmap.h"

class GeoDatabase: public GeoDatabaseBase {
public:
    GeoDatabase() = default;
    virtual ~GeoDatabase() = default;
    virtual bool load(const std::string& map_data_file);
    virtual bool get_poi_location(const std::string& poi, GeoPoint& point) const;
    virtual std::vector<GeoPoint> get_connected_points(const GeoPoint& pt) const;
    virtual std::string get_street_name(const GeoPoint& pt1, const GeoPoint& pt2) const;
private:
    HashMap<GeoPoint> poiToPoint;
    HashMap<std::vector<GeoPoint>> pointToPoints;
    HashMap<std::string> pointsToName;

    void associate(std::string name, const GeoPoint& pt1, const GeoPoint& pt2);
    bool comp(const GeoPoint& pt1, const GeoPoint& pt2) {
        return pt1.to_string() == pt2.to_string();
    }
};
#endif
