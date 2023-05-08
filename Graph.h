//
// Created by manue on 08/05/2023.
//

#ifndef TSP_GRAPH_H
#define TSP_GRAPH_H


#include <vector>
#include "Vertex.h"

class Graph {
public:
    /**@brief Procura o vértice do grafo pelo seu id.
     *
     * Complexidade Temporal: O(1)
     * @param id id do vértice a procurar
     * @return apontador para o vértice encontrado
     */
    Vertex *findVertex(const unsigned &id) const;

    /**@brief Adiciona ao grafo um vértice com id, longitude e latitude.
     *
     * Complexidade Temporal: O(1)
     * @param id id do vértice a adicionar
     * @param longitude longitude do vértice a adicionar
     * @param latitude latitude do vértice a adicionar
     * @return true se a operação foi bem-sucedida, false caso contrário (já existia no grafo um vértice com o mesmo id)
     */
    bool addVertex(const unsigned &id, const double &longitude = 0.0, const double &latitude = 0.0);

    /**@brief Adiciona ao grafo uma aresta com origem no vértice de id orig e destino no vértice de id dest, com distância distance.
     *
     * Complexidade Temporal: O(1)
     * @param orig id do vértice de origem da aresta a adicionar
     * @param dest id do vértice de destino da aresta a adicionar
     * @param distance distância da aresta a adicionar
     * @return true se a operação foi bem-sucedida, false caso contrário (não existe no grafo nenhum vértice com id orig ou com id dest)
     */
    bool addEdge(const unsigned &orig, const unsigned &dest, const double &distance);

    /**@brief Retorna o tamanho (número de nós) do grafo
     *
     * @return tamanho (número de nós) do grafo
     */
    unsigned size();

    /**@brief Limpa o grafo, i. e., remove todas as suas arestas e todos os seus vértices.
     *
     * Complexidade Temporal: O(V + E), sendo V o número de vértices do grafo e E o número de arestas do grafo
     */
    void clear();

private:
    std::vector<Vertex *> vertexSet;
};


#endif //TSP_GRAPH_H
