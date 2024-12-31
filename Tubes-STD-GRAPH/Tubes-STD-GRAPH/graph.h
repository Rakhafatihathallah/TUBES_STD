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

typedef struct vertex *adrVertex;
typedef struct edge *adrEdge;

// vertex (Kecamatan)
struct vertex {
    string id;
    vertex* nextVertex;
    struct edge* firstEdge;
};

struct edge {
    string destDaerahId;
    double jarak; // dalam bentuk meter
    bool bisaDilalui;
    edge* nextEdge;
};

struct graph {
    vertex* firstVertex;
};

void initGraph(graph &G);
void addVertex(graph &G, string namaDaerah);
void buildGraph(graph &G);
void deleteDaerah(graph &G, string namaDaerah);
void addEdge(graph &G, string asal, string tujuan, int jarak);
void deleteRute(graph &G, string asal, string tujuan);
// mencari daerah (vertex)
vertex* searchVertex(graph &G, string namaDaerah);
void setRoadCondition(graph &G, string asal, string tujuan, bool kondisi);
// jalur tercepat yang bebas dilalui
void findShortestRoute(graph &G, string asal, string tujuan);
void showGraph(graph G);
void showVertex(graph G);
void showEdge(graph G);
void showMenu();

#endif /* GRAPH_H */
