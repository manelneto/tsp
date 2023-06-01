//
// Created by manue on 08/05/2023.
//

#ifndef TSP_EDGE_H
#define TSP_EDGE_H


class Vertex;

class Edge {
public:
    /**@brief Construtor com parâmetros. Constrói uma aresta com origem, destino e distância.
     *
     * Complexidade Temporal: O(1)
     * @param orig origem
     * @param dest destino
     * @param dist distância
     */
    Edge(Vertex *orig, Vertex *dest, double distance);

    /**@brief Compara a aresta e edge quanto à sua distância.
     *
     * Complexidade Temporal: O(1)
     * @param edge aresta com a qual comparar
     * @return true se a distância da aresta é inferior à de edge, false caso contrário
     */
    bool operator<(const Edge &edge) const;

    /**@brief Retorna a origem da aresta.
     *
     * Complexidade Temporal: O(1)
     * @return origem da aresta
     */
    Vertex *getOrig() const;

    /**@brief Retorna o destino da aresta.
     *
     * Complexidade Temporal: O(1)
     * @return destino da aresta
     */
    Vertex *getDest() const;

    /**@brief Retorna a distância da aresta.
     *
     * Complexidade Temporal: O(1)
     * @return distância da aresta
     */
    double getDistance() const;

private:
    Vertex *orig;
    Vertex *dest;
    double distance;
};

struct edgeCmp {
    /**Função de comparação para a ordenação da lista de adjacências de um vértice.
     *
     * Complexidade Temporal: O(1)
     * @param edge1 aresta 1
     * @param edge2 aresta 2
     * @return true se a distância da aresta 1 é menor do que a distância da aresta 2, false caso contrário
     */
    bool operator()(const Edge* edge1, const Edge* edge2) const {
        return *edge1 < *edge2;
    }
};


#endif //TSP_EDGE_H
