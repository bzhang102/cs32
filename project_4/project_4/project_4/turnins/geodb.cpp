#include "geodb.h"
#include "geotools.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

bool GeoDatabase::load(const std::string& map_data_file) {
    ifstream infile(map_data_file);
    if(!infile) return false;

    string street;
    string line;
    string lat1, lon1, lat2, lon2;
    string name;
    while(true) {
        // get street segment data
        if(!getline(infile, street)) { break; }
        if(!getline(infile, line)) { break; }
        istringstream iss(line);
        iss >> lat1 >> lon1 >> lat2 >> lon2;

        // make endpoints
        GeoPoint p1(lat1, lon1);
        GeoPoint p2(lat2, lon2);

        // handle any pois
        int pois;
        if(!(infile >> pois)) { break; }
        if(pois > 0) {
            // associate both endpoints with the midpoint
            GeoPoint mid =  midpoint(p1, p2);
            associate(name, p1, mid);
            associate(name, p2, mid);

            // load each poi
            for(int i = 0; i < pois; i++) {
                // get poi data
                getline(infile, line);
                name = line.substr(0, line.find('|'));
                line.erase(0, name.size() + 1);
                lat1 = line.substr(0, line.find(' '));
                line.erase(0, lat1.size() + 1);
                lat2 = line;

                // make new geopoint representing poi
                GeoPoint poi(lat1, lat2);

                // associate poi with geopoint
                poiToPoint.insert(name, poi);

                // make new street segment connecting midpoint with
                associate("path", poi, mid);
            }
        // no pois
        } else {
            // make new street segment connecting both points (bidirectional)
            associate(name, p1, p2);
        }
    }

    return true;
}

bool GeoDatabase::get_poi_location(const std::string& poi, GeoPoint& point) const {
    const GeoPoint* location = poiToPoint.find(poi);
    if(location == nullptr) return false;
    point = *location;
    return true;
}

std::vector<GeoPoint> GeoDatabase::get_connected_points(const GeoPoint& pt) const {
    // obtain segments associated with point
    const vector<StreetSegment>* segments = pointToSegments.find(pt.to_string());
    // populate result with second endpoint of each line segment
    vector<GeoPoint> result(segments->size());
    for(int i = 0; i < segments->size(); i++) {
        result[i] = (*segments)[i].endpoints.second;
    }
    return result;
}

std::string GeoDatabase::get_street_name(const GeoPoint& pt1, const GeoPoint& pt2) const {
    const vector<StreetSegment>* segments = pointToSegments.find(pt1.to_string());
    for(auto& segment : *segments) {
        if(segment.endpoints.second.to_string() == pt2.to_string()) {
            return segment.name;
        }
    }
    // hopefully never executed
    return "";
}

void GeoDatabase::associate(std::string name, const GeoPoint &pt1, const GeoPoint &pt2) {
    // make new street segment
    StreetSegment seg(name, pt1, pt2);
    // get segments associated with p1
    vector<StreetSegment>* segments1 = pointToSegments.find(pt1.to_string());
    // p1 exists
    if(segments1 != nullptr) {
        // see if segment already exists within
        for(auto it = segments1->begin(); it != segments1->end(); it++) {
            // segment exists
            if(comp(seg, *it)) return;
        }
        // segment doesn't exist
        segments1->push_back(seg);
    // p1 doesn't exist
    } else {
        vector<StreetSegment> newVec;
        newVec.push_back(seg);
        pointToSegments.insert(pt1.to_string(), newVec);
    }

    // get segments associated with p2
    vector<StreetSegment>* segments2 = pointToSegments.find(pt2.to_string());
    // p2 exists
    if(segments2 != nullptr) {
        // see if segment already exists within
        for(auto it = segments2->begin(); it != segments2->end(); it++) {
            // segment exists
            if(comp(seg, *it)) return;
        }
        // segment doesn't exist
        segments2->push_back(seg);
        // p1 doesn't exist
    } else {
        vector<StreetSegment> newVec;
        newVec.push_back(seg);
        pointToSegments.insert(pt2.to_string(), newVec);
    }
}
