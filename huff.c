#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Aluno: Matheus Henrique Rodrigues Magalhães
    Matricula: 202103760
    Disciplina: AED2, algoritmo de Huffman
*/


Node* newNode(char data, int freq, Node* left, Node* right) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->freq = freq;
    node->left = left;
    node->right = right;
    return node;
}

void minHeapify(Node** minHeap, int size, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && minHeap[left]->freq < minHeap[smallest]->freq)   // se o node esquerdo existe e se seu valor é menor que o atual
        smallest = left;

    if (right < size && minHeap[right]->freq < minHeap[smallest]->freq) // análogo para o node direito
        smallest = right;

    if (smallest != index) {                                   // se o menor não for o indice atual troca com o atual 
        Node* temp = minHeap[index];
        minHeap[index] = minHeap[smallest];
        minHeap[smallest] = temp;
        minHeapify(minHeap, size, smallest);                   // chamamos a função pro novo índice
    }
}

Node* extractMin(Node** minHeap, int* size) {
    Node* temp = minHeap[0];
    minHeap[0] = minHeap[*size - 1];
    (*size)--;
    minHeapify(minHeap, *size, 0);
    return temp;
}

void insertMinHeap(Node** minHeap, int* size, Node* node) {
    (*size)++;
    int i = *size - 1;
    while (i && node->freq < minHeap[(i - 1) / 2]->freq) {
        minHeap[i] = minHeap[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap[i] = node;
}

Node* buildHuffmanTree(char* msg) {
    int freqMap[256] = {0};
    for (int i = 0; msg[i] != '\0'; i++) {
        freqMap[(int)msg[i]]++;
    }

    Node* minHeap[256]; // array de nodes para o minHeap
    int size = 0;
    
    // adiciona os char's que forem não nulos ao minHeap
    for (int i = 0; i < 256; i++) {
        if (freqMap[i] > 0) {
            minHeap[size++] = newNode((char)i, freqMap[i], NULL, NULL);
        }
    }

    for (int i = size / 2 - 1; i >= 0; i--) {
        minHeapify(minHeap, size, i);
    }

    // constroi a arvore combinando os nodes do minHeap
    while (size > 1) {
        Node* left = extractMin(minHeap, &size);
        Node* right = extractMin(minHeap, &size);
        Node* parent = newNode('\0', left->freq + right->freq, left, right);
        insertMinHeap(minHeap, &size, parent);
    }

    return extractMin(minHeap, &size);                      // retorna a raiz 
}

void buildCodes(Node* root, char* code, int index, char** codes) {
    if (root->left == NULL && root->right == NULL) {        // se o node for uma folha, guarda o binario no array
        code[index] = '\0';
        codes[(int)root->data] = strdup(code);
        return;
    }

    code[index] = '0';
    buildCodes(root->left, code, index + 1, codes);

    code[index] = '1';
    buildCodes(root->right, code, index + 1, codes);
}

char** huffmanEncoding(char* msg, char** codes) {
    Node* root = buildHuffmanTree(msg);

    char code[MAX_TREE_HEIGHT];
    buildCodes(root, code, 0, codes);

    return codes;
}

void printCodes(char** codes) {
    printf("Tabela de caracteres:\n");
    for (int i = 0; i < 256; i++) {
        if (codes[i] != NULL) {
            printf("%c: %s\n", (char)i, codes[i]);
        }
    }
}

void freeCodes(char** codes) {
    for (int i = 0; i < 256; i++) {
        free(codes[i]);
    }
    free(codes);
}
void printEncodedMessage(char* msg, char** codes) {
    printf("Mensagem comprimida: ");
    for (int i = 0; msg[i] != '\0'; i++) {
        printf("%s", codes[(int)msg[i]]);
    }
    printf("\n");
}
