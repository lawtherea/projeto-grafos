// kosaraju/main.cpp
#include <bits/stdc++.h>
using namespace std;

void dfs(int v, vector<bool>& visited, vector<vector<int>>& graph, stack<int>& order) {
    visited[v] = true;
    for (int u : graph[v])
        if (!visited[u])
            dfs(u, visited, graph, order);
    order.push(v);
}

void dfs_reverse(int v, vector<bool>& visited, vector<vector<int>>& graph_rev, vector<int>& component) {
    visited[v] = true;
    component.push_back(v);
    for (int u : graph_rev[v])
        if (!visited[u])
            dfs_reverse(u, visited, graph_rev, component);
}

void kosaraju(int V, vector<vector<int>>& graph, vector<vector<int>>& graph_rev, vector<vector<int>>& components) {
    vector<bool> visited(V + 1, false);
    stack<int> order;

    for (int i = 1; i <= V; ++i)
        if (!visited[i])
            dfs(i, visited, graph, order);

    fill(visited.begin(), visited.end(), false);

    while (!order.empty()) {
        int v = order.top(); order.pop();
        if (!visited[v]) {
            vector<int> component;
            dfs_reverse(v, visited, graph_rev, component);
            components.push_back(component);
        }
    }
}

void showHelp() {
    cout << "Help\n";
    cout << "-h: mostra help\n";
    cout << "-o <arquivo>: redireciona a saida para o arquivo\n";
    cout << "-f <arquivo>: le o grafo do arquivo\n";
}

int main(int argc, char** argv) {
    string input_file = "", output_file = "null";

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-h") == 0) {
            showHelp();
            return 0;
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            output_file = argv[++i];
        } else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            input_file = argv[++i];
        }
    }

    if (input_file.empty()) {
        cout << "Sem input especificado. Use o parametro -f\n";
        return 1;
    }

    ifstream fin(input_file);
    if (!fin) {
        cerr << "Não foi possível abrir o arquivo de input: " << input_file << "\n";
        return 1;
    }

    int V, E;
    fin >> V >> E;
    vector<vector<int>> graph(V + 1), graph_rev(V + 1), components;

    for (int i = 0; i < E; ++i) {
        int u, v;
        fin >> u >> v;
        graph[u].push_back(v);
        graph_rev[v].push_back(u);
    }

    kosaraju(V, graph, graph_rev, components);

    if (output_file != "null") {
        ofstream fout(output_file);
        if (!fout) {
            cerr << "Não foi possível abrir o arquivo de saída: " << output_file << "\n";
            return 1;
        }
        for (auto& cfc : components) {
            for (size_t i = 0; i < cfc.size(); ++i) {
                fout << cfc[i] << (i + 1 < cfc.size() ? " " : "");
            }
            fout << "\n";
        }
    } else {
        for (auto& cfc : components) {
            for (int v : cfc)
                cout << v << " ";
            cout << "\n";
        }
    }

    return 0;
}