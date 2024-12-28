//
//  main.cpp
//  Tubes-STD-GRAPH
//
//  Created by Rakha Fatih Athallah on 20/12/24.
//
#include "graph.h"

int main() {
    graph G = {nullptr};

    // Menambahkan vertex (Kecamatan)
    addVertex(G, "Bandung Kidul");
    addVertex(G, "Batununggal");
    addVertex(G, "Buahbatu");
    addVertex(G, "Rancasari");
    addVertex(G, "Kiaracondong");
    addVertex(G, "Andir");
    addVertex(G, "Sukasari");

    addEdge(G, "Bandung Kidul", "Batununggal", 5000);
    addEdge(G, "Bandung Kidul", "Buahbatu", 10000);
    addEdge(G, "Batununggal", "Rancasari", 7000);
    addEdge(G, "Buahbatu", "Kiaracondong", 3000);
    addEdge(G, "Rancasari", "Andir", 4000);
    addEdge(G, "Kiaracondong", "Sukasari", 6000);
    addEdge(G, "Andir", "Sukasari", 8000);

    cout << "Daftar Kecamatan (Vertex):\n";
    showVertex(G);
    cout << "Daftar Rute (Edge):\n";
    showEdge(G);

    cout << "\nMenemukan rute terpendek dari Bandung Kidul ke Sukasari:\n";
    dijkstra(G, "Bandung Kidul", "Sukasari");

    cout << "\nMengubah kondisi jalan antara Bandung Kidul dan Batununggal menjadi tidak bisa dilalui.\n";
    setRoadCondition(G, "Bandung Kidul", "Batununggal", false);
    cout << "Setelah perubahan kondisi jalan:\n";
    showEdge(G);

    return 0;
}

