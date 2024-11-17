#include <stdio.h>

#define MAX 100

void sumOfSubsets(int set[], int subset[], int n, int target, int subset_size, int sum, int index) {
    // If the subset sum equals the target, print the subset
    if (sum == target) {
        printf("Subset: ");
        for (int i = 0; i < subset_size; i++) {
            printf("%d ", subset[i]);
        }
        printf("\n");
        return;
    }

    // If the sum exceeds the target or no elements are left to explore, stop
    if (sum > target || index >= n) {
        return;
    }

    // Include the current element in the subset
    subset[subset_size] = set[index];
    sumOfSubsets(set, subset, n, target, subset_size + 1, sum + set[index], index + 1);

    // Exclude the current element and move to the next
    sumOfSubsets(set, subset, n, target, subset_size, sum, index + 1);
}

int main() {
    int set[] = {3, 34, 4, 12, 5, 2};
    int target = 9;
    int n = sizeof(set) / sizeof(set[0]);
    int subset[MAX]; // Temporary array to store subsets

    printf("Subsets with sum equal to %d:\n", target);
    sumOfSubsets(set, subset, n, target, 0, 0, 0);

    return 0;
}
