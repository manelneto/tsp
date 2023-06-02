//
// Created by manue on 08/05/2023.
//

#include "Vertex.h"
#include <cmath>
#include <stdexcept>

using namespace std;

Vertex::Vertex(unsigned id, double longitude, double latitude) : id(id), longitude(longitude), latitude(latitude) {}

bool Vertex::operator<(const Vertex &vertex) const {
    return this->distance < vertex.distance;
}

unsigned Vertex::getId() const {
    return this->id;
}

double Vertex::getLongitude() const {
    return this->longitude;
}

double Vertex::getLatitude() const {
    return this->latitude;
}

multiset<Edge *, edgeCmp> Vertex::getAdj() const {
    return this->adj;
}

bool Vertex::isVisited() const {
    return this->visited;
}

double Vertex::getDistance() const {
    return this->distance;
}

Edge *Vertex::getPath() const {
    return this->path;
}

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

void Vertex::setDistance(double distance) {
    this->distance = distance;
}

void Vertex::setPath(Edge *path) {
    this->path = path;
}

Edge *Vertex::addEdge(Vertex *dest, double distance) {
    Edge * newEdge = new Edge(this, dest, distance);
    adj.insert(newEdge);
    dest->incoming.insert(newEdge);
    return newEdge;
}

Edge * Vertex::getEdge(const Vertex * vertex) const {
    for (Edge * edge : adj)
        if (edge->getDest()->getId() == vertex->getId())
            return edge;
    return nullptr;
}

void Vertex::dfsPreorder(vector<unsigned> &preorder) {
    this->visited = true;
    preorder.push_back(this->id);
    for (auto edge : this->adj) {
        auto v = edge->getDest();
        if (!v->isVisited())
            v->dfsPreorder(preorder);
    }
}

double Vertex::toRadians(double deg) {
    return deg * 3.1416/180;
}

double Vertex::calculateDistance(const Vertex *vertex) const {
    if (this->latitude == 0.0 && this->longitude == 0.0 && vertex->latitude == 0.0 && vertex->longitude == 0.0)
        throw invalid_argument("Coordenadas inválidas");
    double lat1 = toRadians(this->latitude);
    double lon1 = toRadians(this->longitude);
    double lat2 = toRadians(vertex->getLatitude());
    double lon2 = toRadians(vertex->getLongitude());
    double dLat = lat2 - lat1;
    double dLon = lon2 - lon1;
    double aux = pow(sin(0.5 * dLat), 2) + cos(lat1) * cos(lat2) * pow(sin(0.5 * dLon), 2);
    double c = 2.0 * atan2(sqrt(aux), sqrt(1.0 - aux));
    double r = 6371000;
    return r * c;
}

Edge *Vertex::getNearestNeighbor() const {
    for (Edge * edge : adj)
        if (!edge->getDest()->isVisited())
            return edge;
    return nullptr;
}
