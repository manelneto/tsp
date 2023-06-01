//
// Created by manue on 08/05/2023.
//

#include "Edge.h"

Edge::Edge(Vertex *orig, Vertex *dest, double distance) : orig(orig), dest(dest), distance(distance) {}

bool Edge::operator<(const Edge &edge) const {
    return this->distance < edge.distance;
}

Vertex *Edge::getOrig() const {
    return this->orig;
}

Vertex *Edge::getDest() const {
    return this->dest;
}

double Edge::getDistance() const {
    return this->distance;
}
