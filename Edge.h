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


#endif //TSP_EDGE_H
