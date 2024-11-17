#include <stdio.h>

// Structure to represent a node in the decision tree
typedef struct {
    int level, value, weight;
    float bound;
} Node;

// Function to calculate the upper bound on the maximum value
float calculate_bound(int level, int weight, int value, int n, int capacity, int weights[], int values[]) {
    if (weight >= capacity) return 0;

    float bound = value;
    int total_weight = weight;

    for (int i = level; i < n; i++) {
        if (total_weight + weights[i] <= capacity) {
            total_weight += weights[i];
            bound += values[i];
        } else {
            bound += (float)(capacity - total_weight) * values[i] / weights[i];
            break;
        }
    }
    return bound;
}

void knapsack_branch_and_bound(int weights[], int values[], int n, int capacity) {
    Node current, next;
    int max_value = 0;

    // Initialize root node
    current.level = -1;
    current.value = 0;
    current.weight = 0;
    current.bound = calculate_bound(0, 0, 0, n, capacity, weights, values);

    Node queue[100]; // Queue for BFS
    int front = 0, rear = 0;
    queue[rear++] = current;

    while (front < rear) {
        current = queue[front++];
        if (current.level == n - 1) continue;

        // Include the next item
        next.level = current.level + 1;
        next.weight = current.weight + weights[next.level];
        next.value = current.value + values[next.level];
        if (next.weight <= capacity && next.value > max_value) {
            max_value = next.value;
        }
        next.bound = calculate_bound(next.level + 1, next.weight, next.value, n, capacity, weights, values);
        if (next.bound > max_value) {
            queue[rear++] = next;
        }

        // Exclude the next item
        next.weight = current.weight;
        next.value = current.value;
        next.bound = calculate_bound(next.level + 1, next.weight, next.value, n, capacity, weights, values);
        if (next.bound > max_value) {
            queue[rear++] = next;
        }
    }

    printf("Maximum value (Branch and Bound): %d\n", max_value);
}

int main() {
    int values[] = {60, 100, 120};
    int weights[] = {10, 20, 30};
    int capacity = 50;
    int n = sizeof(values) / sizeof(values[0]);

    knapsack_branch_and_bound(weights, values, n, capacity);

    return 0;
}
