#include "tour_generator.h"
#include "tourcmd.h"
#include "geotools.h"

#include <vector>

using namespace std;

vector<TourCommand> TourGenerator::generate_tour(const Stops& stops) const {
    vector<TourCommand> instructions;

    string nextPOI;
    string talkingPoints;
    stops.get_poi_data(0, nextPOI, talkingPoints);

    // MARK: TESTER (Comment out for submission)
    ofstream ofile("/Users/brandon/IDEs/XCode/cs_32/project_4/project_4/project_4/test/Route.txt");

    for(int i = 0; i < stops.size(); i++) {
        // make commentary
        TourCommand comment;
        comment.init_commentary(nextPOI, talkingPoints);
        instructions.push_back(comment);

        // check if end of tour
        if(i < stops.size() - 1) {
            // get start point
            GeoPoint start;
            m_db.get_poi_location(nextPOI, start);
            // find next poi
            stops.get_poi_data(i + 1, nextPOI, talkingPoints);
            // get endpoint
            GeoPoint end;
            m_db.get_poi_location(nextPOI, end);
            // get route
            vector<GeoPoint> route = m_router.route(start, end);
            for(int i = 0; i < route.size() - 1; i++) {
                GeoPoint& pt1 = route[i];
                GeoPoint& pt2 = route[i + 1];

                TourCommand proceed;
                proceed.init_proceed(getDirection(pt1, pt2), m_db.get_street_name(pt1, pt2), distance_earth_miles(pt1, pt2), pt1, pt2);
                instructions.push_back(proceed);

                // MARK: TESTER (Comment out for submission)
                if(i == 0) {
                    ofile << pt1.to_string() << endl;
                }
                ofile << pt2.to_string() << endl;

                if(i < route.size() - 2) {
                    GeoPoint& pt3 = route[i + 2];
                    if(m_db.get_street_name(pt1, pt2) != m_db.get_street_name(pt2, pt3)) {
                        double angle = angle_of_turn(pt1, pt2, pt3);
                        if(angle >= 1 && angle < 180) {
                            TourCommand turn;
                            turn.init_turn("left", m_db.get_street_name(pt2, pt3));
                            instructions.push_back(turn);
                        } else if(angle >= 180 && angle <= 359) {
                            TourCommand turn;
                            turn.init_turn("right", m_db.get_street_name(pt2, pt3));
                            instructions.push_back(turn);
                        }
                    }
                }
            }
        }
    }

    return instructions;
}

string TourGenerator::getDirection(const GeoPoint& pt1, const GeoPoint& pt2) const {
    double angle = angle_of_line(pt1, pt2);
    if(0 <= angle && angle < 22.5) {
        return "east";
    } else if(angle < 67.5) {
        return "northeast";
    } else if(angle < 112.5) {
        return "north";
    } else if(angle < 157.5) {
        return "northwest";
    } else if(angle < 202.5) {
        return "west";
    } else if(angle < 247.5) {
        return "southwest";
    } else if(angle < 292.5) {
        return "south";
    } else {
        return "southeast";
    }
}
