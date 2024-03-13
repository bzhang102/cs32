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
//    GeoPoint pt1("34.0727114", "-118.3957365");
//    GeoPoint pt2("34.0701358", "-118.4457751");
//    vector<GeoPoint> route = router.route(pt1, pt2);
//
//    for(const auto& point : route) {
//        cerr << point.to_string() << endl;
//    }
//}
