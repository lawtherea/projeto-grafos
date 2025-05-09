#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <fstream>
using namespace std;

int max_size = 0;
vector<int> current_best_clique;
vector<int> path, best_clique;

void read_graph(ifstream &fin, vector<vector<int>> &graph, int m) {
    for (int i = 0; i < m; i++) {
        int u, v;
        fin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
}

void clique(vector<int> V, int size, vector<vector<int>> graph) {
    if (V.empty()) {
        if (size > max_size) {
            max_size = size;
            best_clique = path;
        }
        return;
    }

    while (!V.empty()) {
        if (size + V.size() <= max_size) {
            return;
        }

        int v = V[0];
        V.erase(V.begin());
        path.push_back(v);

        vector<int> new_V;
        for (int i : V) {
            if (find(graph[v].begin(), graph[v].end(), i) != graph[v].end()) {
                new_V.push_back(i);
            }
        }

        clique(new_V, size + 1, graph);
        path.pop_back();
    }
}

int main(int argc, char **argv) {
    string input_file = "";
    string output_file = "";

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            cout << "Help:" << endl;
            cout << "-h: mostra o help" << endl;
            cout << "-o <arquivo>: redireciona a saida para o arquivo" << endl;
            cout << "-f <arquivo>: indica o 'arquivo' que contem o grafo de entrada" << endl;
            return 0;
        } else if (strcmp(argv[i], "-o") == 0 && i < argc - 1) output_file = argv[++i];
        else if (strcmp(argv[i], "-f") == 0 && i < argc - 1) input_file = argv[++i];
    }

    if (input_file == "") {
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

    vector<vector<int>> graph(n + 1);
    read_graph(fin, graph, m);
    fin.close();

    vector<int> V;
    for (int i = 1; i <= n; i++) V.push_back(i);

    sort(V.begin(), V.end(), [&graph](int u, int v) {
        return graph[u].size() < graph[v].size();
    });

    clique(V, 0, graph);

    sort(best_clique.begin(), best_clique.end());

    cout << "Tamanho do clique: " << max_size << endl;
    cout << "Clique Maxima Encontrada: ";
    for (int i : best_clique) cout << i << " ";
    cout << endl;

    if (!output_file.empty()) {
        ofstream fout(output_file);
        fout << "Tamanho do clique: " << max_size << endl;
        fout << "Clique Maxima Encontrada: ";
        for (int i : best_clique) fout << i << " ";
        fout << endl;
        fout.close();
    }

    return 0;
}