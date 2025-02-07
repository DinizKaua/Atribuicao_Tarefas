#include <stdio.h>
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
    // MOSTRANDO MATRIZ APOS SUBTRACOES
    printf("Matriz subtraida pelo menor elemento em linhas e colunas:\n");
    for (int i = 0; i<tam; i++){
        for (int j = 0; j<tam; j++){
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }  
    }

//2° ETAPA DO ALGORÍTIMO - VERIFICAR DESIGNAÇÃO
int contZeros(int **matriz, int tam, int indice){ // contar quantidade de zeros da coluna
    int qtdZeros = 0;
    for(int i = 0; i<tam;i++){
        if(matriz[i][indice]==0) qtdZeros++;
    }
    return qtdZeros;
}

int verif_designacao(int **matriz, int tam, int *designados){
      for(int i = 0; i<tam;i++){
        designados[i] = -1;
    }

    // VETORES QUE IDENTIFICAM LINHAS E COLUNAS DESIGNADAS
    int linha[tam], coluna[tam]; 
     for(int i = 0; i<tam; i++){
        linha[i] = 0;
        coluna[i] = 0;
    }

    // "COBRINDO" OS ZEROS E PEGANDO O ENDEREÇO DELES
    int contador = 0;
    for(int i = 0; i<tam;i++){ 
        int temp = -1;
        int aux = tam + 1;
        for(int j = 0; j<tam;j++){
            if(linha[i] == 0 && coluna[j] == 0 && matriz[i][j] == 0){
                if(contZeros(matriz, tam, j)<aux){
                    temp = j;
                    aux = contZeros(matriz, tam, j);
                }             
            }
        }
        
        if(temp != -1) {
            coluna[temp] = 1;
            linha[i] = 1;
            designados[i] = temp;
            contador++;
        }
    }
    // IMPRIMINDO O ENDEREÇO DOS ZEROS DESIGINADOS (-1 não tem designação)
   // printf("\nEndereco dos zeros designados: ");
    for(int i = 0; i<tam;i++){
       // printf("%d ", designados[i]);
    }
   // printf("\n\n");
    
    if(contador == tam) return 1;
    else return 0;
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
    // MARCAR COLUNAS COM ZEROS NÃO DESIGNADOS
    for(int i = 0; i<tam; i++){
        if(linhasMarcadas[i] == 1){
            for(int j = 0; j<tam;j++){
                if(matriz[i][j] == 0) colunasMarcadas[j] = 1;
            }
        }
    }

    // NAS COLUNAS MARCADAS, MARCAR LINHAS COM ZEROS DESIGNADOS
    for(int j = 0; j < tam; j++){
        if(colunasMarcadas[j] == 1){
            for(int i = 0; i<tam; i++){
                if(designados[i] == j){
                    linhasMarcadas[i] = 1;
                }
            }
        }
    }

    // EXIBINDO LINHAS E COLUNAS MARCADAS
   // printf("Linhas marcadas: \n");
    for(int i = 0; i<tam; i++){
        //printf("%d ", linhasMarcadas[i]);
    }
    //printf("\ncolunas marcadas: \n");
    for(int i = 0; i<tam; i++){
        //printf("%d ", colunasMarcadas[i]);
    }
    //printf("\n");

    // ENCONTRANDO MENOR VALOR MARCADO NA MATRIZ 
    int menorValor = 100000; //gambiarra
    for(int i = 0; i<tam; i++){
        if(linhasMarcadas[i] == 1){
            for(int j = 0; j<tam;j++){
                if(colunasMarcadas[j] == 0)
                    if(matriz[i][j] < menorValor && matriz[i][j]!= 0) menorValor = matriz[i][j];
            }
        }
    }

    printf("\no menor valor: %d\n\n", menorValor);

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
    FILE *arquivo = fopen("../assign100.txt","r");
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
    
    /*
    for(int i = 0; i<2; i++){
    verif_designacao(pontmat, tam, zerosDesignados);
    cobrimento(pontmat, tam, zerosDesignados);}
    */
    
    while(verif_designacao(pontmat, tam, zerosDesignados)==0){
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