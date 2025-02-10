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

// 2° ETAPA DO ALGORÍTIMO - REALIZAR E VERIFICAR DESIGAÇÃO

// BUSCA VIA DFS PARA ATRIBUIÇÃO DE UMA COLUNA PARA LINHA
int dfs(int linha, int tam, int **matriz, int *linhasdesignadas, int *colunasvisitadas) {
    for (int coluna = 0; coluna < tam; coluna++) {
        
        if (matriz[linha][coluna] == 0 && !colunasvisitadas[coluna]) {
            colunasvisitadas[coluna] = 1;  // MARCA AS COLUNAS VISITADAS COM 1
            // SE A LINHA ESTIVER DESIGNADA ELE PROCURA OUTRA QUE POSSA DESIGNAR
            if (linhasdesignadas[coluna] == -1 || dfs(linhasdesignadas[coluna], tam, matriz, linhasdesignadas, colunasvisitadas)) {
                linhasdesignadas[coluna] = linha;  // ATRIBUI A COLUNA À LINHA
                return 1;
            }
        }
    }
    return 0;
}

int verif_designacao(int **matriz, int tam, int *designados) {//TENTA FAZER UMA ATRIBUIÇÃO ÓTIMA
    for (int i = 0; i < tam; i++) {
        designados[i] = -1;
    }
    // VETOR guarda[j] GUARDA A LINHA ATUALMENTE DESIGNADA À COLUNA j
    int *guarda = malloc(tam * sizeof(int));
    if (guarda == NULL) {
        printf("Erro de alocacao.\n");
        return 0;
    }
    for (int j = 0; j < tam; j++) {
        guarda[j] = -1;
    }
    
    int contalinhas = 0;  // CONTADOR DE LINHAS ATRIBUIDAS
    
    // PARA CADA LINHA, TENTA ENCONTRAR UMA COLUNA COM ZERO QUE POSSA SER ATRIBUÍDA
    for (int linha = 0; linha < tam; linha++) {
        // VETOR PARA MARCAR QUAIS COLUNAS JÁ FORAM VISITADAS 
        int *visitados = calloc(tam, sizeof(int));
        if (visitados == NULL) {
            printf("Erro de alocacao.\n");
            free(guarda);
            return 0;
        }
        if (dfs(linha, tam, matriz, guarda, visitados)) {
            contalinhas++;
        }
        free(visitados);
    }
    
    // SE O CASAMENTO MÁXIMO ENCONTROU UMA DESIGNAÇÃO PARA TODAS AS LINHAS, INVERTE O MAPEAMENTO, PARA QUE designados[i] SEJA A COLUNA ATRIBUÍDA À LINHA i
    for (int col = 0; col < tam; col++) {
        if (guarda[col] != -1) {
            designados[guarda[col]] = col;
        }
    }
    
    /* IMPRIMINDO O ENDEREÇO DOS ZEROS DESIGINADOS (-1 não tem designação)
    printf("\nEndereco dos zeros designados: ");
    for (int i = 0; i < tam; i++) {
        printf("%d ", designados[i]);
    }
    printf("\n\n");
    */
    
    free(guarda);
    
    if (contalinhas == tam)
        return 1;
    else
        return 0;
}

// 3° ETAPA DO ALGORÍTIMO - REDUÇÃO ADICIONAL DA MATRIZ

void cobrimento(int **matriz, int tam, int *designados){

    int *linhasMarcadas = (int*)calloc(tam, sizeof(int));
    int *colunasMarcadas =(int*)calloc(tam, sizeof(int));
    if(linhasMarcadas == NULL || colunasMarcadas == NULL){
        printf("Erro de alocacao.\n");
        return;
    }
    
    // MARCAR LINHAS SEM NENHUM ZERO DESIGNADO
    for(int i = 0; i<tam; i++){
        if(designados[i] == -1) linhasMarcadas[i] = 1;
    }

    while(1){ // ESSSES PASSOS VÃO SE REPETIR ATE QUE NÃO HAJA NADA MAIS A SER MARCADO
   
    // MARCAR COLUNAS COM ZEROS NÃO DESIGNADO
    int ctd = 0;
    for(int i = 0; i<tam; i++){
        if(linhasMarcadas[i] == 1){
            for(int j = 0; j<tam;j++){
                if(matriz[i][j] == 0 && designados[i] != j && colunasMarcadas[j] != 1){
                    colunasMarcadas[j] = 1;
                    ctd++;
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
                    ctd++;
                    }
                 }
             }
         }
         if(ctd==0) break;
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
    int menorValor = INT_MAX; 
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
    free(linhasMarcadas);
    free(colunasMarcadas);
    /*EXIBINDO A MATRIZ RESULTANTE
    for(int i = 0; i<tam; i++){
        for(int j = 0; j<tam;j++){
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }*/
}

int main(){
    //ABRINDO ARQUIVO
    FILE *arquivo = fopen("assign800.txt","r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    //LENDO TAMANHO DA MATRIZ
    int tam;
    fscanf(arquivo, "%d", &tam);
    
    //ALOCANDO ESPACO DINAMICAMENTE PARA A MATRIZ A SER LIDA DO ARQUIVO E UMA CÓPIA DELA
    int **pontmat = (int**)calloc(tam, sizeof(int*));
    int **matrizCopia = (int**)calloc(tam, sizeof(int*));

    if(pontmat == NULL || matrizCopia == NULL){
        printf("Erro de alocacao.\n");
        fclose(arquivo);
        return -1;
    }

    for (int i = 0; i<tam; i++){
        pontmat[i]=calloc(tam, sizeof(int));
        matrizCopia[i]=calloc(tam, sizeof(int));

        if(pontmat[i] == NULL || matrizCopia[i] == NULL){
            printf("Erro de alocacao\n");
            fclose(arquivo);
            return -1;
        } 
    }

    //LENDO, MOSTRANDO MATRIZ DO ARQUIVO E ATRIBUINDO VALORES A CÓPIA DESSA MATRIZ
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

    //CHAMANDO A ETAPA 2 E 3
    int *zerosDesignados = (int*) malloc(tam*sizeof(int)); //endereço dos zeros designados
    if(zerosDesignados == NULL){
        printf("Erro de alocacao\n");
        return -1;
    }
    
    while(verif_designacao(pontmat, tam, zerosDesignados)==0){ // a ideia é que enquanto a designação não funcione, ele reduza mais
        cobrimento(pontmat, tam, zerosDesignados);
    }
    
    // SOMANDO OS TEMPOS COM O ENDEREÇO DAS DESIGNAÇÕES
    long int somaTempo = 0;
    for(int i = 0; i<tam;i++){
        if(zerosDesignados[i] == -1)somaTempo += 0;
        else somaTempo += matrizCopia[i][zerosDesignados[i]]; 
    }
    
    // EXIBINDO A SOMA TOTAL DE UNIDADES DE TEMPO
    printf("Resultado: %ld\n", somaTempo);

    //LIBERANDO MEMÓRIA ALOCADA PARA A MATRIZ E ARRAYS
    for (int i = 0; i<tam; i++){
        free(pontmat[i]);
        free(matrizCopia[i]);
    }
    free(pontmat);
    free(matrizCopia);
    free(zerosDesignados);
    
    //FECHANDO ARQUIVO
    fclose(arquivo);
    return 0;
}