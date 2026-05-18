#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *data;  
    int capacity;
    int size;
} MinHeap;

MinHeap *heap_create(int capacity)
{
    MinHeap *heap = malloc(sizeof(MinHeap));
    heap->data = malloc(sizeof(int) * capacity);
    if (!heap->data) {
        free(heap);
        return NULL;
    }
    heap->capacity = capacity;
    heap->size = 0;
    return heap;
}

void heap_destroy(MinHeap *heap)
{
    free(heap->data);
    free(heap);
}

int parent(int i) 
{ 
    return (i - 1) / 2; 
}

int left_child(int i) 
{ 
    return 2 * i + 1; 
}

int right_child(int i) 
{ 
    return 2 * i + 2; 
}

void swap(int *a, int *b) 
{ 
    int tmp = *a; *a = *b; *b = tmp; 
}

void fix_up(MinHeap *heap, int idx)
{
    while (idx > 0 && heap->data[parent(idx)] > heap->data[idx]) {
        swap(&heap->data[parent(idx)], &heap->data[idx]);
        idx = parent(idx);
    }
}

void fix_down(MinHeap *heap, int idx)
{
    int smallest = idx;
    int left = left_child(idx);
    int right = right_child(idx);
    while (left < heap->size && heap->data[left] < heap->data[idx]) 
        smallest = idx;
    while (right < heap->size && heap->data[right] < heap->data[idx]) 
        smallest = right;
    if (smallest != idx) {
        swap(&heap->data[smallest], &heap->data[idx]);
        fix_down(heap, smallest);
    }
		
}

bool push(MinHeap *heap, int val)
{
    if (heap->size >= heap->capacity) {
        int new_capacity = heap->capacity * 2;
        int *new_data = realloc(heap->data, sizeof(int) * new_capacity);
        if (!new_data) 
            return false;
        heap->data = new_data;
        heap->capacity = new_capacity;
    }
    heap->data[heap->size++] = val;
    fix_up(heap, heap->size - 1);
    return true;
}

int pop(MinHeap *heap)
{
    if (heap->size <= 0) 
        exit(1);
    int root = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    fix_down(heap, 0);
    return root;
}

int peek(MinHeap *heap) 
{ 
    return heap->data[0]; 
}

int size(MinHeap *heap) 
{ 
    return heap->size; 
}

bool is_empty(MinHeap *heap) 
{ 
    return heap->size == 0; 
}
