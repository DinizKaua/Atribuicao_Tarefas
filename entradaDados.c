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
    //MOSTRANDO MATRIZ APOS SUBTRACOES
    printf("Matriz subtraida pelo menor elemento em linhas e colunas:\n");
    for (int i = 0; i<tam; i++){
        for (int j = 0; j<tam; j++){
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }    
    }

//2° ETAPA DO ALGORÍTIMO - VERIFICAR DESIGNAÇÃO
int verif_designacao(int **matriz, int tam, int *designados){

    // VETORES QUE IDENTIFICAM LINHAS E COLUNAS DESIGNADAS
    int linha[tam], coluna[tam]; 
     for(int i = 0; i<tam; i++){
        linha[i] = 0;
        coluna[i] = 0;
    }

    // "COBRINDO" OS ZEROS E PEGANDO O ENDEREÇO DELES
    int contador = 0;
    for(int i = 0; i<tam;i++){ 
        for(int j = 0; j<tam;j++){
            if(linha[j] == 0 && coluna[j] == 0 && matriz[i][j] == 0){
                designados[i] = j;
                linha[j] = 1;
                coluna[j] = 1;
                contador++;
                break;
            }

        }
    }
    //IMPRIMINDO O ENDEREÇO DOS ZEROS DESIGINADOS (-1 não tem designação)
    printf("Endereco dos zeros designados\n");
    for(int i = 0; i<tam;i++){
        printf("%d ", designados[i]);
    }

    if(contador == tam) return 1;
    else return 0;
}

int main(){
    //ABRINDO ARQUIVO
    FILE *arquivo = fopen("C:\\Users\\willy\\Desktop\\Atribuicao_Tarefas\\teste.txt","r");
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

    //LENDO E MOSTRANDO MATRIZ DO ARQUIVO
    printf("Matriz lida:\n");
    for (int i = 0; i<tam; i++){
        for (int j = 0; j<tam; j++){
            fscanf(arquivo, "%d", &pontmat[i][j]);
            printf("%d ", pontmat[i][j]);
        }
        printf("\n");
    }
    
    //CHAMANDO A ETAPA 1
    subtraimatriz(pontmat,tam);

    //CHAMANDO A ETAPA DOIS
    int *zerosDesignados = (int*) malloc(tam*sizeof(int)); //endereço dos zeros designados
    for(int i = 0; i<tam;i++){
        zerosDesignados[i] = -1;
    }
    verif_designacao(pontmat, tam, zerosDesignados);  

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