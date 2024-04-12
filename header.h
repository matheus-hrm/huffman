#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HEIGHT 100


typedef struct Node {
    char data;
    int freq;
    struct Node* left;
    struct Node* right;
} Node;


Node* newNode(char data, int freq, Node* left, Node* right);
Node* extractMin(Node** minHeap, int* size) ;
Node* buildHuffmanTree(char* msg) ;

char** huffmanEncoding(char* msg, char** codes) ;

void minHeapify(Node** minHeap, int size, int index) ;
void insertMinHeap(Node** minHeap, int* size, Node* node) ;
void buildCodes(Node* root, char* code, int index, char** codes) ;
void printCodes(char** codes) ;
void printEncodedMessage(char* msg, char** codes) ;
void freeCodes(char** codes) ;

#endif