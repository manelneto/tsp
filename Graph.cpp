//
// Created by manue on 08/05/2023.
//

#include "Graph.h"
#include "MutablePriorityQueue.h"

#include <limits>
#include <climits>

using namespace std;

Vertex *Graph::findVertex(const unsigned &id) const {
    if (id >= this->size())
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
    v2->addEdge(v1, distance);
    edges += 1;
    return true;
}

unsigned Graph::size() const {
    return vertexSet.size();
}

void Graph::clear() {
    vertexSet.clear();
    edges = 0;
}

bool Graph::isComplete() const {
    unsigned n = size();
    return edges == (n * (n - 1))/2;
}

double Graph::tspBacktracking(vector<unsigned> &circuit) const {
    vector<unsigned> currentPath(this->size());
    double minDist = numeric_limits<unsigned>::max();
    currentPath[0] = 0;
    tspBacktracking(1, 0, currentPath, minDist, circuit);
    return minDist;
}

pair<double, double> Graph::tspTriangularApproximation(vector<unsigned> &circuit) const {
    pair<Graph, double> prim = mstPrim();
    Graph mst = prim.first;
    double cost = 0.0;
    for (unsigned i = 0; i < mst.size(); i++) {
        Vertex * vertex = mst.findVertex(i);
        if (!vertex->isVisited())
            vertex->dfsPreorder(circuit);
    }
    for (unsigned i = 0; i < circuit.size() - 1; i++) {
        const Vertex *source = findVertex(circuit[i]);
        const Vertex *dest = findVertex(circuit[i + 1]);
        const Edge *edge = source->getEdge(dest);
        cost += edge ? edge->getDistance() : source->calculateDistance(dest);
    }
    const Edge *end = findVertex(circuit.back())->getEdge(findVertex(0));
    cost += end ? end->getDistance() : findVertex(circuit.back())->calculateDistance(findVertex(0));
    return make_pair(prim.second, cost);
}

pair<double, double> Graph::tspHeuristic(vector<unsigned> &circuit) const {
    double cost = tspNearestNeighbor(circuit);
    const Edge *end = findVertex(circuit.back())->getEdge(findVertex(0));
    cost += end->getDistance();
    return make_pair(cost, 0.0);
}

void Graph::tspBacktracking(unsigned currentIndex, double currentDist, vector<unsigned> &currentPath, double &minDist, vector<unsigned> &circuit) const {
    unsigned size = this->size();
    const Edge * edge;
    if (currentIndex == size && (edge = findVertex(currentPath[size - 1])->getEdge(findVertex(currentPath[0])))) {
        currentDist += edge->getDistance();
        if (currentDist < minDist) {
            minDist = currentDist;
            circuit = currentPath;
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
            if (unvisited) {
                currentPath[currentIndex] = i;
                tspBacktracking(currentIndex + 1, currentDist + edge->getDistance(), currentPath, minDist, circuit);
            }
        }
    }
}

pair<Graph, double> Graph::mstPrim() const {
    Graph mst;
    double cost = 0.0;

    for (const auto v : vertexSet) {
        v->setVisited(false);
        v->setDistance((double) INT_MAX);
        v->setPath(nullptr);
        mst.addVertex(v->getId(), v->getLongitude(), v->getLatitude());
    }

    MutablePriorityQueue<Vertex> q;
    Vertex* root = findVertex(0);
    root->setDistance(0.0);
    q.insert(root);
    while (!q.empty()) {
        auto v = q.extractMin();
        v->setVisited(true);
        for (const auto &edge : v->getAdj()) {
            Vertex* u = edge->getDest();
            if (!u->isVisited()) {
                double distance = u->getDistance();
                if (edge->getDistance() < distance) {
                    u->setDistance(edge->getDistance());
                    u->setPath(edge);
                    if (distance == (double) INT_MAX)
                        q.insert(u);
                    else
                        q.decreaseKey(u);
                }
            }
        }
    }

    for (const auto v : vertexSet) {
        v->setVisited(false);
        Edge *edge = v->getPath();
        if (edge) {
            mst.addEdge(v->getId(),edge->getOrig()->getId(), edge->getDistance());
            cost += edge->getDistance();
        }
    }

    return make_pair(mst, cost);
}

double Graph::tspNearestNeighbor(vector<unsigned> &circuit) const {
    double cost = 0.0;

    for (const auto v : vertexSet) {
        v->setVisited(false);
        v->setDistance((double) INT_MAX);
        v->setPath(nullptr);
    }

    Vertex *vertex = findVertex(0);
    vertex->setVisited(true);
    circuit.push_back(vertex->getId());
    for (unsigned i = 0; i < size() - 1; i++) {
        Edge* edge = vertex->getNearestNeighbor();
        vertex = edge->getDest();
        vertex->setVisited(true);
        vertex->setDistance(edge->getDistance());
        vertex->setPath(edge);
        circuit.push_back(vertex->getId());
        cost += edge->getDistance();
    }

    return cost;
}
