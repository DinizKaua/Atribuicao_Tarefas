#include <stdio.h>
#include <limits.h>
#include <stdlib.h>


// 1° ETAPA DO ALGORÍTIMO - CONSISTE EM REDUZIR A MATRIZ
void subtraimatriz(int **matriz, int tam){
    //ENCONTRAR O MENOR ELEMENTO EM CADA LINHA
    for (int i = 0; i <tam; i++){
        int menorlinha = matriz[i][0];
        for (int j = 1; j<tam; j++){
            if (matriz[i][j]<menorlinha){
                menorlinha = matriz[i][j];
            }
        }
        //SUBTRAIR CADA ELEMENTO DA LINHA PELO MENOR ENCONTRADO
        for (int j = 0; j<tam; j++){
            matriz[i][j] -= menorlinha;
        }
    }
    //ENCONTRAR O MENOR ELEMENTO EM CADA COLUNA
    for (int j = 0; j<tam; j++){
        int menorcoluna = matriz[0][j];
        for (int i = 1; i<tam; i++){
            if (matriz[i][j]<menorcoluna){
                menorcoluna = matriz[i][j];
            }
        }
        //SUBTRAIR CADA ELEMENTO DA COLUNA PELO MENOR ENCONTRADO
        for (int i = 0; i<tam; i++){
            matriz[i][j]-=menorcoluna;
        }
    }
    /* MOSTRANDO MATRIZ APOS SUBTRACOES
    printf("Matriz subtraida pelo menor elemento em linhas e colunas:\n");
    for (int i = 0; i<tam; i++){
        for (int j = 0; j<tam; j++){
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }*/
          
}

/*
   Função auxiliar que, dada uma linha (row), tenta encontrar (via DFS)
   uma atribuição de coluna (col) para essa linha, possivelmente “desfazendo”
   uma atribuição anterior se necessário.
   
   Parâmetros:
   - row: índice da linha atual.
   - tam: tamanho da matriz (número de linhas/colunas).
   - matriz: matriz de custos (ou benefícios), onde zeros indicam candidatos à atribuição.
   - match: vetor de tamanho 'tam' onde match[j] indica qual linha está designada à coluna j (ou -1 se nenhuma).
   - visited: vetor auxiliar para marcar quais colunas já foram visitadas nesta chamada.
   
   Retorna 1 (verdadeiro) se foi possível encontrar/ajustar uma atribuição para a linha 'row';
   caso contrário, retorna 0.
*/
int dfs(int row, int tam, int **matriz, int *match, int *visited) {
    for (int col = 0; col < tam; col++) {
        // Se há um zero na posição (row, col) e essa coluna ainda não foi visitada
        if (matriz[row][col] == 0 && !visited[col]) {
            visited[col] = 1;  // marca a coluna como visitada
            // Se a coluna não está designada ou se conseguimos "desalocar" a linha que estava designada
            if (match[col] == -1 || dfs(match[col], tam, matriz, match, visited)) {
                match[col] = row;  // atribui a coluna 'col' à linha 'row'
                return 1;
            }
        }
    }
    return 0;
}

/*
   Função verif_designacao – tenta encontrar uma atribuição ótima dos zeros usando
   um algoritmo de casamento bipartido. Se for possível designar uma coluna (com zero)
   para cada linha, retorna 1; caso contrário, retorna 0.
   
   Parâmetros:
   - matriz: matriz quadrada de inteiros (geralmente o resultado de operações prévias do método húngaro).
   - tam: dimensão da matriz.
   - designados: vetor de tamanho 'tam' que, ao final, conterá, para cada linha i, o índice da coluna designada
     (ou -1 se a linha não tiver sido atribuída).
*/
int verif_designacao(int **matriz, int tam, int *designados) {
    // Inicializa o vetor de designações para as linhas com -1 (nenhuma designação)
    for (int i = 0; i < tam; i++) {
        designados[i] = -1;
    }
    
    // Vetor 'match' para as colunas: match[j] guarda a linha atualmente designada à coluna j
    int *match = malloc(tam * sizeof(int));
    if (match == NULL) {
        printf("Erro de alocacao.\n");
        return 0;
    }
    for (int j = 0; j < tam; j++) {
        match[j] = -1;
    }
    
    int matchingCount = 0;  // contador de linhas que foram atribuídas
    
    // Para cada linha, tenta encontrar (via DFS) uma coluna com zero que possa ser atribuída
    for (int row = 0; row < tam; row++) {
        // Vetor para marcar quais colunas já foram visitadas nesta iteração
        int *visited = calloc(tam, sizeof(int));
        if (visited == NULL) {
            printf("Erro de alocacao.\n");
            free(match);
            return 0;
        }
        if (dfs(row, tam, matriz, match, visited)) {
            matchingCount++;
        }
        free(visited);
    }
    
    // Se o casamento máximo encontrou uma designação para todas as linhas, inverte o mapeamento
    // para que designados[i] seja a coluna atribuída à linha i.
    for (int col = 0; col < tam; col++) {
        if (match[col] != -1) {
            designados[match[col]] = col;
        }
    }
    
    /* Imprime os endereços (índices) dos zeros designados (-1 indica que a linha não foi atribuída)
    printf("\nEndereco dos zeros designados: ");
    for (int i = 0; i < tam; i++) {
        printf("%d ", designados[i]);
    }
    printf("\n\n");
    */
    
    free(match);
    
    // Se conseguimos designar todas as linhas, retorna 1; caso contrário, retorna 0.
    if (matchingCount == tam)
        return 1;
    else
        return 0;
}


