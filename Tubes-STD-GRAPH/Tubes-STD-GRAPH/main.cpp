//
//  main.cpp
//  Tubes-STD-GRAPH
//
//  Created by Rakha Fatih Athallah on 20/12/24.
//
#include "graph.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    graph G;
    buildGraph(G);
    int pilihan;
    string asal, tujuan, namaDaerah;
    int jarak;
    bool kondisi;

    do {
        showMenu();
        cin >> pilihan;
        cin.ignore(); // Membersihkan input buffer

        switch (pilihan) {
            case 1:
                cout << "Masukkan nama daerah baru: ";
                getline(cin, namaDaerah);
                addVertex(G, namaDaerah);
                cout << "Daerah " << namaDaerah << " berhasil ditambahkan.\n";
                break;

            case 2:
                cout << "Masukkan asal: ";
                getline(cin, asal);
                cout << "Masukkan tujuan: ";
                getline(cin, tujuan);
                cout << "Masukkan jarak (meter): ";
                cin >> jarak;
                cin.ignore();
                addEdge(G, asal, tujuan, jarak);
                cout << "Rute dari " << asal << " ke " << tujuan << " berhasil ditambahkan.\n";
                break;

            case 3:
                cout << "Masukkan nama daerah yang akan dihapus: ";
                getline(cin, namaDaerah);
                deleteDaerah(G, namaDaerah);
                cout << "Daerah " << namaDaerah << " berhasil dihapus.\n";
                break;

            case 4:
                cout << "Masukkan asal: ";
                getline(cin, asal);
                cout << "Masukkan tujuan: ";
                getline(cin, tujuan);
                deleteRute(G, asal, tujuan);
                cout << "Rute dari " << asal << " ke " << tujuan << " berhasil dihapus.\n";
                break;

            case 5:
                cout << "Graf saat ini:\n";
                showGraph(G);
                break;

            case 6:
                cout << "Masukkan asal: ";
                getline(cin, asal);
                cout << "Masukkan tujuan: ";
                getline(cin, tujuan);
                cout << "Kondisi jalan (1 untuk bisa dilalui, 0 untuk tidak bisa): ";
                cin >> kondisi;
                cin.ignore();
                setRoadCondition(G, asal, tujuan, kondisi);
                cout << "Kondisi jalan berhasil diperbarui.\n";
                break;

            case 7:
                cout << "Masukkan asal: ";
                getline(cin, asal);
                cout << "Masukkan tujuan: ";
                getline(cin, tujuan);
                findShortestRoute(G, asal, tujuan);
                break;

            case 8:
                cout << "Daftar semua rute:\n";
                showEdge(G);
                break;

            case 9:
                cout << "Daftar semua daerah:\n";
                showVertex(G);
                break;

            case 0:
                cout << "Terima kasih telah menggunakan sistem ini.\n";
                break;

            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }

        cout << endl;
    } while (pilihan != 0);

    return 0;
}
