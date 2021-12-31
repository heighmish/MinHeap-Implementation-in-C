//this file includes the main functions for using a binary min heap
//uses the array implementation where root is stored at 0

#include "minHeap.h"
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

//O(maxSize), creates and allocates memory for a new min heap
minHeap *newMinHeap(int maxSize) {
    minHeap *newheap =  malloc(sizeof(minHeap));
    assert(newheap != NULL);
    newheap->size = 0;
    newheap->maxSize = maxSize;
    newheap->arr = malloc(maxSize * sizeof(minHeapNode));
    for (int i = 0; i<maxSize; i++) {
        newheap->arr[i] = NULL;
    }
    return newheap;
}


//allocates memory for new node in array
//O(1)
minHeapNode *newMinHeapNode(int distance, int value) {
    minHeapNode *newNode = malloc(sizeof(minHeapNode));
    assert(newNode != NULL);
    newNode->dist = distance;
    newNode->v = value;
    newNode->pos = -1;
    return newNode;
}


//returns boolean whether heap is empty
//O(1)
int isHeapEmpty(minHeap *heap) {
    return heap->size == 0;
}

//Free memory allocated 
//all heap nodes are freed after use in Dijkstra's algorithm do not need to be freed here
void freeMinHeap(minHeap *heap) {
    assert(heap);
    free(heap->arr);
    free(heap);
}

//swaps the position of two nodes in the array
//O(1)
void swapNode(minHeap *heap, int child, int parent) {
    minHeapNode *temp = heap->arr[parent];
    heap->arr[parent] = heap->arr[child];
    heap->arr[parent]->pos = parent;
    heap->arr[child] = temp;
    heap->arr[child]->pos = child;
}

//Insert node at end of list
//Then upheaps the node to its position, upheap takes at maximum log(n) where n is the depth of the heap
// O(log n)
minHeapNode *insertHeap(minHeap *heap, int distance, int value) {
    minHeapNode *newNode = newMinHeapNode(distance, value); //create new node
    if (heap->size == 0) { //heap is empty
        heap->arr[0] = newNode; //set first node of array to newNode
        newNode->pos = 0; 
    } else {
        heap->arr[heap->size] = newNode; //set last node of array to newNode position
        int parNodeInt = floor(((heap->size)-1)/2); //this is the position of the parent in array representation
        int newNodeInt = heap->size; // this is the first location of any newly added node
        newNode->pos = newNodeInt;        
        minHeapNode *parNode = heap->arr[parNodeInt]; //parent node is guaranteed to exist as this is not the first node in the array
        while (parNode->dist > newNode->dist) { //while parent is larger than newNode, maximum Log(n)
            swapNode(heap, newNodeInt, parNodeInt); //swap newNode upwards
            newNodeInt = parNodeInt; //position in array of newnode is now the position of the previous parent node
            parNodeInt = floor(((newNodeInt)-1)/2); //update parent position
            parNode = heap->arr[parNodeInt]; //update parent node
        }
    }
    heap->size++; //post increment size
    
    return newNode;
}


minHeapNode *removeMin(minHeap *heap) { //remove root, put last (size) node into root and downheap
    assert(!isHeapEmpty(heap));
    minHeapNode *retNode = heap->arr[0], *lastNode = heap->arr[heap->size-1];
    heap->arr[heap->size-1] = NULL;
    heap->arr[0] = lastNode;
    heap->size--;
    //downheap-
    int stillLarger = 1;
    int lastNodeInt = 0;
    lastNode->pos = 0;
    int i = 0;
    while (stillLarger) {
        int leftChildInt = calculateLeftChild(lastNodeInt), rightChildInt = calculateRightChild(lastNodeInt);       
        minHeapNode *leftChild = NULL, *rightChild = NULL;                                                                                                                                   
        if (leftChildInt > heap->size || rightChildInt > heap->size) {
            stillLarger = 0;
        } else {
            leftChild = heap->arr[leftChildInt], rightChild = heap->arr[rightChildInt];
        }
        if (leftChild == NULL && rightChild == NULL) { //nothing to swap with break loop
            stillLarger = 0;
        } else if (leftChild == NULL && rightChild != NULL) {
            if (lastNode->dist > rightChild->dist) {
                swapNode(heap, rightChildInt, lastNodeInt);
                lastNodeInt = rightChildInt;
            } else { //neither is larger
                stillLarger = 0;
            }
        } else if (leftChild != NULL && rightChild == NULL) {
            if (lastNode->dist > leftChild->dist) {
                swapNode(heap, leftChildInt, lastNodeInt);
                lastNodeInt = leftChildInt;
            } else { //left is not larger
                stillLarger = 0;
            }
        } else if (leftChild != NULL && rightChild != NULL) {
            if (leftChild->dist <= rightChild->dist) { //left is smaller
                swapNode(heap, leftChildInt, lastNodeInt);
                lastNodeInt = leftChildInt;
            } else if (rightChild->dist < leftChild->dist) { //right is smaller
                swapNode(heap, rightChildInt, lastNodeInt);
                lastNodeInt = rightChildInt;
            } else { //neither is larger
                stillLarger = 0;
            }
        } else {
            stillLarger = 0;
        }
    }
    return retNode;
    
}

int calculateLeftChild(int s) {
    int leftChildInt;
    leftChildInt = ((s+1)*2)-1;
    return leftChildInt;
}

int calculateRightChild(int s) {
    int rightChildInt;
    rightChildInt = ((s+1)*2);
    return rightChildInt;
}

void upHeap(minHeap *heap, minHeapNode *upHeapNode) {
    int parNodeInt = floor(((upHeapNode->pos)-1)/2); //this is the position of the parent in array representation
    int newNodeInt = upHeapNode->pos; // this is the first location of any newly added node
    minHeapNode *parNode = heap->arr[parNodeInt]; //parent node is guaranteed to exist as this is not the first node in the array
    while (parNode->dist > upHeapNode->dist) { //while parent is larger than newNode, maximum Log(n)
        swapNode(heap, newNodeInt, parNodeInt); //swap newNode upwards
        newNodeInt = parNodeInt; //position in array of newnode is now the position of the previous parent node
        parNodeInt = floor(((newNodeInt)-1)/2); //update parent position
        parNode = heap->arr[parNodeInt]; //update parent node
    }
}


void printHeap(minHeap *heap) {
    for (int i=0; i<heap->size; i++) {
        putchar('\n');
        printf("%d,%d, i:%d pos:%d", heap->arr[i]->dist, heap->arr[i]->v, i, heap->arr[i]->pos);
        putchar('\n');
    }
}



//test main for testing min binary heap
/*
int main() {
    minHeap *H = newMinHeap(100);
    minHeapNode *node;
    //insertHeap(H, 5, 10);
    //minHeapNode *min = removeMin(H);
    //printf("%d", min->dist);
    for (int i = 10; i > 0; i--) {
        node = insertHeap(H, i, i);
    }
    //printHeap(H);
    
    while (!isHeapEmpty(H)) {
        minHeapNode *min = removeMin(H);
        printf("%d", min->dist);
        //printHeap(H);
        putchar('\n');
    } 
    //printHeap(H);
    return 0;
}
*/