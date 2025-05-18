# Teoria dos Grafos | Instituto de Computação - UFAL

## 📌 Descrição

Este projeto foi desenvolvido como parte da disciplina de **Teoria dos Grafos**, do curso de Ciência da Computação da **Universidade Federal de Alagoas (UFAL)**.

O trabalho consiste na implementação de cinco algoritmos fundamentais em grafos, abordando problemas clássicos como:
- Caminhos mínimos
- Árvores geradoras mínimas
- Componentes fortemente conexas
- Clique máxima

Todos os algoritmos foram implementados em **C++**, com entrada padronizada por linha de comando, estrutura modular, `Makefile` para compilação e suporte a testes automatizados via shell script.

---

## 👥 Aluna:
Leila Maria Biggi de Souza Cavalcante

---

## 🧠 Algoritmos Implementados

### 1. Algoritmo de Prim
Constrói a Árvore Geradora Mínima (AGM) de um grafo conectado e ponderado, selecionando arestas de menor peso sem formar ciclos.

### 2. Algoritmo de Kruskal
Encontra a AGM utilizando ordenação de arestas por peso, com união de componentes sem ciclos.

### 3. Algoritmo de Dijkstra
Determina o caminho mínimo de um vértice inicial para os demais vértices em um grafo com pesos não-negativos.

### 4. Algoritmo de Kosaraju
Identifica todas as componentes fortemente conexas de um grafo direcionado por meio de duas passagens de DFS.

### 5. Algoritmo de Carraghan-Pardalos
Resolve o problema da clique máxima, identificando o maior subconjunto de vértices todos mutuamente adjacentes.

---

## 📁 Estrutura do Repositório

```
projeto-grafos/
├── Bat1/                   # Scripts e instâncias para testes automatizados
├── Bat2/                   # Testes automatizados do algoritmo 5
├── carraghan_pardalos/     # Algoritmo 5: clique máxima
├── dijkstra/               # Caminho mínimo
├── kosaraju/               # Componentes fortemente conexas
├── kruskal/                # Árvore geradora mínima
├── prim/                   # Árvore geradora mínima
```

---

## 🚀 Como Executar

### Clonar o repositório:
```bash
git clone https://github.com/lawtherea/projeto-grafos.git
cd projeto-grafos
```

### Compilar um algoritmo:
```bash
cd <nome_algoritmo>
make
```

### Execute com os parâmetros desejados, por exemplo:
```bash
./prim -f entrada.txt -i 1 -s
```

### Parâmetros aceitos:
- `-h`: mostra ajuda
- `-f <arquivo>`: define o arquivo de entrada do grafo
- `-i <vértice>`: define o vértice inicial (quando aplicável)
- `-s`: imprime a solução (arestas ou caminho)
- `-o <arquivo>`: redireciona a saída para um arquivo

---

## 🧪 Rodando os testes automatizados

```bash
cd Bat1
bash Bat1.sh
```

⚠️ Requisitos:
- O script `Bat1.sh` exige `diff` instalado (disponível no Git Bash ou WSL para usuários Windows).
- Certifique-se de que os binários (`*.bin`) foram gerados corretamente com os nomes esperados.

---

## 🧪 Script para testar o algoritmo de Carraghan-Pardalos (Bat2.sh)

Para executar o script, certifique-se de que o executável carraghan_pardalos.exe está na pasta carraghan_pardalos. Em seguida, execute o script Bat2.sh a partir da pasta Bat2:

```bash
bash Bat2.sh
```

O script irá testar o algoritmo de Carraghan-Pardalos em todos os casos de teste disponíveis e comparar as saídas com os gabaritos correspondentes. 

## 📝 Observações

- O algoritmo de Carraghan-Pardalos pode retornar diferentes cliques do mesmo tamanho, dependendo da ordem de visita dos vértices.
- Todos os arquivos foram desenvolvidos conforme as instruções da disciplina.

---

> Projeto acadêmico — Universidade Federal de Alagoas • Instituto de Computação • Teoria dos Grafos
