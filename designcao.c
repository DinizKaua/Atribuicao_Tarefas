#include <stdio.h>
#include <stdlib.h>

int verificaDesignacao(int n, int matriz[n][n]){ //Veririfica se a designação já está correta
    
    int linha[n], coluna[n]; // Vetores que identificam linhas e colunas designadas
    for(int i = 0; i<n; i++){
        linha[i] = 0;
        coluna[i] = 0;
    }

    int contador = 0;
    for(int i = 0; i<n;i++){ // "cobrindo" os zeros
        for(int j = 0; j<n;j++){
            if(linha[j] == 0 && coluna[j] == 0 && matriz[i][j] == 0){
                linha[j] = 1;
                coluna[j] = 1;
                contador++;
                break;
            }

        }
    }
    if(contador == n) return 1;
    else return 0;

}

int main(){
    int n = 4;
    int matriz[4][4] = {{0, 2, 3, 4},
                        {0, 0, 4, 5},
                        {1, 2, 0, 0},
                        {1, 2, 0, 0,}};

    if(verificaDesignacao(n, matriz)){
        printf("ta designada");
    }
    else{
        printf("ta nao o");
    }
    return 0;
}