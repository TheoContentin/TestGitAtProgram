#pragma once

class PointDist {
public:
    PointDist(int i0, int j0, double dist0)
    : i(i0), j(j0), dist(dist0) {}
    int i,j;
    double dist;

    bool operator<(PointDist p) const {
        return (dist<p.dist);
    }

    bool operator>(PointDist p) const {
        return (dist>p.dist);
    }

};
