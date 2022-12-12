#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int numVertices;
    int numArestas;
    char tipo;
    int isValorado;
    int *arestas;
    int *pesos;
    int coluna;
} sGRAFO;

FILE *abreGrafo();

void menu(int opcao);

sGRAFO lerGrafo(FILE *grafo);

sGRAFO gerarGrafo();

void printGrafo(sGRAFO grafoInfo);

void calculaGrau(FILE *grafo);

void calculaGrauDirigido(sGRAFO grafoInfo);

void calculaGrauNaoDirigido(sGRAFO grafoInfo);

void gerarMatrizAdj(FILE *grafo);

void dijkstra(FILE *grafo);

int minDistance(const int dist[], const bool sptSet[], sGRAFO grafoinfo);

void primMST(FILE *grafo);

int minKey(const int chave[], const bool mstSet[], sGRAFO grafoinfo);

int main() {
    int opcao;

    do {
        printf("=-------- Menu --------=\n");
        printf("[1] Ler um grafo (.txt)\n");
        printf("[2] Gerar um grafo (.txt)\n");
        printf("[3] Converter lista e matriz de adjacencias\n");
        printf("[4] Calcular o grau de cada vertice\n");
        printf("[5] Encontrar arvore geradora minima\n");
        printf("[6] Encontrar caminho mais curto por Dijkstra\n");
        printf("[0] Sair\n");
        scanf("%d", &opcao);

        menu(opcao);
    } while (opcao != 0);

    return 0;
}

FILE *abreGrafo() {
    FILE *grafo;
    char filename[50];

    do {
        printf("Digite o nome do arquivo: ");
        scanf("%s", filename);
        printf("\n");
    } while ((grafo = fopen(filename, "r")) == NULL);

    return grafo;
}

void printGrafo(sGRAFO grafoInfo) {
    printf("%d %d %c %d\n", grafoInfo.numVertices, grafoInfo.numArestas, grafoInfo.tipo, grafoInfo.isValorado);

    grafoInfo.coluna = 2;
    if (grafoInfo.isValorado)
        grafoInfo.coluna = 3;

    for (int i = 0; i < grafoInfo.numArestas; ++i) {
        for (int j = 0; j < grafoInfo.coluna; j++) {
            if ((j+1) % 3 == 0){
                printf("%d", grafoInfo.pesos[i]);
                continue;
            }
            printf("%d ", grafoInfo.arestas[i + grafoInfo.numArestas * j]);

        }
        printf("\n");
    }
}

void menu(int opcao) {
    sGRAFO grafoInfo;
    FILE *grafo;

    switch (opcao) {
        case 1:
            grafo = abreGrafo();
            grafoInfo = lerGrafo(grafo);
            printGrafo(grafoInfo);
            printf("\n");
            fclose(grafo);
            break;
        case 2:
            grafoInfo = gerarGrafo();
            printGrafo(grafoInfo);
            printf("\n");
            break;
        case 3:
            grafo = abreGrafo();
            gerarMatrizAdj(grafo);
            fclose(grafo);
            break;
        case 4:
            grafo = abreGrafo();
            calculaGrau(grafo);
            fclose(grafo);
            break;
        case 5:
            grafo = abreGrafo();
            primMST(grafo);
            fclose(grafo);
            break;
        case 6:
            grafo = abreGrafo();
            dijkstra(grafo);
            fclose(grafo);
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida...\n");
            break;
    }
}

sGRAFO lerGrafo(FILE *grafo) {
    sGRAFO grafoInfo;
    fscanf(grafo, "%d %d %c %d", &grafoInfo.numVertices, &grafoInfo.numArestas, &grafoInfo.tipo, &grafoInfo.isValorado);

    grafoInfo.coluna = 2;
    if (grafoInfo.isValorado)
        grafoInfo.coluna = 3;

    grafoInfo.arestas = (int *) malloc(sizeof(int) * grafoInfo.coluna * grafoInfo.numArestas);
    grafoInfo.pesos = (int *) malloc(sizeof(int) * grafoInfo.numArestas);

    if (!grafoInfo.isValorado) {
        for (int i = 0; i < grafoInfo.numArestas; ++i) {
            grafoInfo.pesos[i] = 1;
        }
    }

    for (int i = 0; i < grafoInfo.numArestas; i++) {
        for (int j = 0; j < grafoInfo.coluna; j++) {
            if ((j + 1) == 3) {
                fscanf(grafo, "%d", &grafoInfo.pesos[i]);
            } else {
                fscanf(grafo, "%d", &grafoInfo.arestas[i + grafoInfo.numArestas * j]);
            }
        }
    }

    return grafoInfo;
}

