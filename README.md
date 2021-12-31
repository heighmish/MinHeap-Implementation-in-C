# MinHeap-Implementation-in-C
Implementation of a array based minimum heap (binary heap) in C that stores a graph node datatype. The Heap stores a custom struct minHeapNode that stores 3 integers, a vertex ID number, a distance value dist and a position number pos that refers to the position of the vertex in the heap. This heap was designed to be used with a graph to perform Dijkstra's shortest path algorithm in O((n+m)log(n)).

In that implementation of Dijstra's, the nodes are freed as they are explored and that is why they are not freed inside the free heap function.
