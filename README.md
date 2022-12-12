# Implementação de uma estrutura de dados para manipular Grafos 
- Ler um arquivo .txt contendo um grafo
- Gerar um arquivo .txt contendo um grafo 
- Gerar matriz de adjacências 
- Calcular e mostrar o grau de cada vértice 
- Encontrar uma árvore geradora mínima 
- Mostrar distancias dos caminhos mais curtos de um vértice para todos outros usando Dijkstra

# Formato do arquivo .txt contendo um grafo

- Primeira linha: 
num_vertices num_arestas *tipo* *valorado*

- Linhas seguintes:
vi vj *peso*

#

- Obs:
*tipo* será G para grafo não dirigido e D para grafo dirigido
*valorado* será 1 para grafo valorado e 0 para grafo não valorado
*peso* é opcional e só existirá para grafo ponderado
Arestas ou arcos paralelos aparecerão mais de uma vez no arquivo
