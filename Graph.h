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

    /**@brief Adiciona ao grafo uma aresta bidirecional com origem no vértice de id orig e destino no vértice de id dest, com distância distance.
     *
     * Complexidade Temporal: O(1)
     * @param orig id do vértice de origem da aresta a adicionar
     * @param dest id do vértice de destino da aresta a adicionar
     * @param distance distância da aresta a adicionar
     * @return true se a operação foi bem-sucedida, false caso contrário (não existe no grafo nenhum vértice com id orig ou com id dest)
     */
    bool addEdge(const unsigned &orig, const unsigned &dest, const double &distance) const;

    /**@brief Retorna o tamanho (número de nós) do grafo
     *
     * @return tamanho (número de nós) do grafo
     */
    unsigned size() const;

    /**@brief Limpa o grafo, i. e., remove todas as suas arestas e todos os seus vértices.
     *
     * Complexidade Temporal: O(V + E), sendo V o número de vértices do grafo e E o número de arestas do grafo
     */
    void clear();

    /**@brief Resolve o Travelling Salesperson Problem (TSP) através de um algoritmo de backtracking.
     *
     * Complexidade Temporal: O(V!), sendo V o número de vértices
     * @param circuit circuito encontrado como solução para o Travelling Salesperson Problem (TSP)
     * @return custo do circuito encontrado como solução para o Travelling Salesperson Problem (TSP)
     */
    double tspBacktracking(std::vector<unsigned> &circuit) const;

    /**
     * @brief Resolve o Travelling Salesperson Problem (TSP) através de uma heurística de aproximação triangular.
     *
     * Complexidade Temporal: O(V<SUP>2</SUP>), sendo V o número de vértices do grafo
     * @param circuit circuito encontrado como solução para o Travelling Salesperson Problem (TSP)
     * @return par cujo primeiro valor é o custo da Minimum Cost Spanning Tree (MST) determinada para a heurística e o segundo valor é o custo do circuito encontrado como solução para o Travelling Salesperson Problem (TSP)
     */
    std::pair<double, double> tspTriangularApproximation(std::vector<unsigned> &circuit) const;

private:
    std::vector<Vertex *> vertexSet;

    /**@brief Função auxiliar recursiva para resolver o Travelling Salesperson Problem (TSP) através de um algoritmo de backtracking.
     *
     * Complexidade Temporal: O(V!), sendo V o número de vértices
     * @param currentIndex índice atual do nó a analisar no circuito
     * @param currentDist distância (peso) atual do circuito encontrado
     * @param currentPath circuito encontrado até ao momento
     * @param minDist distância mínima (peso mínimo) do circuito encontrado até ao momento
     * @param circuit circuito encontrado como solução para o Travelling Salesperson Problem (TSP)
     */
    void tspBacktracking(unsigned currentIndex, double currentDist, std::vector<unsigned> &currentPath, double &minDist, std::vector<unsigned> &circuit) const;

    /**
     * @brief Determina uma Minimum Cost Spanning Tree (MST) do grafo através do algoritmo de Prim.
     *
     * Complexidade Temporal: O(E log(V)), sendo V o número de vértices do grafo e E o número de arestas do grafo
     * @return par cujo primeiro valor é a Minimum Cost Spanning Tree (MST) determinada e o segundo valor é o custo da Minimum Cost Spanning Tree (MST) determinada
     */
    std::pair<Graph, double> mstPrim() const;
};


#endif //TSP_GRAPH_H
