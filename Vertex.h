//
// Created by manue on 08/05/2023.
//

#ifndef TSP_VERTEX_H
#define TSP_VERTEX_H


#include <vector>
#include "Edge.h"

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

private:
    unsigned id;
    double longitude;
    double latitude;
    std::vector<Edge *> adj;
    std::vector<Edge *> incoming;

    /**@brief Apaga a aresta edge.
     *
     * Complexidade Temporal: O(n), sendo n o tamanho da lista de arestas de entrada no vértice de destino da aresta edge
     * @param edge aresta a apagar
     */
    void deleteEdge(Edge *edge) const;
};


#endif //TSP_VERTEX_H
