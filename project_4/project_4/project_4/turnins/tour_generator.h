#ifndef TOUR_GENERATOR_H
#define TOUR_GENERATOR_H

#include "base_classes.h"
#include "router.h"
#include "stops.h"
#include "tourcmd.h"

#include <vector>

class TourGenerator: public TourGeneratorBase
{
public:
    TourGenerator(const GeoDatabaseBase& geodb, const RouterBase& router) : m_router(&router), m_db(&geodb) {}
    virtual ~TourGenerator();
    virtual std::vector<TourCommand> generate_tour(const Stops& stops) const;
private:
    const RouterBase* m_router;
    const GeoDatabaseBase* m_db;
};
#endif