sGRAFO gerarGrafo() {
    sGRAFO grafoInfo;

    FILE *grafo;

    char filename[50], tipo;
    int num = 0, numVertices = 0, numArestas = 0, isValorado;

    int buff = 0;

    do {
        if(buff != 0)
            printf("Nome ja esta em uso, tente novamente.\n");
        printf("Digite o nome do arquivo: ");
        scanf("%s", filename);
        printf("\n");
        buff++;
    } while ((grafo = fopen(filename, "r")) != NULL);

    grafo = fopen(filename, "w+");

    printf("Digite o numero de vertices, arestas, tipo e se eh valorado: \n");
    scanf("%d", &numVertices);
    scanf("%d", &numArestas);
    scanf(" %[^\n]%*c", &tipo);
    scanf("%d", &isValorado);

    fprintf(grafo, "%d %d %c %d\n", numVertices, numArestas, tipo, isValorado);
    grafoInfo.numVertices = numVertices;
    grafoInfo.numArestas = numArestas;
    grafoInfo.tipo = tipo;
    grafoInfo.isValorado = isValorado;

    grafoInfo.coluna = 2;
    if (grafoInfo.isValorado)
        grafoInfo.coluna = 3;

    grafoInfo.arestas = (int *) malloc(sizeof(int) * grafoInfo.coluna * grafoInfo.numArestas);

    for (int i = 0; i < grafoInfo.numArestas; ++i) {
        printf("Digite os valores da aresta %d: ", i+1);
        for (int j = 0; j < grafoInfo.coluna; j++) {
            scanf("%d", &num);
            grafoInfo.arestas[i + grafoInfo.numArestas * j] = num;
            fprintf(grafo, "%d ", grafoInfo.arestas[i + grafoInfo.numArestas * j]);
        }
        fprintf(grafo, "\n");
    }

    fclose(grafo);
    return grafoInfo;
}

void calculaGrau(FILE *grafo) {
    sGRAFO grafoInfo;

    grafoInfo = lerGrafo(grafo);

    grafoInfo.coluna = 2;
    if (grafoInfo.isValorado)
        grafoInfo.coluna = 3;

    if (grafoInfo.tipo == 'D') {
        calculaGrauDirigido(grafoInfo);
    } else {
        calculaGrauNaoDirigido(grafoInfo);
    }
}

void calculaGrauDirigido(sGRAFO grafoInfo) {
    int vet[grafoInfo.numVertices][2];

    for (int i = 0; i < grafoInfo.numVertices; i++)
        for (int j = 0; j < 2; j++)
            vet[i][j] = 0;

    for (int i = 0; i < grafoInfo.numArestas; ++i) {
        for (int j = 0; j < grafoInfo.coluna; j++) {
            if (j == 0) {
                vet[((grafoInfo.arestas[i + grafoInfo.numArestas * j]) - 1)][0]++;
            } else {
                vet[((grafoInfo.arestas[i + grafoInfo.numArestas * j]) - 1)][1]++;
            }
        }
    }

    for (int i = 0; i < grafoInfo.numVertices; i++) {
        printf("Vertice %d:\nGrau de Saida %d; Grau de Entrada %d\n\n", i + 1, vet[i][0], vet[i][1]);
    }
}

void calculaGrauNaoDirigido(sGRAFO grafoInfo) {
    int vet[grafoInfo.numVertices];

    for (int i = 0; i < grafoInfo.numVertices; i++)
        vet[i] = 0;

    for (int i = 0; i < grafoInfo.numArestas; ++i) {
        for (int j = 0; j < grafoInfo.coluna; j++) {
            vet[((grafoInfo.arestas[i + grafoInfo.numArestas * j]) - 1)]++;
        }
    }

    for (int i = 0; i < grafoInfo.numVertices; i++) {
        printf("Vertice %d:\nGrau %d\n\n", i + 1, vet[i]);
    }
}

void gerarMatrizAdj(FILE *grafo) {
    sGRAFO grafoInfo;

    grafoInfo = lerGrafo(grafo);

    grafoInfo.coluna = 2;
    if (grafoInfo.isValorado)
        grafoInfo.coluna = 3;

    int matrizAdj[grafoInfo.numVertices][grafoInfo.numVertices];

    for (int i = 0; i < grafoInfo.numVertices; ++i) {
        for (int j = 0; j < grafoInfo.numVertices; ++j) {
            matrizAdj[i][j] = 0;
        }
    }

    for (int i = 0; i < grafoInfo.numArestas; ++i) {
        matrizAdj[((grafoInfo.arestas[i + grafoInfo.numArestas * 0]) - 1)][((grafoInfo.arestas[i + grafoInfo.numArestas * 1]) - 1)] = grafoInfo.pesos[i];
        if(grafoInfo.tipo == 'G')
            matrizAdj[((grafoInfo.arestas[i + grafoInfo.numArestas * 1]) - 1)][((grafoInfo.arestas[i + grafoInfo.numArestas * 0]) - 1)] = grafoInfo.pesos[i];
    }

    for (int i = 0; i < grafoInfo.numVertices; ++i) {
        for (int j = 0; j < grafoInfo.numVertices; ++j) {
            printf("%d\t", matrizAdj[i][j]);
        }
        printf("\n");
    }
}


