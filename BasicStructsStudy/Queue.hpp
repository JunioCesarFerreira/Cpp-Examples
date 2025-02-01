#include <stdio.h>

#define MAX_SIZE_QUEUE 100  // Tamanho máximo da fila

class Queue {
private:
    int arr[MAX_SIZE_QUEUE];
    int rear;
    
public:
    Queue() {
        rear = 0;
    }
    
    bool isEmpty() {
        return rear == 0;
    }
    
    bool isFull() {
        return rear == MAX_SIZE_QUEUE - 1;
    }
    
    void enqueue(int value) {
        if (isFull()) {
            printf("Fila cheia!\n");
        } else {
            arr[rear] = value;
            rear++;
        }
    }
    
    int dequeue() {
        if (isEmpty()) {
            printf("Fila vazia!\n");
            return -1;
        } else {
            int dequeuedValue = arr[0];
            for (int i=0; i < rear; i++) {
                arr[i] = arr[i+1];
            }
            rear--;
            return dequeuedValue;
        }
    }
    
    int peek() {
        if (isEmpty()) {
            printf("Fila vazia!\n");
            return -1;
        } else {
            return arr[0];
        }
    }
};