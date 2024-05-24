#include <stdio.h>
#include  <stdlib.h>

#define parent(idx) ((idx - 1) / 2)
#define left(idx) (2*idx + 1)
#define right(idx) (2*idx + 2)

typedef struct {
    int len;
    int *tree;
} Heap;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int swim(Heap *heap, int idx) {
    if (idx < 0 || idx >= heap->len) {
        return -1;
    }
    while (heap->tree[parent(idx)] < heap->tree[idx]) {
        swap(&heap->tree[parent(idx)], &heap->tree[idx]);
        idx = parent(idx);
    }
    return 0;
}

//  |    |
//  |    |
//  |    |
// \      /      napraw
//  \    /
//   \  /
//    \/
int sink(Heap *heap, int idx) {
    if (idx < 0 || idx >= heap->len) {
        return -1;
    }
    while (heap->tree[parent(idx)] < heap->tree[idx]) {
        int parent = parent(idx);
        swap(&heap->tree[parent(idx)], &heap->tree[idx]);
        idx = parent(idx);
    }
    return 0;
}

void print_heap(Heap *heap) {
    for (int i = 0; i < heap->len; i++) {
        printf("%i ", (heap->tree[i]));
    }
    printf("\n");
}

Heap *init_heap(int *init_list, size_t len) {
    Heap *heap;
    if ((heap = malloc(sizeof(Heap))) == NULL) {
        return NULL;
    }
    if ((heap->tree = malloc(len * sizeof(*heap->tree))) == NULL) {
        free(heap);
        return NULL;
    }

    heap->len = len;
    for (int i = 0; i < len; i++) {
        heap->tree[i] = init_list[i];
    }
    return heap;
}

int main(void) {
    int a[] = { 4, 3, 2, 1, 1, 4, 5 };
    Heap *heap = init_heap(a, 7);

    print_heap(heap);
    if (swim(heap, 6) == -1) {
        return -1;
    }
    print_heap(heap);

    return 0;
}
