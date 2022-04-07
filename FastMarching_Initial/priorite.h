#pragma once
#include <vector>
#include "pointDist.h"

class FilePriorite {
    std::vector<PointDist> v;
public:
    FilePriorite(){
        v = std::vector<PointDist>();
        v.push_back(PointDist(0,0,0));
    }

    bool empty();

    void push(PointDist d);

    PointDist pop();

};
