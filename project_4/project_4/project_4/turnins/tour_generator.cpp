#include "tour_generator.h"
#include "tourcmd.h"

#include <vector>

using namespace std;

vector<TourCommand> TourGenerator::generate_tour(const Stops& stops) const {
    vector<TourCommand> instructions;

    string nextPOI;
    string talkingPoints;
    stops.get_poi_data(0, nextPOI, talkingPoints);
    for(int i = 0; i < stops.size(); i++) {
        // make commentary
        TourCommand comment;
        comment.init_commentary(nextPOI, talkingPoints);
        instructions.push_back(comment);

        // check if end of tour
        if(i < stops.size() - 1) {
            // get start point
            GeoPoint start;
            m_db->get_poi_location(nextPOI, start);
            // find next poi
            stops.get_poi_data(i + 1, nextPOI, talkingPoints);
            // get endpoint
            GeoPoint end;
            m_db->get_poi_location(nextPOI, end);
            // get route
            vector<GeoPoint> route = m_router->route(start, end);

            
        }
    }

    return instructions;
}
