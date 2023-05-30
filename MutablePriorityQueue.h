//
// Created by manue on 30/05/2023.
//

#ifndef TSP_MUTABLEPRIORITYQUEUE_H
#define TSP_MUTABLEPRIORITYQUEUE_H


#include <vector>

template<class T>
class MutablePriorityQueue {
public:
    /**@brief Construtor sem parâmetros. Constrói uma fila de prioridade mutável (minHeap) com índices a começar em 1 para facilitar cálculos de pais/filhos.
     *
     * Complexidade Temporal: O(1)
     */
    MutablePriorityQueue();

    /**@brief Insere o elemento x na fila de prioridade mutável e reajusta a fila.
     *
     * Complexidade Temporal: O(log n), sendo n o número de elementos na fila de prioridade mutável
     * @param x elemento a inserir na fila de prioridade mutável
     */
    void insert(T *x);

    /**@brief Retorna o elemento mais prioritário (menor índice) da fila de prioridade mutável, retira-o da fila e reajusta-a.
     *
     * Complexidade Temporal: O(log n), sendo n o número de elementos na fila de prioridade mutável
     * @return apontador para o elemento mais prioritário da fila de prioridade mutável
     */
    T *extractMin();

    /**@brief Atualiza a prioridade do elemento x (aumentando-a, diminuindo o índice) e reajusta a fila de prioridade mutável.
     *
     * Complexidade Temporal: O(log n), sendo n o número de elementos na fila de prioridade mutável
     * @param x elemento a atualizar prioridade
     */
    void decreaseKey(T *x);

    /**@brief Verifica se a fila de prioridade mutável não contém elementos, i. e., se o seu tamanho é 1.
     *
     * Complexidade Temporal: O(1)
     * @return true se a fila de prioridade mutável está vazia, false caso contrário
     */
    bool empty();

private:
    std::vector<T *> H;

    /**@brief Sobe o elemento de índice i na fila de prioridade mutável (minHeap), i. e., troca-o sucessivamente com o seu pai até se encontrar na posição correta.
     *
     * Complexidade Temporal: O(log n), sendo n o número de elementos na fila de prioridade mutável
     * @param i índice do elemento a subir na fila de prioridade mutável
     */
    void heapifyUp(unsigned i);

    /**@brief Desce o elemento de índice i na fila de prioridade mutável (minHeap), i. e, troca-o sucessivamente com um dos seus filhos até se encontrar na posição correta.
     *
     * Complexidade Temporal: O(log n), sendo n o número de elementos na fila de prioridade mutável
     * @param i índice do elemento a descer na fila de prioridade mutável
     */
    void heapifyDown(unsigned i);

    /**@brief Coloca o elemento x na posição índice i da fila de prioridade mutável, atualizando o seu índice.
     *
     * Comlexidade Temporal: O(1)
     * @param i índice da nova posição do elemento x
     * @param x elemento a colocar na posição índice i da fila de prioridade mutável
     */
    inline void set(unsigned i, T *x);
};

// Index calculations
#define parent(i) ((i) / 2)
#define leftChild(i) ((i) * 2)

template<class T>
MutablePriorityQueue<T>::MutablePriorityQueue() {
    H.push_back(nullptr);
}

template<class T>
void MutablePriorityQueue<T>::insert(T *x) {
    H.push_back(x);
    heapifyUp(H.size() - 1);
}

template<class T>
T *MutablePriorityQueue<T>::extractMin() {
    auto x = H[1];
    H[1] = H.back();
    H.pop_back();
    if (H.size() > 1)
        heapifyDown(1);
    x->queueIndex = 0;
    return x;
}

template<class T>
void MutablePriorityQueue<T>::decreaseKey(T *x) {
    heapifyUp(x->queueIndex);
}

template<class T>
bool MutablePriorityQueue<T>::empty() {
    return H.size() == 1;
}

template<class T>
void MutablePriorityQueue<T>::heapifyUp(unsigned i) {
    auto x = H[i];
    while (i > 1 && *x < *H[parent(i)]) {
        set(i, H[parent(i)]);
        i = parent(i);
    }
    set(i, x);
}

template<class T>
void MutablePriorityQueue<T>::heapifyDown(unsigned i) {
    auto x = H[i];
    while (true) {
        unsigned k = leftChild(i);
        if (k >= H.size())
            break;
        if (k + 1 < H.size() && *H[k + 1] < *H[k])
            ++k; // right child of i
        if (!(*H[k] < *x))
            break;
        set(i, H[k]);
        i = k;
    }
    set(i, x);
}

template<class T>
void MutablePriorityQueue<T>::set(unsigned i, T *x) {
    H[i] = x;
    x->queueIndex = i;
}


#endif //TSP_MUTABLEPRIORITYQUEUE_H
