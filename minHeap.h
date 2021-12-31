#ifndef MINHEAP_H
#define MINHEAP_H

typedef struct minHeapNode {
    int v; //value (vertex)
    int dist; //key
    int pos; //position in the heap, array index
} minHeapNode;



typedef struct minHeap {
    int size;
    int maxSize;
    minHeapNode **arr;
} minHeap;

minHeap *newMinHeap(int maxSize);
minHeapNode *newMinHeapNode(int distance, int value);
int isHeapEmpty(minHeap *heap);
void freeMinHeap(minHeap *heap);
void swapNode(minHeap *heap, int child, int parent);
minHeapNode *insertHeap(minHeap *heap, int distance, int value);
void printHeap(minHeap *heap);
minHeapNode *removeMin(minHeap *heap);
int calculateRightChild(int s);
int calculateLeftChild(int s);
void upHeap(minHeap *heap, minHeapNode *upHeapNode);
void freeMinHeapNode(minHeapNode *node);


#endif