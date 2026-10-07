#include <stdio.h>
#include <stdlib.h>

#define SIZE 5 // Maximum size of the queue

int queue[SIZE];
int front = -1, rear = -1;

// Check if the queue is full
int isFull() {
    if ((front == 0 && rear == SIZE - 1) || (front == rear + 1)) {
        return 1;
    }
    return 0;
}

// Check if the queue is empty
int isEmpty() {
    if (front == -1) {
        return 1;
    }
    return 0;
}

// Function to add an element to the queue
void enqueue(int value) {
    if (isFull()) {
        printf("Queue is full! Cannot enqueue %d\n", value);
    } else {
        if (front == -1) front = 0;
        rear = (rear + 1) % SIZE;
        queue[rear] = value;
        printf("Enqueued: %d\n", value);
    }
}

// Function to remove an element from the queue
void dequeue() {
    if (isEmpty()) {
        printf("Queue is empty! Cannot dequeue.\n");
    } else {
        printf("Dequeued: %d\n", queue[front]);
        if (front == rear) {
            front = -1;
            rear = -1; // Reset queue if empty
        } else {
            front = (front + 1) % SIZE;
        }
    }
}

// Function to display the queue
void display() {
    if (isEmpty()) {
        printf("Queue is empty!\n");
    } else {
        int i;
        printf("Queue elements: ");
        for (i = front; ; i = (i + 1) % SIZE) {
            printf("%d ", queue[i]);
            if (i == rear) break;
        }
        printf("\n");
    }
}

// Main function to demonstrate queue operations
int main() {
    printf("=== DEMONSTRASI QUEUE ===\n");
    enqueue(10);
    enqueue(20);
    enqueue(30);
    display();

    dequeue();
    display();

    enqueue(40);
    enqueue(50);
    enqueue(60); // This will show "Queue is full" or circular behavior depending on implementation
    display();

    return 0;
}