// 3° ETAPA DO ALGORÍTIMO - REDUÇÃO ADICIONAL DA MATRIZ
void cobrimento(int **matriz, int tam, int *designados){

    int linhasMarcadas[tam], colunasMarcadas[tam];
    for(int i = 0; i<tam;i++){
        linhasMarcadas[i] = 0;
        colunasMarcadas[i] = 0;
    }
    
    // MARCAR LINHAS SEM NENHUM ZERO DESIGNADO
    for(int i = 0; i<tam; i++){
        if(designados[i] == -1) linhasMarcadas[i] = 1;
    }

    while(1){ // ESSSES PASSOS VÃO SE REPETIR ATE QUE NÃO HAJA NADA MAIS A SER MARCADO
   
    // MARCAR COLUNAS COM ZEROS NÃO DESIGNADO
    int ctd1 = 0, ctd2 = 0;
    for(int i = 0; i<tam; i++){
        if(linhasMarcadas[i] == 1){
            for(int j = 0; j<tam;j++){
                if(matriz[i][j] == 0 && designados[i] != j && colunasMarcadas[j] != 1){
                    colunasMarcadas[j] = 1;
                    ctd1++;
                }
            }
        }
    }
    // NAS COLUNAS MARCADAS, MARCAR LINHAS COM ZEROS DESIGNADOS
    for(int j = 0; j < tam; j++){
        if(colunasMarcadas[j] == 1){
            for(int i = 0; i<tam; i++){
                if(designados[i] == j && linhasMarcadas[i] != 1){
                    linhasMarcadas[i] = 1;
                    ctd2++;
                    }
                 }
             }
         }
         if(ctd1 == 0 && ctd2==0) break;
    }

    /* EXIBINDO LINHAS E COLUNAS MARCADAS
    printf("Linhas marcadas: \n");
    for(int i = 0; i<tam; i++){
        printf("%d ", linhasMarcadas[i]);
    }
    printf("\ncolunas marcadas: \n");
    for(int i = 0; i<tam; i++){
        printf("%d ", colunasMarcadas[i]);
    }
    printf("\n");
    */

    // ENCONTRANDO MENOR VALOR MARCADO NA MATRIZ 
    int menorValor = INT_MAX; //gambiarra
    for(int i = 0; i<tam; i++){
        if(linhasMarcadas[i] == 1){
            for(int j = 0; j<tam;j++){
                if(colunasMarcadas[j] == 0)
                    if(matriz[i][j] < menorValor) menorValor = matriz[i][j];
            }
        }
    }
    //printf("\no menor valor: %d\n\n", menorValor);

    // SUBTRAINDO O MENOR VALOR
    for(int i = 0; i<tam; i++){
        if(linhasMarcadas[i] == 1){
            for(int j = 0; j<tam;j++){
                if(colunasMarcadas[j] == 0 && matriz[i][j]!=0) 
                    matriz[i][j] -= menorValor;
            }
        }
    }

    //SOMAR AOS ELEMENTOS QUE NÃO SÃO MARCADOS NEM NA COLUNA E NEM NA LINHA
    for(int i = 0; i<tam;i++){
        if(linhasMarcadas[i]==0){
            for(int j = 0; j<tam;j++){
                if(colunasMarcadas[j] == 1){
                    matriz[i][j] += menorValor;
                }
            }
        }
    }
    /*exibindo a matriz resultante
    for(int i = 0; i<tam; i++){
        for(int j = 0; j<tam;j++){
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }*/
}

int main(){
    //ABRINDO ARQUIVO
    FILE *arquivo = fopen("../assign600.txt","r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    //LENDO TAMANHO DA MATRIZ
    int tam;
    fscanf(arquivo, "%d", &tam);
    
    //ALOCANDO ESPACO DINAMICAMENTE PRA MATRIZ A SER LIDA DO ARQUIVO
    int **pontmat;
    pontmat = (int**)malloc(tam*sizeof(int*));
    for (int i = 0; i<tam; i++){
        pontmat[i]=malloc(tam*sizeof(int));
    }

    //LENDO, MOSTRANDO MATRIZ DO ARQUIVO E CRIANDO UMA CÓPIA ESTÁTICA DESSA MATRIZ
    int matrizCopia[tam][tam];
    //printf("Matriz lida:\n");
    for (int i = 0; i<tam; i++){
        for (int j = 0; j<tam; j++){
            fscanf(arquivo, "%d", &pontmat[i][j]);
            matrizCopia[i][j] = pontmat[i][j];
            //printf("%d ", pontmat[i][j]);
        }
        //printf("\n");
    }
    
    //CHAMANDO A ETAPA 1
    subtraimatriz(pontmat,tam);

    //CHAMANDO A ETAPA DOIS E A TRÊS
    int *zerosDesignados = (int*) malloc(tam*sizeof(int)); //endereço dos zeros designados
    
    while(verif_designacao(pontmat, tam, zerosDesignados)==0){ // a ideia é que enquanto a designação não funcione, ele reduza mais
        cobrimento(pontmat, tam, zerosDesignados);
    }
    
    // SOMANDO OS TEMPOS COM O ENDEREÇO DAS DESIGNAÇÕES
    int somaTempo = 0;
    for(int i = 0; i<tam;i++){
        if(zerosDesignados[i] == -1)somaTempo += 0;
        else somaTempo += matrizCopia[i][zerosDesignados[i]]; 
    }

    // EXIBINDO A SOMA TOTAL DE UNIDADES DE TEMPO
    printf("Resultado: %d\n", somaTempo);

    //LIBERANDO MEMORIA ALOCADA PARA A MATRIZ E ARRAYS
    for (int i = 0; i<tam; i++){
        free(pontmat[i]);
    }
    free(pontmat);
    free(zerosDesignados);
    
    //FECHANDO ARQUIVO
    fclose(arquivo);
    return 0;
}