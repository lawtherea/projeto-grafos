// dijkstra/main.cpp
#include <bits/stdc++.h>
using namespace std;

void dijkstra(vector<vector<int>> &grafo, vector<int> &dist, vector<int> &pre, vector<vector<int>> &pesos)
{
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> fila; 
    fila.push({0, 1});

    while(!fila.empty())
    {
        int u = fila.top().second;
        int dist_ate_u = fila.top().first;
        fila.pop();

        if(dist_ate_u <= dist[u])
        {
            for(auto v : grafo[u])
            {
                int peso_uv = pesos[u][v];
                if(dist[u] + peso_uv < dist[v])
                {
                    dist[v] = dist[u] + peso_uv;
                    pre[v] = u;
                    fila.push({dist[v], v});
                }
            }
        }
    }
}

void showHelp() {
    cout << "Help:" << endl;
    cout << "-h: mostra o help" << endl;
    cout << "-o <arquivo>: redireciona a saida para o arquivo" << endl;
    cout << "-f <arquivo>: indica o 'arquivo' que contem o grafo de entrada" << endl;
    cout << "-i: vertice inicial" << endl;
}

int main(int argc, char **argv)
{
    string input_file = "", output_file = "";
    int vert_inicial = 1;

    for(int i = 1; i < argc; i++) 
    {
        if (strcmp(argv[i], "-h") == 0) {
            showHelp();
            return 0;
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) output_file = argv[++i];
        else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) input_file = argv[++i];
        else if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) vert_inicial = atoi(argv[++i]);
    }

    if (input_file.empty()) {
        cerr << "Sem input especificado. Use o parametro -f" << endl;
        return 1;
    }

    ifstream fin(input_file);
    if (!fin) {
        cerr <<  "Nao foi possivel abrir o arquivo de input: " << input_file << endl;
        return 1;
    }

    int n, m;
    fin >> n >> m;
    vector<vector<int>> pesos(n + 1, vector<int>(n + 1, numeric_limits<int>::max()));
    vector<vector<int>> grafo(n + 1);

    for(int i = 1; i <= m; i++) {
        int u, v, peso;
        fin >> u >> v >> peso;
        if(u < 0 || v < 0 || peso < 0) {
            cout << "Entrada invalida !" << endl;
            return 0;
        }
        grafo[u].push_back(v);
        grafo[v].push_back(u);
        pesos[u][v] = peso;
        pesos[v][u] = peso;
    }

    vector<int> dist(n + 1, numeric_limits<int>::max());
    dist[vert_inicial] = 0;
    vector<int> pre(n + 1, -1);

    fin.close();

    dijkstra(grafo, dist, pre, pesos);

    if (!output_file.empty()) {
        ofstream fout(output_file);
        if (!fout) {
            cerr << "Nao foi possivel abrir o arquivo de output: " << output_file << endl;
            return 1;
        }
        for(int i = 1; i <= n; i++) {
            if(dist[i] == numeric_limits<int>::max()) dist[i] = -1;
            fout << i << ":" << dist[i] << endl;
        }
        fout.close();
    } else {
        for(int i = 1; i <= n; i++) {
            if(dist[i] == numeric_limits<int>::max()) dist[i] = -1;
            cout << i << ":" << dist[i];
            if(i != n) cout << " ";
            else cout << endl;
        }
    }

    return 0;
}