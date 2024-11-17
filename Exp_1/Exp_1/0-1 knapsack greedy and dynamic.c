#include <stdio.h>
#include <stdlib.h>

// Structure for items
typedef struct {
    int value;
    int weight;
    double ratio; // value-to-weight ratio
} Item;

// Comparator function for sorting items by value-to-weight ratio (descending)
int compare(const void *a, const void *b) {
    Item *item1 = (Item *)a;
    Item *item2 = (Item *)b;
    if (item2->ratio > item1->ratio) return 1;
    if (item2->ratio < item1->ratio) return -1;
    return 0;
}

// Greedy Approach
void knapsack_greedy(int values[], int weights[], int n, int capacity) {
    Item items[n];
    for (int i = 0; i < n; i++) {
        items[i].value = values[i];
        items[i].weight = weights[i];
        items[i].ratio = (double)values[i] / weights[i];
    }
    qsort(items, n, sizeof(Item), compare); // Sort items by ratio
    
    int totalValue = 0, remainingCapacity = capacity;
    printf("Greedy Approach Selected Items:\n");
    for (int i = 0; i < n && remainingCapacity > 0; i++) {
        if (items[i].weight <= remainingCapacity) {
            printf("Weight: %d, Value: %d\n", items[i].weight, items[i].value);
            totalValue += items[i].value;
            remainingCapacity -= items[i].weight;
        }
    }
    printf("Total Value: %d\n", totalValue);
}

// Dynamic Programming Approach
void knapsack_dp(int values[], int weights[], int n, int capacity) {
    int dp[n + 1][capacity + 1];

    // Initialize DP table
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (weights[i - 1] <= w)
                dp[i][w] = dp[i - 1][w] > (values[i - 1] + dp[i - 1][w - weights[i - 1]])
                               ? dp[i - 1][w]
                               : values[i - 1] + dp[i - 1][w - weights[i - 1]];
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    // Backtrack to find the selected items
    int w = capacity;
    printf("Dynamic Programming Selected Items:\n");
    for (int i = n; i > 0 && w > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            printf("Weight: %d, Value: %d\n", weights[i - 1], values[i - 1]);
            w -= weights[i - 1];
        }
    }
    printf("Total Value: %d\n", dp[n][capacity]);
}

// Main Function
int main() {
    int values[] = {6, 5, 8, 10};
    int weights[] = {2, 3, 4, 5};
    int capacity = 8;
    int n = sizeof(values) / sizeof(values[0]);

    printf("Greedy Approach:\n");
    knapsack_greedy(values, weights, n, capacity);

    printf("\nDynamic Programming Approach:\n");
    knapsack_dp(values, weights, n, capacity);

    return 0;
}
