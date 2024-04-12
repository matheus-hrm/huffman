#include "header.h"
#include "huff.c"

/*
    Aluno: Matheus Henrique Rodrigues Magalhães
    Matricula: 202103760
    Disciplina: AED2, 
    Exercício: Algoritmo de Huffman

    Para implementação desse algoritmo utilizei minHeap, a motivação por trás disso é 
    obter os números que aparecem em menor frequência na arvore com mais facilidade,
    os números que menos aparecerem na mensagem irão para os nós mais a esquerda e os
    que mais aparecem a direita, construindo a árvore de baixo pra cima e somando o valor dos nós.
    Após isso o código irá gerar uma tabela onde cada caracter corresponde a um número binário salvo
    em um array, o programa por sua vez irá atravessar a árvore construindo a mensagem final em forma
    binária de acordo com a direção dos nós filhos da árvore, o programa no entanto funciona apenas 
    de forma ilustrativa, já que não comprime de fato o tamanho da frase em bits pois usa um array 
    de char de 8 bytes para guardar os números binários, que são caracteres ASCII.
    
    Compile o arquivo com "gcc -o main main.c"
*/

int main() {
    char msg[100];
    printf("Insira uma mensagem: ");
    fgets(msg, sizeof(msg), stdin);
    msg[strcspn(msg, "\n")] = '\0';  // remove o \n 

    char* codes[256] = {NULL};
    huffmanEncoding(msg, codes);
    printCodes(codes);
    printEncodedMessage(msg, codes);
    freeCodes(codes);
    return 0;
}
