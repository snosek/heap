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

void swim(Heap *heap, int idx) {
    while (idx > 0 && heap->tree[parent(idx)] < heap->tree[idx]) {
        swap(&heap->tree[parent(idx)], &heap->tree[idx]);
        idx = parent(idx);
    }
}

void sink(Heap *heap, int idx) {
    while (left(idx) < heap->len) {
        int larger_child = left(idx);
        if (right(idx) < heap->len && heap->tree[right(idx)] > heap->tree[left(idx)]) {
            larger_child = right(idx);
        }
        if (heap->tree[idx] >= heap->tree[larger_child]) {
            break;
        }
        swap(&heap->tree[idx], &heap->tree[larger_child]);
        idx = larger_child;
    }
}

void heapify (Heap *heap) {
    for (int i = heap->len/2; i >= 0; i--) {
        sink(heap, i);
    }
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
    heapify(heap);
    return heap;
}

void heap_sort(int *arr, size_t len) {
    Heap *heap = init_heap(arr, len);
    for (int i = len - 1; i >= 0; i--) {
        arr[i] = heap->tree[0];
        heap->tree[0] = heap->tree[i];
        heap->len--;
        sink(heap, 0);
    }
    free(heap->tree);
    free(heap);
}

void print_arr(int arr[], int len) {
    for (int i = 0; i < len; i++) {
        printf("%i ", (arr[i]));
    }
    printf("\n");
}

int main(void) {
    int arr[] = { 2, 8, 5, 55, 89, 233, 610, 34, 377, 144, 1, 21, 3, 1, 13 };
    int len = sizeof(arr)/sizeof(arr[0]);

    printf("Unsorted array: ");
    print_arr(arr, len);
    printf("Sorted array: ");
    heap_sort(arr, len);
    print_arr(arr, len);

    return 0;
}
