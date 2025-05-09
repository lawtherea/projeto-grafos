// kruskal/main.cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <fstream>
using namespace std;

vector<int> fathers;

int find(int x) {
    if (fathers[x] == x) return x;
    return fathers[x] = find(fathers[x]);
}

void unite(int x, int y) {
    int fx = find(x);
    int fy = find(y);
    if (fx != fy) fathers[fx] = fy;
}

void showHelp() {
    cout << "Help:" << endl;
    cout << "-h: mostra o help" << endl;
    cout << "-o <arquivo>: redireciona a saida para o arquivo" << endl;
    cout << "-f <arquivo>: indica o 'arquivo' que contem o grafo de entrada" << endl;
    cout << "-s: mostra a solucao (em ordem crescente)" << endl;
}

int main(int argc, char **argv) {
    string input_file = "", output_file = "";
    bool show_solution = false;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-h") == 0) {
            showHelp();
            return 0;
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) output_file = argv[++i];
        else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) input_file = argv[++i];
        else if (strcmp(argv[i], "-s") == 0) show_solution = true;
    }

    if (input_file.empty()) {
        cerr << "Sem input especificado. Use o parametro -f" << endl;
        return 1;
    }

    ifstream fin(input_file);
    if (!fin) {
        cerr << "Nao foi possivel abrir o arquivo de input: " << input_file << endl;
        return 1;
    }

    int n, m;
    fin >> n >> m;
    vector<pair<int, pair<int, int>>> edgeList;
    fathers.resize(n + 1);
    for (int i = 0; i <= n; ++i) fathers[i] = i;

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        fin >> u >> v >> w;
        edgeList.emplace_back(w, make_pair(u, v));
    }

    sort(edgeList.begin(), edgeList.end());
    vector<pair<int, int>> mst;
    int total_weight = 0;

    for (auto& [w, e] : edgeList) {
        int u = e.first, v = e.second;
        if (find(u) != find(v)) {
            unite(u, v);
            mst.emplace_back(u, v);
            total_weight += w;
        }
    }

    ostream* out;
    ofstream fout;
    if (!output_file.empty()) {
        fout.open(output_file);
        if (!fout) {
            cerr << "Nao foi possivel abrir o arquivo de output: " << output_file << endl;
            return 1;
        }
        out = &fout;
    } else {
        out = &cout;
    }

    if (show_solution) {
        for (size_t i = 0; i < mst.size(); ++i) {
            *out << "(" << mst[i].first << "," << mst[i].second << ")";
            if (i + 1 < mst.size()) *out << " ";
        }
        *out << endl;
    } else {
        *out << total_weight << endl;
    }

    return 0;
}