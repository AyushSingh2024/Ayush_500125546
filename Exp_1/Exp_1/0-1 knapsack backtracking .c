#include <stdio.h>

int max_value = 0; // To store the maximum value

void knapsack_backtracking(int n, int weights[], int values[], int capacity, int index, int current_value, int current_weight) {
    if (current_weight > capacity) {
        return; // If weight exceeds capacity, stop exploring
    }

    if (current_value > max_value) {
        max_value = current_value; // Update max value
    }

    if (index >= n) {
        return; // All items processed
    }

    // Include the current item
    knapsack_backtracking(n, weights, values, capacity, index + 1, current_value + values[index], current_weight + weights[index]);

    // Exclude the current item
    knapsack_backtracking(n, weights, values, capacity, index + 1, current_value, current_weight);
}

int main() {
    int values[] = {60, 100, 120};
    int weights[] = {10, 20, 30};
    int capacity = 50;
    int n = sizeof(values) / sizeof(values[0]);

    knapsack_backtracking(n, weights, values, capacity, 0, 0, 0);

    printf("Maximum value (Backtracking): %d\n", max_value);

    return 0;
}

