#include "geodb.h"
#include "geopoint.h"
#include "geotools.h"
#include "hashmap.h"

#include <sstream>
#include <string>
#include <vector>

using namespace std;

// TODO: LOAD
bool GeoDatabase::load(const string& map_data_file) {
    // attempt to load data file
    ifstream infile(map_data_file);
    if(!infile) return false;

    // for each street segment
    while(true) {
        string street;
        string line;
        string lat1, lon1, lat2, lon2;
        // get street segment data
        if(!getline(infile, street)) { break; }
        if(!getline(infile, line)) { break; }
        istringstream iss(line);
        iss >> lat1 >> lon1 >> lat2 >> lon2;
        // make endpoints
        GeoPoint p1(lat1, lon1);
        GeoPoint p2(lat2, lon2);
        // make new street segment connecting both points (bidirectional)
        associate(street, p1, p2);
        // handle any pois
        int pois;
        if(!(infile >> pois)) { break; }
        infile.ignore(10000,'\n');
        //if any pois exist
        if(pois > 0) {
            // associate both endpoints with the midpoint
            GeoPoint mid = midpoint(p1, p2);
            associate(street, p1, mid);
            associate(street, p2, mid);
            // load each poi
            for(int i = 0; i < pois; i++) {
                string name;
                string lat, lon;
                // get poi data
                getline(infile, line);
                name = line.substr(0, line.find('|'));
                line.erase(0, name.size() + 1);
                lat = line.substr(0, line.find(' '));
                line.erase(0, lat1.size() + 1);
                lon = line;
                // make new geopoint representing poi
                GeoPoint poi(lat, lon);
                // associate poi with geopoint
                poiToPoint.insert(name, poi);
                // make new street segment connecting midpoint with
                associate("a path", poi, mid);
            }
        }
    }
    return true;
}

bool GeoDatabase::get_poi_location(const string& poi, GeoPoint& point) const {
    // find location in map
    const GeoPoint* location = poiToPoint.find(poi);
    // check for existence
    if(location == nullptr) return false;
    point = *location;
    return true;
}

vector<GeoPoint> GeoDatabase::get_connected_points(const GeoPoint& pt) const {
    // find all connected points in map
    const vector<GeoPoint>* points = pointToPoints.find(pt.to_string());
    // check if any exist
    return (points == nullptr) ? vector<GeoPoint>() : *points;
}

string GeoDatabase::get_street_name(const GeoPoint& pt1, const GeoPoint& pt2) const {
    // find street name in map
    const string* name = pointsToName.find(pt1.to_string() + "|" + pt2.to_string());
    // check for existence
    return (name == nullptr) ? "" : *name;
}

void GeoDatabase::associate(string name, const GeoPoint &pt1, const GeoPoint &pt2) {
    // get and insert into points associated with pt1
    pointToPoints[pt1.to_string()].push_back(pt2);
    pointToPoints[pt2.to_string()].push_back(pt1);
    //insert street name
    pointsToName.insert(pt1.to_string() + "|" + pt2.to_string(), name);
    pointsToName.insert(pt2.to_string() + "|" + pt1.to_string(), name);
}
