//
// Created by manue on 08/05/2023.
//

#include "Graph.h"
#include "MutablePriorityQueue.h"

#include <limits>
#include <climits>
#include <random>
#include <algorithm>

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
    circuit.push_back(0);
    for (unsigned i = 0; i < circuit.size() - 1; i++) {
        const Vertex *source = findVertex(circuit[i]);
        const Vertex *dest = findVertex(circuit[i + 1]);
        const Edge *edge = source->getEdge(dest);
        cost += edge ? edge->getDistance() : source->calculateDistance(dest);
    }
    return make_pair(prim.second, cost);
}

pair<double, double> Graph::tspHeuristic(vector<unsigned> &circuit) const {
    double before = tspNearestNeighbor(circuit);
    double after = tspSimulatedAnnealing(before, circuit);
    return make_pair(before, after);
}

void Graph::tspBacktracking(unsigned currentIndex, double currentDist, vector<unsigned> &currentPath, double &minDist, vector<unsigned> &circuit) const {
    unsigned size = this->size();
    const Edge * edge;
    if (currentIndex == size && (edge = findVertex(currentPath[size - 1])->getEdge(findVertex(currentPath[0])))) {
        currentDist += edge->getDistance();
        if (currentDist < minDist) {
            minDist = currentDist;
            circuit = currentPath;
            circuit.push_back(0);
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
    cost += findVertex(circuit.back())->getEdge(findVertex(0))->getDistance();
    circuit.push_back(0);
    return cost;
}

std::pair<double, std::vector<unsigned>> Graph::tspTwoOptSwap(double cost, const vector<unsigned> &circuit) const {
    random_device device;
    mt19937 rng(device());
    uniform_int_distribution<unsigned> distribution(0, circuit.size() - 2);
    unsigned first = distribution(rng);
    unsigned second = max(first, distribution(rng));

    if (second == first)
        return make_pair(cost, circuit);

    Edge *oldFirst = findVertex(circuit[first])->getEdge(findVertex(circuit[first + 1]));
    Edge *oldSecond = findVertex(circuit[second])->getEdge(findVertex(circuit[second + 1]));

    Edge *newFirst = findVertex(circuit[first])->getEdge(findVertex(circuit[second]));
    Edge *newSecond = findVertex(circuit[first + 1])->getEdge(findVertex(circuit[second + 1]));

    double delta = oldFirst->getDistance() + oldSecond->getDistance() - newFirst->getDistance() - newSecond->getDistance();

    //if (delta <= 0)
    //
    //    return make_pair(cost, circuit);

    vector<unsigned> tentative = circuit;
    reverse(tentative.begin() + first + 1, tentative.begin() + second + 1);

    return make_pair(cost - delta, tentative);
}

double Graph::tspSimulatedAnnealing(double cost, vector<unsigned> &circuit) const {
    random_device device;
    mt19937 rng(device());
    uniform_real_distribution<double> distribution(0.0, 1.0);

    double bestCost = cost;
    vector<unsigned> bestCircuit = circuit;
    for (double temperature = 100.0; temperature > 0.1; temperature *= 0.9)
        for (unsigned i = 0; i < circuit.size(); i++) {
            pair<double, vector<unsigned>> neighbor = tspTwoOptSwap(cost, circuit);
            double delta = neighbor.first - cost;
            if (delta <= 0) {
                cost = neighbor.first;
                circuit = neighbor.second;
                if (cost < bestCost) {
                    bestCost = cost;
                    bestCircuit = circuit;
                }
            }
            else {
                double random = distribution(rng);
                if (random < exp(-delta/temperature)) {
                    cost = neighbor.first;
                    circuit = neighbor.second;
                }
            }
        }
    circuit = bestCircuit;
    return bestCost;
}
