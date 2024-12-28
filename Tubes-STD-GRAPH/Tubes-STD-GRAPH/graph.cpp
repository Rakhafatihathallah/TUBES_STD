//
//  graph.cpp
//  Tubes-STD-GRAPH
//
//  Created by Rakha Fatih Athallah on 20/12/24.
//

#include "graph.h"
#include <iostream>
#include <map>
#include <string>

using namespace std;

void addVertex(graph& G, string id) {
    vertex* newVertex = new vertex{id, nullptr, nullptr};
    if (G.firstVertex == nullptr) {
        G.firstVertex = newVertex;
    } else {
        vertex* temp = G.firstVertex;
        while (temp->nextVertex != nullptr) {
            temp = temp->nextVertex;
        }
        temp->nextVertex = newVertex;
    }
}

void addEdge(graph& G, string asal, string tujuan, double jarak) {
    vertex* asalVertex = searchVertex(G, asal);
    vertex* tujuanVertex = searchVertex(G, tujuan);

    if (asalVertex == nullptr || tujuanVertex == nullptr) {
        cout << "Vertex tidak ditemukan!" << endl;
        return;
    }

    edge* newEdge = new edge{tujuan, jarak, true, nullptr}; // defaultnya smua edge bisa dilalui
    if (asalVertex->firstEdge == nullptr) {
        asalVertex->firstEdge = newEdge;
    } else {
        edge* temp = asalVertex->firstEdge;
        while (temp->nextEdge != nullptr) {
            temp = temp->nextEdge;
        }
        temp->nextEdge = newEdge;
    }
}

vertex* searchVertex(graph& G, string id) {
    vertex* temp = G.firstVertex;
    while (temp != nullptr) {
        if (temp->id == id) {
            return temp;
        }
        temp = temp->nextVertex;
    }
    return nullptr;
}

void setRoadCondition(graph& G, string asal, string tujuan, bool condition) {
    vertex* asalVertex = searchVertex(G, asal);
    if (asalVertex == nullptr) {
        cout << "Vertex asal tidak ditemukan!" << endl;
        return;
    }

    edge* temp = asalVertex->firstEdge;
    while (temp != nullptr) {
        if (temp->destId == tujuan) {
            temp->bisaDilalui = condition;
            return;
        }
        temp = temp->nextEdge;
    }
    cout << "Edge tidak ditemukan!" << endl;
}

void dijkstra(graph& G, string asal, string tujuan) {
    map<string, double> distances;
    map<string, string> previous;
    map<string, bool> visited;

    const double INF = 9999999;

    vertex* temp = G.firstVertex;
    while (temp != nullptr) {
        distances[temp->id] = INF;
        visited[temp->id] = false;
        temp = temp->nextVertex;
    }
    distances[asal] = 0;

    // Dijkstra
    while (true) {
        string u = "";
        double minDist = INF;
        for (const auto& pair : distances) {
            if (!visited[pair.first] && pair.second < minDist) {
                u = pair.first;
                minDist = pair.second;
            }
        }

        if (u == "") break;

        visited[u] = true;
        vertex* uVertex = searchVertex(G, u);
        edge* e = uVertex->firstEdge;
        while (e != nullptr) {
            if (e->bisaDilalui && !visited[e->destId] && distances[u] + e->jarak < distances[e->destId]) {
                distances[e->destId] = distances[u] + e->jarak;
                previous[e->destId] = u;
            }
            e = e->nextEdge;
        }
    }

    if (distances[tujuan] == INF) {
        cout << "Tidak ada jalur yang tersedia!" << endl;
        return;
    }

    cout << "Jalur terpendek dari " << asal << " ke " << tujuan << " adalah: ";
    string current = tujuan;
    while (current != asal) {
        cout << current << " <- ";
        current = previous[current];
    }
    cout << asal << endl;
}

void showVertex(graph& G) {
    vertex* temp = G.firstVertex;
    while (temp != nullptr) {
        cout << temp->id << endl;
        temp = temp->nextVertex;
    }
}

void showEdge(graph& G) {
    vertex* temp = G.firstVertex;
    while (temp != nullptr) {
        edge* e = temp->firstEdge;
        while (e != nullptr) {
            cout << temp->id << " -> " << e->destId << " : " << e->jarak << " meter, Bisa Dilalui: " << (e->bisaDilalui ? "Ya" : "Tidak") << endl;
            e = e->nextEdge;
        }
        temp = temp->nextVertex;
    }
}
