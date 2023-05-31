//
// Created by manue on 08/05/2023.
//

#ifndef TSP_VERTEX_H
#define TSP_VERTEX_H


#include <vector>
#include "Edge.h"
#include "MutablePriorityQueue.h"

class Vertex {
public:
    /**@brief Construtor com parâmetros. Constrói um vértice com id, longitude e latitude.
     *
     * Complexidade Temporal: O(1)
     * @param id id
     * @param longitude longitude
     * @param latitude latitude
     */
    Vertex(unsigned id, double longitude, double latitude);

    /**@brief Compara o vértice e vertex quanto à sua distância.
     *
     * Complexidade Temporal: O(1)
     * @param vertex vértice com o qual comparar
     * @return true se a distância do vértice é inferior à de vertex, false caso contrário
     */
    bool operator<(Vertex &vertex) const;

    /**@brief Retorna o id do vértice.
     *
     * Complexidade Temporal: O(1)
     * @return id do vértice
     */
    unsigned getId() const;

    /**@brief Retorna a longitude do vértice.
     *
     * Complexidade Temporal: O(1)
     * @return longitude do vértice
     */
    double getLongitude() const;

    /**@brief Retorna a latitude do vértice.
     *
     * Complexidade Temporal: O(1)
     * @return latitude do vértice
     */
    double getLatitude() const;

    /**@brief Retorna a lista de adjacências (arestas a sair) do vértice.
     *
     * Complexidade Temporal: O(1)
     * @return lista de adjacências (arestas a sair) do vértice
     */
    std::vector<Edge *> getAdj() const;

    /**@brief Indica se o vértice foi visitado.
     *
     * Complexidade Temporal: O(1)
     * @return true se o vértice foi visitado, false caso contrário
     */
    bool isVisited() const;

    /**@brief Retorna a distância do vértice
     *
     * Complexidade Temporal: O(1)
     * @return distância do vértice
     */
    double getDistance() const;

    /**@brief Retorna a aresta predecessora do vértice no caminho atual.
     *
     * Complexidade Temporal: O(1)
     * @return a aresta predecessora do vértice no caminho atual
     */
    Edge *getPath() const;

    /**@brief Define estado visitado do vértice como visited.
     *
     * Complexidade Temporal: O(1)
     * @param visited novo estado visitado do vértice
     */
    void setVisited(bool visited);

    /**@brief Define a distância do vértice como distance.
     *
     * Complexidade Temporal: O(1)
     * @param cost nova distância do vértice
     */
    void setDistance(double distance);

    /**@brief Define a aresta predecessora do vértice como path.
     *
     * Complexidade Temporal: O(1)
     * @param path nova aresta predecessora do vértice
     */
    void setPath(Edge *path);

    /**@brief Adiciona um aresta desde o vértice até dest, com distância distance.
     *
     * Complexidade Temporal: O(1)
     * @param dest destino da aresta
     * @param distance distância da aresta
     * @return aresta adicionada ao vértice
     */
    Edge *addEdge(Vertex *dest, double distance);

    /**@brief Retorna a aresta com origem no vértice e destino em vertex (se existir).
     *
     * Complexidade Temporal: O(n), sendo n o tamanho da lista de adjacências (arestas a sair) do vértice
     * @return aresta com origem no vértice e destino em vertex
     */
    const Edge * getEdge(Vertex * vertex) const;

    /**@brief Remove todas as arestas de saída do vértice.
     *
     * Complexidade Temporal: O(n), sendo n o tamanho da lista de adjacências (arestas a sair) do vértice
     */
    void removeOutgoingEdges();

    /**@brief Calcula a distância entre o vértice e vertex através do método de Haversine.
     *
     * @param vertex vértice de destino para o cálculo da distância
     * @return distância entre o vértice e vertex
     */
    double calculateDistance(Vertex * vertex) const;

    friend class MutablePriorityQueue<Vertex>;

private:
    unsigned id;
    double longitude;
    double latitude;
    std::vector<Edge *> adj;
    bool visited = false;
    double distance = 0.0;
    Edge *path = nullptr;
    std::vector<Edge *> incoming;
    int queueIndex;

    /**@brief Apaga a aresta edge.
     *
     * Complexidade Temporal: O(n), sendo n o tamanho da lista de arestas de entrada no vértice de destino da aresta edge
     * @param edge aresta a apagar
     */
    void deleteEdge(Edge *edge) const;
};


#endif //TSP_VERTEX_H
