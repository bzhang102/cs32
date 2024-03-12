#include "geodb.h"
#include <iostream>

using namespace std;

int main() {
    GeoDatabase geodb;
    geodb.load("/Users/brandon/IDEs/XCode/cs_32/project_4/project_4/project_4/provided/mapdata.txt");

    GeoPoint p;
    if (geodb.get_poi_location("Diddy Riese", p))
        cout << "The PoI is at " << p.sLatitude << ", "
        << p.sLongitude << endl;
    else
        cout << "PoI not found!\n";

    // testing get_street_name
    GeoPoint p1("34.0732851", "-118.4931016");
    GeoPoint p2("34.0736122", "-118.4927669");
    cout << geodb.get_street_name(p1, p2) << endl;
    cout << geodb.get_street_name(p2, p1) << endl;

    // testing get_connected_points
    std::vector<GeoPoint> pts = geodb.get_connected_points(GeoPoint("34.0736122", "-118.4927669"));
    if (pts.empty())
        cout << "There are no points connected to your specified point\n";
    else{
        for(const auto& p: pts)
            cout << p.sLatitude << ", " << p.sLongitude << endl;
    }
    cout << endl;

    std::vector<GeoPoint> pts2 = geodb.get_connected_points(GeoPoint("34.0601422", "-118.4468929"));
    if (pts2.empty())
        cout << "There are no points connected to your specified point\n";
    else{
        for(const auto& p: pts2)
            cout << p.sLatitude << ", " << p.sLongitude << endl;
    }
    cout << endl;

    std::vector<GeoPoint> pts3 = geodb.get_connected_points(GeoPoint("34.0600768", "-118.4467216"));
    if (pts3.empty())
        cout << "There are no points connected to your specified point\n";
    else{
        for(const auto& p: pts3)
            cout << p.sLatitude << ", " << p.sLongitude << endl;
    }
}
