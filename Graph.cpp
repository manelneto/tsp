//
// Created by manue on 08/05/2023.
//

#include "Graph.h"

Vertex *Graph::findVertex(const unsigned &id) const {
    if (id >= vertexSet.size())
        return nullptr;
    return vertexSet[id];
}

bool Graph::addVertex(const unsigned &id, const double &longitude, const double &latitude) {
    if (findVertex(id))
        return false;
    vertexSet.push_back(new Vertex(id, longitude, latitude));
    return true;
}

bool Graph::addEdge(const unsigned &orig, const unsigned &dest, const double &distance) {
    Vertex * v1 = findVertex(orig);
    Vertex * v2 = findVertex(dest);
    if (!v1 || !v2)
        return false;
    v1->addEdge(v2, distance);
    return true;
}

unsigned Graph::size() {
    return vertexSet.size();
}

void Graph::clear() {
    for (auto v: vertexSet)
        v->removeOutgoingEdges();
    vertexSet.clear();
}
