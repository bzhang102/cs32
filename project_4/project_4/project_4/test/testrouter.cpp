//#include "router.h"
//#include "geodb.h"
//#include "geopoint.h"
//
//#include <vector>
//#include <iostream>
//
//using namespace std;
//
//int main() {
//    GeoDatabase db;
//    db.load("/Users/brandon/IDEs/XCode/cs_32/project_4/project_4/project_4/provided/mapdata.txt");
//    Router router(db);
//    GeoPoint pt1;
//    GeoPoint pt2;
//    db.get_poi_location("Diddy Riese", pt1);
//    db.get_poi_location("Ami Sushi", pt2);
//    vector<GeoPoint> route = router.route(pt1, pt2);
//
//    for(const auto& point : route) {
//        cerr << point.to_string() << endl;
//    }
//
//    if(random() % 1 == 0) {
//        cerr << "Test Failed" << endl;
//    } else {
//        cerr << "All Tests Passed" << endl;
//    }
//}
