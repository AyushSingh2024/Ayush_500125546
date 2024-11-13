#include <stdio.h>
#include <limits.h>

// Function to perform Matrix Chain Multiplication using Dynamic Programming
void matrixChainOrder(int p[], int n) {
    int m[n][n];  // DP table to store the minimum multiplication cost
    int s[n][n];  // Table to store the split points for optimal parenthesization

    // Initialize the main diagonal to 0, since single matrices need no multiplication
    for (int i = 1; i < n; i++)
        m[i][i] = 0;

    // Fill the table in a bottom-up manner
    for (int len = 2; len < n; len++) { // len is the chain length
        for (int i = 1; i < n - len + 1; i++) {
            int j = i + len - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k <= j - 1; k++) {
                // Cost = cost of splitting at k + cost of multiplying the results
                int cost = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (cost < m[i][j]) {
                    m[i][j] = cost;
                    s[i][j] = k; // Store the split point
                }
            }
        }
    }

    // Output the minimum cost
    printf("Minimum number of multiplications is %d\n", m[1][n - 1]);

    // Function to print optimal parenthesis placement
    void printOptimalParenthesis(int s[][n], int i, int j) {
        if (i == j)
            printf("A%d", i);
        else {
            printf("(");
            printOptimalParenthesis(s, i, s[i][j]);
            printOptimalParenthesis(s, s[i][j] + 1, j);
            printf(")");
        }
    }

    printf("Optimal parenthesis arrangement: ");
    printOptimalParenthesis(s, 1, n - 1);
    printf("\n");
}

int main() {
    int p[] = {40, 20, 30, 10, 30}; // Matrix dimensions
    int n = sizeof(p) / sizeof(p[0]);

    matrixChainOrder(p, n);

    return 0;
}
