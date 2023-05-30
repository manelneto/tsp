//
// Created by manue on 08/05/2023.
//

#include "Graph.h"

#include <limits>

using namespace std;

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

bool Graph::addEdge(const unsigned &orig, const unsigned &dest, const double &distance) const {
    Vertex * v1 = findVertex(orig);
    Vertex * v2 = findVertex(dest);
    if (!v1 || !v2)
        return false;
    v1->addEdge(v2, distance);
    v2->addEdge(v1, distance);
    return true;
}

unsigned Graph::size() const {
    return vertexSet.size();
}

void Graph::clear() {
    for (auto v: vertexSet)
        v->removeOutgoingEdges();
    vertexSet.clear();
}

double Graph::tspBacktracking(unsigned path[]) const {
    unsigned currentPath[vertexSet.size()];
    double minDist = numeric_limits<unsigned>::max();
    currentPath[0] = 0;
    tspBacktracking(1, 0, currentPath, minDist, path);
    return minDist;
}

void Graph::tspBacktracking(unsigned currentIndex, double currentDist, unsigned currentPath[], double &minDist, unsigned path[]) const {
    unsigned size = vertexSet.size();
    const Edge * edge;
    if (currentIndex == size && (edge = findVertex(currentPath[size - 1])->getEdge(findVertex(currentPath[0])))) {
        currentDist += edge->getDistance();
        if (currentDist < minDist) {
            minDist = currentDist;
            for (unsigned i = 0; i < size; i++)
                path[i] = currentPath[i];
        }
    }
    for (unsigned i = 1; i < size; i++) {
        edge = findVertex(currentPath[currentIndex - 1])->getEdge(findVertex(i));
        if (edge && currentDist + edge->getDistance() < minDist) {
            bool unvisited = true;
            for (unsigned j = 1; j < currentIndex; j++)
                if (currentPath[j] == i) {
                    unvisited = false;
                    break;
                }
            edge = findVertex(currentPath[currentIndex - 1])->getEdge(findVertex(i));
            if (unvisited && edge) {
                currentPath[currentIndex] = i;
                tspBacktracking(currentIndex + 1, currentDist + edge->getDistance(), currentPath, minDist, path);
            }
        }
    }
}
