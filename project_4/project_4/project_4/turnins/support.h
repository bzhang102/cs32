#ifndef SUPPORT_H
#define SUPPORT_H

#include "geopoint.h"

struct StreetSegment {
    StreetSegment(std::string streetName, const GeoPoint& pt1, const GeoPoint& pt2) : name(streetName), endpoints(std::pair<GeoPoint, GeoPoint>(pt1, pt2)) {};
    std::string name;
    std::pair<GeoPoint, GeoPoint> endpoints;
};

bool comp(const GeoPoint& pt1, const GeoPoint& pt2) {
    return pt1.latitude == pt2.latitude && pt1.longitude == pt2.longitude;
}

bool comp(const StreetSegment& seg1, const StreetSegment& seg2) {
    GeoPoint pt11 = seg1.endpoints.first;
    GeoPoint pt12 = seg1.endpoints.second;
    GeoPoint pt21 = seg2.endpoints.first;
    GeoPoint pt22 = seg2.endpoints.second;

    return seg1.name == seg2.name && ((comp(pt11, pt21) && comp(pt12, pt22)) || (comp(pt11, pt22) && comp(pt12, pt21)));
}

#endif