void dijkstra(FILE *grafo) {
    sGRAFO grafoInfo;

    grafoInfo = lerGrafo(grafo);

    int src = 0, matrizAdj[grafoInfo.numVertices][grafoInfo.numVertices];

    for (int i = 0; i < grafoInfo.numVertices; ++i) {
        for (int j = 0; j < grafoInfo.numVertices; ++j) {
            matrizAdj[i][j] = 0;
        }
    }

    for (int i = 0; i < grafoInfo.numArestas; ++i) {
        matrizAdj[((grafoInfo.arestas[i + grafoInfo.numArestas * 0]) - 1)][((grafoInfo.arestas[i + grafoInfo.numArestas * 1]) - 1)] = grafoInfo.pesos[i];
        if(grafoInfo.tipo == 'G')
            matrizAdj[((grafoInfo.arestas[i + grafoInfo.numArestas * 1]) - 1)][((grafoInfo.arestas[i + grafoInfo.numArestas * 0]) - 1)] = grafoInfo.pesos[i];
    }

    for (int i = 0; i < grafoInfo.numVertices; ++i) {
        for (int j = 0; j < grafoInfo.numVertices; ++j) {
            printf("%d\t", matrizAdj[i][j]);
        }
        printf("\n");
    }

    printf("Digite o vertice fonte: ");
    scanf("%d", &src);
    src--;
    printf("\n");

    int dist[grafoInfo.numVertices];
    bool sptSet[grafoInfo.numVertices];

    for (int i = 0; i < grafoInfo.numVertices; i++){
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }
    dist[src] = 0;

    for (int i = 0; i < grafoInfo.numVertices - 1; i++) {
        int u = minDistance(dist, sptSet, grafoInfo);

        sptSet[u] = true;

        for (int j = 0; j < grafoInfo.numVertices; j++) {
            if (!sptSet[j] && matrizAdj[u][j] && dist[u] != INT_MAX && dist[u] + matrizAdj[u][j] < dist[j])
                dist[j] = dist[u] + matrizAdj[u][j];
        }
    }

    for (int i = 0; i < grafoInfo.numVertices; i++)
        printf("Vertice: %d; Dist da fonte: %d\n", i+1, dist[i]);
}

int minDistance(const int dist[], const bool sptSet[], sGRAFO grafoInfo) {
    int min = INT_MAX, minIndex = 0;

    for (int v = 0; v < grafoInfo.numVertices; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], minIndex = v;

    return minIndex;
}

void primMST(FILE *grafo) {
    sGRAFO grafoInfo;

    grafoInfo = lerGrafo(grafo);

    int matrizAdj[grafoInfo.numVertices][grafoInfo.numVertices];

    for (int i = 0; i < grafoInfo.numVertices; ++i) {
        for (int j = 0; j < grafoInfo.numVertices; ++j) {
            matrizAdj[i][j] = 0;
        }
    }

    for (int i = 0; i < grafoInfo.numArestas; ++i) {
        matrizAdj[((grafoInfo.arestas[i + grafoInfo.numArestas * 0]) - 1)][((grafoInfo.arestas[i + grafoInfo.numArestas * 1]) - 1)] = grafoInfo.pesos[i];
        if(grafoInfo.tipo == 'G')
            matrizAdj[((grafoInfo.arestas[i + grafoInfo.numArestas * 1]) - 1)][((grafoInfo.arestas[i + grafoInfo.numArestas * 0]) - 1)] = grafoInfo.pesos[i];
    }

    /*for (int i = 0; i < grafoInfo.numVertices; ++i) {
        for (int j = 0; j < grafoInfo.numVertices; ++j) {
            printf("%d\t", matrizAdj[i][j]);
        }
        printf("\n");
    }*/

    int prim[grafoInfo.numVertices];
    int chave[grafoInfo.numVertices];
    bool mstSet[grafoInfo.numVertices];

    for (int i = 0; i < grafoInfo.numVertices; i++) {
        chave[i] = INT_MAX;
        mstSet[i] = false;
    }
    chave[0] = 0;
    prim[0] = -1;

    for (int i = 0; i < grafoInfo.numVertices - 1; i++) {
        int u = minKey(chave, mstSet, grafoInfo);

        mstSet[u] = true;

        for (int j = 0; j < grafoInfo.numVertices; j++) {
            if (matrizAdj[u][j] && mstSet[j] == false && matrizAdj[u][j] < chave[j]) {
                prim[j] = u;
                chave[j] = matrizAdj[u][j];
            }
        }
    }

    printf("Arestas: \n");
    for (int i = 1; i < grafoInfo.numVertices; i++)
        printf("%d---%d\n", prim[i], i);
}

int minKey(const int chave[], const bool mstSet[], sGRAFO grafoInfo) {
    int min = INT_MAX, minIndex;

    for (int v = 0; v < grafoInfo.numVertices; v++)
        if (mstSet[v] == false && chave[v] < min)
            min = chave[v], minIndex = v;

    return minIndex;
}