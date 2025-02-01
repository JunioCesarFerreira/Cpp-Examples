#include <stdio.h>

#define MAX_SIZE_STACK 100  // Tamanho máximo da pilha

class Stack {
private:
    int arr[MAX_SIZE_STACK];
    int top;
    
public:
    Stack() {
        top = -1;
    }
    
    bool isEmpty() {
        return top == -1;
    }
    
    bool isFull() {
        return top == MAX_SIZE_STACK - 1;
    }
    
    void push(int value) {
        if (!isFull()) {
            arr[++top] = value;
        } else {
            printf("Pilha cheia!\n");
        }
    }
    
    int pop() {
        if (!isEmpty()) {
            return arr[top--];
        } else {
            printf("Pilha vazia!\n");
            return -1; // Indica que não há elementos para remover
        }
    }
    
    int peek() {
        if (!isEmpty()) {
            return arr[top];
        } else {
            printf("Pilha vazia!\n");
            return -1;
        }
    }
};