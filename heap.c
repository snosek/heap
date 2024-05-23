#include <stdio.h>
#include  <stdlib.h>

#define parent(idx) ((idx - 1) / 2)
#define left(idx) (2*idx + 1)
#define right(idx) (2*idx + 2)

typedef struct {
    int size;
    int *tree;
} Heap;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swim(Heap *heap, int idx) {
    while (heap->tree[parent(idx)] < heap->tree[idx]) {
        swap(&heap->tree[parent(idx)], &heap->tree[idx]);
        idx = parent(idx);
    }
}

void sink(Heap *heap, int idx) {
    while (heap->tree[parent(idx)] < heap->tree[idx]) {
        int parent = parent(idx);
        swap(&heap->tree[parent(idx)], &heap->tree[idx]);
        idx = parent(idx);
    }
}

void print_heap(Heap *heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%i ", (heap->tree[i]));
    }
    printf("\n");
}

int main(void) {
    Heap *heap = malloc(sizeof(Heap));
    heap->tree = malloc(7 * sizeof(int));
    heap->size = 7;
    int arr[7] = {7,6,5,4,3,2,1};
    heap->tree = arr;
    print_heap(heap);

    print_heap(heap);
    return 0;
}
