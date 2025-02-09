Grupo 4, C - Problema de Atribuição de Tarefas

* Instruções para execução do programa.
1 - Nossa entrada de dados é por meio de arquivos no formato txt.
2 - Na linha 217 informe o nome do arquivo no formato "../nome.txt", exemplo "../assign100.txt".
3 - O arquivo deve ser colocado na mesma pasta do arquivo main.c (o qual será executado).

* Detalhes da Implementação
A resolução proposta por nossa equipe foi a implementação
do "Algoritmo Húngaro" ideal para situações de atribuição
de tarefas. Nosso código gira em torno de três passos:

1 - Reduzir a matriz, subtraindo linhas e colunas pelo menor elemento respectivo.

2 - Verificar, por meio de DFS (busca por profundidade), se a matriz reduzida já pode ser designada e assim realizar a designação

3 - Reduzir novamente a matriz sem alterar as designações que estão estáveis caso o passo 2 falhe.

obs: O passo 2 e 3 ficam alternando até que a designação ocorra perfeitamente.

* Considerações finais
Para as matrizes de 3000 adiante não conseguimos realizar o teste, não sei ao certo o motivo, mas imagino que
seja devido ao enorme número de processamentos considerando que o algoritmo húngaro possui tempo de execução O(n^3).

O códifo possui alguns debugs comentados em formato de saída de dados (printf). Optamos por deixa-los, para melhor 
monitoramento se necessário. 


