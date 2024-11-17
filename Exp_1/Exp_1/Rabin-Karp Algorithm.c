#include <stdio.h>
#include <string.h>
#define d 256 // Number of characters in the input alphabet

void rabinKarp(char *text, char *pattern, int q) {
    int n = strlen(text);
    int m = strlen(pattern);
    int h = 1; // Value of d^(m-1)
    int p = 0; // Hash value for pattern
    int t = 0; // Hash value for text
    int i, j;

    // Precompute h = d^(m-1) % q
    for (i = 0; i < m - 1; i++)
        h = (h * d) % q;

    // Calculate initial hash values for pattern and first window of text
    for (i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    printf("Rabin-Karp Algorithm:\n");
    for (i = 0; i <= n - m; i++) {
        // Check hash values
        if (p == t) {
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j])
                    break;
            }
            if (j == m) {
                printf("Pattern found at index %d\n", i);
            }
        }

        // Calculate hash for the next window
        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;
            if (t < 0) t += q;
        }
    }
}
