//
//  graph.cpp
//  Tubes-STD-GRAPH
//
//  Created by Rakha Fatih Athallah on 20/12/24.
//

#include "graph.h"
#include <iostream>
#include <string>
#include <map>
#define firstVertex(G) G.firstVertex
#define nextVertex(v) v->nextVertex
#define firstEdge(v) v->firstEdge
#define idVertex(v) v->idVertex
#define destVertexID(e) e->destVertexID
#define weight(e) e->weight
#define nextEdge(e) e->nextEdge

using namespace std;

void initGraph(graph &G) {
    G.firstVertex = nullptr;
}

void addVertex(graph &G, string namaDaerah) {
    vertex* newVertex = new vertex;
    newVertex->id = namaDaerah;
    newVertex->nextVertex = nullptr;
    newVertex->firstEdge = nullptr;

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

void addEdge(graph &G, string asal, string tujuan, int jarak) {
    vertex* src = searchVertex(G, asal);
    vertex* dest = searchVertex(G, tujuan);

    if (src != nullptr && dest != nullptr && jarak > 0) {
        edge* newEdge = new edge;
        newEdge->destDaerahId = tujuan;
        newEdge->jarak = jarak;
        newEdge->bisaDilalui = true;
        newEdge->nextEdge = nullptr;

        if (src->firstEdge == nullptr) {
            src->firstEdge = newEdge;
        } else {
            edge* temp = src->firstEdge;
            while (temp->nextEdge != nullptr) {
                temp = temp->nextEdge;
            }
            temp->nextEdge = newEdge;
        }
    }
}

void buildGraph(graph &G) {
    string namaDaerah;
    initGraph(G);
    addVertex(G, "Bojongsoang");
    addVertex(G, "Bandung Kidul");
    addVertex(G, "Batununggal");
    addVertex(G, "Buahbatu");
    addVertex(G, "Rancasari");
    addVertex(G, "Kiaracondong");
    addVertex(G, "Andir");
    addVertex(G, "Sukasari");
    
    addEdge(G, "Bojongsoang", "Batununggal", 1200);
    addEdge(G, "Batununggal", "Bojongsoang", 1200);
    
    addEdge(G, "Bandung Kidul", "Kiaracondong", 1000);
    addEdge(G, "Kiaracondong", "Bandung Kidul", 1000);
    addEdge(G, "Kiaracondong", "Bojongsoang", 1400);
    addEdge(G, "Bojongsoang", "Kiaracondong", 1400);
    addEdge(G, "Baleendah", "Bojongsoang", 800);
    addEdge(G, "Bojongsoang", "Baleendah", 800);
    addEdge(G, "Baleendah", "Andir", 100);
    addEdge(G, "Andir", "Baleendah", 100);
    addEdge(G, "Andir", "Bojongsoang", 600);
    addEdge(G, "Bojongsoang", "Andir", 600);
    addEdge(G, "Baleendah", "Sukasari", 1400);
    addEdge(G, "Sukasari", "Baleendah", 1400);
    addEdge(G, "Batununggal", "Rancasari", 1200);
    addEdge(G, "Rancasari", "Batununggal", 1200);
    addEdge(G, "Rancasari", "Buahbatu", 1600);
    addEdge(G, "Buahbatu", "Rancasari", 1600);
    addEdge(G, "Batununggal", "Bandung Kidul", 700);
    addEdge(G, "Bandung Kidul", "Batununggal", 700);
    addEdge(G, "Batununggal", "Buahbatu", 1100);
    addEdge(G, "Buahbatu", "Batununggal", 1100);
}

vertex* searchVertex(graph &G, string namaDaerah) {
    vertex* temp = G.firstVertex;
    while (temp != nullptr) {
        if (temp->id == namaDaerah) {
            return temp;
        }
        temp = temp->nextVertex;
    }
    return nullptr;
}

void setRoadCondition(graph &G, string asal, string tujuan, bool kondisi) {
    vertex* src = searchVertex(G, asal);
    if (src != nullptr) {
        edge* temp = src->firstEdge;
        while (temp != nullptr) {
            if (temp->destDaerahId == tujuan) {
                temp->bisaDilalui = kondisi;
                return;
            }
            temp = temp->nextEdge;
        }
    }
}

void findShortestRoute(graph &G, string asal, string tujuan) {
    const int INF = INT_MAX;
    map<string, int> jarak;
    map<string, bool> dikunjungi;
    map<string, string> prevVertex;  // Untuk menyimpan rute

    // Inisialisasi jarak dan dikunjungi
    for (vertex* temp = G.firstVertex; temp != nullptr; temp = temp->nextVertex) {
        jarak[temp->id] = INF;
        dikunjungi[temp->id] = false;
    }

    jarak[asal] = 0;

    while (true) {
        string currentVertex = "";
        int minDistance = INF;

        // Cari vertex dengan jarak terkecil yang belum dikunjungi
        for (const auto &pair : jarak) {
            if (!dikunjungi[pair.first] && pair.second < minDistance) {
                minDistance = pair.second;
                currentVertex = pair.first;
            }
        }

        // Jika tidak ada vertex yang bisa diproses atau mencapai tujuan
        if (currentVertex == "" || currentVertex == tujuan) {
            break;
        }

        dikunjungi[currentVertex] = true;

        vertex* current = searchVertex(G, currentVertex);
        for (edge* tempEdge = current->firstEdge; tempEdge != nullptr; tempEdge = tempEdge->nextEdge) {
            if (tempEdge->bisaDilalui && !dikunjungi[tempEdge->destDaerahId]) {
                int newDist = jarak[currentVertex] + tempEdge->jarak;
                if (newDist < jarak[tempEdge->destDaerahId]) {
                    jarak[tempEdge->destDaerahId] = newDist;
                    prevVertex[tempEdge->destDaerahId] = currentVertex; // Simpan vertex asal
                }
            }
        }
    }

    if (jarak[tujuan] == INF) {
        cout << "Tidak ada jalur ke tujuan." << endl;
    } else {
        cout << "Jarak terpendek dari " << asal << " ke " << tujuan << ": " << jarak[tujuan] << " meter" << endl;

        cout << "Rute: ";
        string path = tujuan;
        while (path != asal) {
            path = prevVertex[path];
            cout << path << " -> ";
        }
        cout << tujuan << endl;
    }
}

void showGraph(graph G) {
    vertex* tempVertex = G.firstVertex;
    while (tempVertex != nullptr) {
        cout << tempVertex->id << " -> ";
        edge* tempEdge = tempVertex->firstEdge;
        while (tempEdge != nullptr) {
            cout << tempEdge->destDaerahId << "(" << tempEdge->jarak << " m, " << (tempEdge->bisaDilalui ? "Bisa" : "Tidak Bisa") << ") ";
            tempEdge = tempEdge->nextEdge;
        }
        cout << endl;
        tempVertex = tempVertex->nextVertex;
    }
}

void showVertex(graph G) {
    vertex* temp = G.firstVertex;
    while (temp != nullptr) {
        cout << temp->id << endl;
        temp = temp->nextVertex;
    }
}

void showEdge(graph G) {
    vertex* tempVertex = G.firstVertex;
    while (tempVertex != nullptr) {
        edge* tempEdge = tempVertex->firstEdge;
        while (tempEdge != nullptr) {
            cout << tempVertex->id << " -> " << tempEdge->destDaerahId << " (" << tempEdge->jarak << " m, "
                 << (tempEdge->bisaDilalui ? "Bisa" : "Tidak Bisa") << ")" << endl;
            tempEdge = tempEdge->nextEdge;
        }
        tempVertex = tempVertex->nextVertex;
    }
}

void deleteDaerah(graph &G, string namaDaerah) {
    vertex* temp = G.firstVertex;
    vertex* prev = nullptr;
    while (temp != nullptr && temp->id != namaDaerah) {
        prev = temp;
        temp = temp->nextVertex;
    }

    if (temp == nullptr) {
        cout << "Daerah tidak ditemukan!" << endl;
        return;
    }

    if (prev == nullptr) {
        G.firstVertex = temp->nextVertex;
    } else {
        prev->nextVertex = temp->nextVertex;
    }

    delete temp;
}

void deleteRute(graph &G, string asal, string tujuan) {
    // source / asal
    vertex* src = searchVertex(G, asal);
    if (src != nullptr) {
        edge* temp = src->firstEdge;
        edge* prev = nullptr;
        while (temp != nullptr && temp->destDaerahId != tujuan) {
            prev = temp;
            temp = temp->nextEdge;
        }

        if (temp == nullptr) {
            cout << "Rute tidak ditemukan!" << endl;
            return;
        }

        if (prev == nullptr) {
            src->firstEdge = temp->nextEdge;
        } else {
            prev->nextEdge = temp->nextEdge;
        }

        delete temp;
    }
}

void showMenu() {
    cout << "=== Sistem Pemadam Kebakaran ===" << endl;
    cout << "1. Tambah Daerah" << endl;
    cout << "2. Tambah Rute" << endl;
    cout << "3. Hapus Daerah" << endl;
    cout << "4. Hapus Rute" << endl;
    cout << "5. Tampilkan Graf" << endl;
    cout << "6. Set Kondisi Jalan" << endl;
    cout << "7. Cari Rute Tercepat" << endl;
    cout << "8. Tampilkan Rute" << endl;
    cout << "9. Tampilkan Daerah" << endl;
    cout << "0. Keluar" << endl;
    cout << "Pilih menu: ";
}
