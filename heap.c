#include <stdio.h>
#include  <stdlib.h>

#define parent(idx) ((idx - 1) / 2)
#define left(idx) (2*idx + 1)
#define right(idx) (2*idx + 2)

#define RED "\x1b[31m"
#define COLOR_RESET "\x1b[0m"
#define printerr(msg) (printf(RED msg COLOR_RESET "\n"))

typedef struct {
    int len;
    int *tree;
} Heap;

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

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int swim(Heap *heap, int idx) {
    if (idx < 0 || idx >= heap->len) {
        printerr("Swim error: invalid index.");
        return -1;
    }
    while (idx > 0 && heap->tree[parent(idx)] < heap->tree[idx]) {
        swap(&heap->tree[parent(idx)], &heap->tree[idx]);
        idx = parent(idx);
    }
    return 0;
}

int sink(Heap *heap, int idx) {
    if (idx < 0 || idx >= heap->len) {
        printerr("Sink error: invalid index.");
        return -1;
    }

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
    return 0;
}

int heapify (Heap *heap) {
    for (int i = heap->len/2; i >= 0; i--) {
        sink(heap, i);
    }
    return 0;
}

int heap_sort(int *arr, size_t len) {
    Heap *heap = init_heap(arr, len);
    heapify(heap);

    for (int i = len - 1; i > 0; i--) {
        swap(&heap->tree[0], &heap->tree[i]);
        heap->len--;
        sink(heap, 0);
    }

    for (int i = 0; i < len; i++) {
        arr[i] = heap->tree[i];
    }

    free(heap->tree);
    free(heap);
    return 0;
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
