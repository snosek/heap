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

Heap *init_heap(int *init_list, size_t len) {
    Heap *heap = malloc(sizeof(Heap));
    if (heap == NULL) {
        return NULL;
    }
    if ((heap->tree = malloc(len * sizeof(*heap->tree))) == NULL) {
        free(heap);
        return NULL;
    }

    heap->size = len;
    for (int i = 0; i < len; i++) {
        heap->tree[i] = init_list[i];
    }
    return heap;
}

int main(void) {
    int a[] = {1,1,2,3,5,8};
    Heap *heap = init_heap(a, 6);
    print_heap(heap);
    swim(heap, 3);
    print_heap(heap);
    return 0;
}
