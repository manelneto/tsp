//
// Created by manue on 08/05/2023.
//

#include "Vertex.h"

Vertex::Vertex(unsigned id, double longitude, double latitude) : id(id), longitude(longitude), latitude(latitude) {}

unsigned Vertex::getId() const {
    return this->id;
}

double Vertex::getLongitude() const {
    return this->longitude;
}

double Vertex::getLatitude() const {
    return this->latitude;
}

Edge *Vertex::addEdge(Vertex *dest, double distance) {
    Edge * newEdge = new Edge(this, dest, distance);
    adj.push_back(newEdge);
    dest->incoming.push_back(newEdge);
    return newEdge;
}

const Edge * Vertex::getEdge(Vertex * vertex) const {
    for (const Edge * edge : adj)
        if (edge->getDest()->getId() == vertex->getId())
            return edge;
    return nullptr;
}

void Vertex::removeOutgoingEdges() {
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        it = adj.erase(it);
        deleteEdge(edge);
    }
}

void Vertex::deleteEdge(Edge *edge) const {
    Vertex *dest = edge->getDest();
    auto it = dest->incoming.begin();
    while (it != dest->incoming.end())
        if ((*it)->getOrig()->getId() == id)
            it = dest->incoming.erase(it);
        else
            it++;
    delete edge;
}
