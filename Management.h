//
// Created by manue on 08/05/2023.
//

#ifndef TSP_MANAGEMENT_H
#define TSP_MANAGEMENT_H


#include <string>
#include <unordered_set>
#include "Graph.h"

class Management {
public:
    /**@brief Apresenta o menu principal e permite selecionar uma das opções apresentadas.
     *
     * Complexidade Temporal: amplamente variável de acordo com o input
     * @return false se o utilizador pretender sair, true caso contrário
     */
    bool menu();

private:
    std::string nodesFile;
    std::string edgesFile;
    std::string graphFile;
    bool filesRead = false;
    Graph graph;

    /**@brief Verifica se str é um número inteiro não negativo.
     *
     * Complexidade Temporal: O(n), sendo n o comprimento de str
     * @param str string a verificar
     * @return true se str é um número inteiro não negativo, false caso contrário
     */
    static bool isInt(const std::string &str);

    /**@brief Lê o input do utilizador.
     *
     * Complexidade Temporal: O(n), sendo n o comprimento do input do utilizador
     * @return input do utilizador
     */
    static std::string readInput();

    /**@brief Lê o input do utilizador, forçando que seja um número inteiro não negativo.
     *
     * Complexidade Temporal: O(n), sendo n a posição do primeiro input válido introduzido pelo utilizador
     * @return número inteiro não negativo introduzido pelo utilizador
     */
    static int readInt();

    /**@brief Valida um número inteiro, isto é, verifica se n pertence ao intervalo [min, max]. Enquanto o número for inválido, tenta ler um número válido.
     *
     * Complexidade Temporal: O(n), sendo n a posição do primeiro input válido introduzido pelo utilizador
     * @param n número a validar
     * @param min limite inferior do intervalo de números válidos
     * @param max limite superior do intervalo de números válidos
     * @return número inteiro válido introduzido pelo utilizador
     */
    static int validateInt(int n, int min, int max);

    /**@brief Valida um número inteiro, isto é, verifica se n pertence ao conjunto valid. Enquanto o número for inválido, tenta ler um número válido.
     *
     * Complexidade Temporal: O(n), sendo n a posição do primeiro input válido introduzido pelo utilizador
     * @param n número a validar
     * @param valid conjunto de números válidos
     * @return número inteiro válido introduzido pelo utilizador
     */
    static int validateInt(int n, const std::unordered_set<int> &valid);

    /**@brief Lê o ficheiro de nós e cria os nós do grafo.
     *
     * Complexidade Temporal: O(n), sendo n o número de linhas do ficheiro de nós
     * @return true se a leitura do ficheiro de nós foi bem-sucedida, false caso contrário
     */
    bool readNodesFile();

    /**@brief Lê o ficheiro de arestas e preenche o grafo com as arestas.
     *
     * Complexidade Temporal: O(n), sendo n o número de linhas do ficheiro de arestas
     * @return true se a leitura do ficheiro de arestas foi bem-sucedida, false caso contrário
     */
    bool readEdgesFile();

    /**@brief Lê o ficheiro do grafo e cria o grafo.
     *
     * Complexidade Temporal: O(n), sendo n o número de linhas do ficheiro do grafo
     * @param header true se a primeira linha do ficheiro do grafo é um cabeçalho, false caso contrário
     * @return true se a leitura do ficheiro do grafo foi bem-sucedida, false caso contrário
     */
    bool readGraphFile(bool header);

    /**@brief Lê os ficheiros de dados, depois de limpar os dados anteriores.
     *
     * Complexidade Temporal: O(n), sendo n o número de linhas do(s) ficheiro(s) de dados
     */
    void readDataset();

    /**@brief Lê um Toy Graph.
     *
     * Complexidade Temporal: O(n), sendo n o número de linhas do ficheiro do grafo
     */
    void readToyGraph();

    /**@brief Lê um Medium-Size Graph
     *
     * Complexidade Temporal: O(n), sendo n o número de linhas do ficheiro do grafo
     */
    void readMediumSizeGraph();

    /**@brief Lê um Real-World Graph.
     *
     * Complexidade Temporal: O(n), sendo n o número de linhas do ficheiro de nós/arestas
     */
    void readRealWorldGraph();

    /**@brief Verifica se os ficheiros de dados foram lidos, i. e., se existem dados para analisar. Em caso negativo, lê os ficheiros de dados.
     *
     * Complexidade Temporal: O(n), sendo n o número de linhas do(s) ficheiro(s) de dados
     */
    void checkDataset();

    /**@brief Resolve o Travelling Salesperson Problem (TSP) através de um algoritmo de backtracking.
     *
     * Complexidade Temporal: O(V!), sendo V o número de vértices do grafo a analisar
     */
    void backtrackingAlgorithm();

    /**@brief Resolve (de forma aproximada) o Travelling Salesperson Problem (TSP) através de uma heurística de aproximação triangular.
     *
     * Complexidade Temporal: O(V<SUP>2</SUP>), sendo V o número de vértices do grafo a analisar
     */
    void triangularApproximationHeuristic();

    /**@brief Resolve (de forma aproximada) o Travelling Salesperson Problem (TSP) através de uma combinação de heurísticas: Nearest Neighbor para a construção do circuito e Simulated Annealing com 2-opt para a otimização.
     *
     * Complexidade Temporal: O(V<SUP>2</SUP>), sendo V o número de vértices do grafo a analisar
     */
    void ourHeuristic();
};


#endif //TSP_MANAGEMENT_H
