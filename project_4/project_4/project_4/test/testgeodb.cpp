#include "geodb.h"
#include "geopoint.h"
#include <iostream>

int main() {
    GeoDatabase db;
    db.load("/Users/brandon/IDEs/XCode/cs_32/project_4/project_4/project_4/provided/mapdata.txt");
    GeoPoint pt;
    db.get_poi_location("a", pt);
    std::cerr << db.get_street_name(pt, GeoPoint("1.0000000", "1.0000000")) << std::endl;
}
