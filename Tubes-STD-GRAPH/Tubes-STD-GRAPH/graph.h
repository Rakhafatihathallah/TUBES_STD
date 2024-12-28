//
//  graph.hpp
//  Tubes-STD-GRAPH
//
//  Created by Rakha Fatih Athallah on 20/12/24.
//
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <map>
#include <string>

using namespace std;


// vertex (Kecamatan)
struct vertex {
    string id;
    vertex* nextVertex;
    struct edge* firstEdge;
};

struct edge {
    string destId;
    double jarak;
    bool bisaDilalui;
    edge* nextEdge;
};

struct graph {
    vertex* firstVertex;
};

void addVertex(graph& G, string id);

void addEdge(graph& G, string asal, string tujuan, double jarak);

vertex* searchVertex(graph& G, string id);

void setRoadCondition(graph& G, string asal, string tujuan, bool condition);

void dijkstra(graph& G, string asal, string tujuan);

void showVertex(graph& G);

void showEdge(graph& G);

#endif /* GRAPH_H */
