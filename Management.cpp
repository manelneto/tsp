//
// Created by manue on 08/05/2023.
//

#include "Management.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <list>
#include <stdexcept>

using namespace std;

bool Management::isInt(const string &str) {
    for (const char &ch : str)
        if (!isdigit(ch))
            return false;
    return true;
}

string Management::readInput() {
    string s;
    getline(cin, s);
    cout << endl;
    return s;
}

int Management::readInt() {
    string s = readInput();
    while (!isInt(s)) {
        cout << "Deve inserir um número inteiro não negativo. Tente novamente: ";
        s = readInput();
    }
    int n;
    try {
        n = stoi(s);
    } catch (invalid_argument &) {
        cout << "Não introduziu nenhum número. Tente novamente: ";
        n = readInt();
    }
    return n;
}

int Management::validateInt(int n, int min, int max) {
    while (n < min || n > max) {
        cout << "O número inserido não é válido (deve pertencer ao intervalo [" << min << ", " << max
             << "]). Tente novamente: ";
        n = readInt();
    }
    return n;
}

bool Management::menu() {
    cout << "\nMenu Principal:\n"
            "1 - Ler ficheiros de dados\n"
            "2 - Usar o algoritmo de 'backtracking'\n"
            "3 - Usar a heurística de aproximação triangular\n"
            "4 - Usar a nossa heurística\n"
            "0 - Sair\n"
            "Opção: ";
    int option = readInt();
    option = validateInt(option, 0, 4);
    if (option == 1)
        readDataset();
    else if (option == 2)
        backtrackingAlgorithm();
    else if (option == 3)
        triangularApproximationHeuristic();
    else if (option == 4)
        ourHeuristic();
    else
        return false;
    return true;
}

bool Management::readNodesFile() {
    ifstream in("../files/" + nodesFile);
    if (!in.is_open()) {
        cout << "Erro ao abrir o ficheiro " << nodesFile << "." << endl;
        cout << "Verifique se o ficheiro se encontra dentro do diretório files." << endl;
        return false;
    }
    cout << "\nA ler ficheiro " << nodesFile << "..." << endl;
    string line;
    getline(in, line);
    unsigned errors = 0;
    while (getline(in, line)) {
        istringstream iss(line);
        string field;
        vector<string> fields(3);
        unsigned f = 0;
        while (getline(iss, field, ','))
            fields[f++] = field;
        unsigned id = stoul(fields[0]);
        double longitude = stod(fields[1]);
        double latitude = stod(fields[2]);
        if (!graph.addVertex(id, longitude, latitude))
            errors++;
    }
    cout << "Leitura do ficheiro " << nodesFile << " bem-sucedida!" << endl;
    cout << "Foram lidos " << graph.size() << " nós e ocorreram " << errors << " erros. ";
    return true;
}

bool Management::readEdgesFile() {
    ifstream in("../files/" + edgesFile);
    if (!in.is_open()) {
        cout << "Erro ao abrir o ficheiro " << edgesFile << "." << endl;
        cout << "Verifique se o ficheiro se encontra dentro do diretório files." << endl;
        return false;
    }
    cout << "\nA ler ficheiro " << edgesFile << "..." << endl;
    string line;
    getline(in, line);
    unsigned counter = 0;
    unsigned errors = 0;
    while (getline(in, line)) {
        istringstream iss(line);
        string field;
        vector<string> fields(3);
        unsigned f = 0;
        while (getline(iss, field, ','))
            fields[f++] = field;
        unsigned orig = stoul(fields[0]);
        unsigned dest = stoul(fields[1]);
        double distance = stod(fields[2]);
        if (graph.addEdge(orig, dest, distance))
            counter++;
        else
            errors++;
    }
    cout << "Leitura do ficheiro " << edgesFile << " bem-sucedida!" << endl;
    cout << "Foram lidas " << counter << " arestas e ocorreram " << errors << " erros." << endl;
    return true;
}

bool Management::readGraphFile() {
    ifstream in("../files/" + graphFile);
    if (!in.is_open()) {
        cout << "Erro ao abrir o ficheiro " << graphFile << "." << endl;
        cout << "Verifique se o ficheiro se encontra dentro do diretório files." << endl;
        return false;
    }
    cout << "\nA ler ficheiro " << graphFile << "..." << endl;
    string line;
    getline(in, line);
    unsigned counter = 0;
    unsigned errors = 0;
    unsigned last = 0;
    list<pair<unsigned, unsigned>> edges;
    list<double> distances;
    while (getline(in, line)) {
        istringstream iss(line);
        string field;
        vector<string> fields(3);
        unsigned f = 0;
        while (f < 3 && getline(iss, field, ','))
            fields[f++] = field;
        unsigned orig = stoul(fields[0]);
        unsigned dest = stoul(fields[1]);
        last = max(last, orig);
        last = max(last, dest);
        double distance = stod(fields[2]);
        edges.emplace_back(orig, dest);
        distances.push_back(distance);
    }
    if (edges.size() != distances.size())
        throw logic_error("Algo correu mal...");
    for (unsigned i = 0; i <= last; i++)
        graph.addVertex(i);
    auto edge = edges.begin();
    auto distance = distances.begin();
    for (; edge != edges.end() && distance != distances.end(); edge++, distance++)
        if (graph.addEdge(edge->first, edge->second, *distance))
            counter++;
        else
            errors++;
    cout << "Leitura do ficheiro " << graphFile << " bem-sucedida!" << endl;
    cout << "Foram lidos " << graph.size() << " nós e " << counter << " arestas e ocorreram " << errors << " erros." << endl;
    return true;
}

void Management::readDataset() {
    cout << "A limpar dados..." << endl;
    graph.clear();
    cout << "\nGrafo a Ler:\n"
            "1 - Real-World-Graph\n"
            "2 - Toy-Graph\n"
            "0 - Retroceder\n"
            "Opção: ";
    int option = readInt();
    option = validateInt(option, 0, 2);
    if (option == 1)
        readRealWorldGraph();
    else if (option == 2)
        readToyGraph();
}

void Management::readRealWorldGraph() {
    string path = "Real-World-Graphs/graph";
    cout << "\nReal-World-Graph (1, 2, 3): ";
    int option = readInt();
    option = validateInt(option, 1, 3);
    path += (char) ('0' + option);
    nodesFile = path + "/nodes.csv";
    edgesFile = path + "/edges.csv";
    bool nodesRead = readNodesFile();
    cout << endl;
    bool edgesRead = readEdgesFile();
    cout << endl;
    filesRead = nodesRead && edgesRead;
}

void Management::readToyGraph() {
    string path = "Toy-Graphs";
    cout << "\nToy-Graph:\n"
            "1 - shipping\n"
            "2 - stadiums\n"
            "3 - tourism\n"
            "Opção: ";
    int option = readInt();
    option = validateInt(option, 1, 3);
    if (option == 1)
        path += "/shipping.csv";
    else if (option == 2)
        path += "/stadiums.csv";
    else
        path += "/tourism.csv";
    graphFile = path;
    filesRead = readGraphFile();
}

void Management::checkDataset() {
    while (!filesRead) {
        cout
                << "Ainda não leu os ficheiros de dados (ou ocorreu um erro durante a leitura), pelo que não existem dados para analisar."
                << endl;
        cout << endl;
        readDataset();
    }
}

void Management::backtrackingAlgorithm() {
    checkDataset();
    // TODO
}

void Management::triangularApproximationHeuristic() {
    checkDataset();
    // TODO
}

void Management::ourHeuristic() {
    checkDataset();
    // TODO
}
