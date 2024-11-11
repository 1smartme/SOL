#include <stdio.h>

int main() {
    int n, m, i, j, k;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    printf("Enter the number of resource types: ");
    scanf("%d", &m);
    
    int alloc[n][m], max[n][m], avail[m];
    
    // Taking input for Allocation Matrix
    printf("Enter the Allocation Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("alloc[%d][%d]: ", i, j);
            scanf("%d", &alloc[i][j]);
        }
    }
    
    // Taking input for Maximum Requirement Matrix
    printf("Enter the Maximum Requirement Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("max[%d][%d]: ", i, j);
            scanf("%d", &max[i][j]);
        }
    }
    
    // Taking input for Available Resources
    printf("Enter the Available Resources:\n");
    for (j = 0; j < m; j++) {
        printf("avail[%d]: ", j);
        scanf("%d", &avail[j]);
    }
    
    int f[n], ans[n], ind = 0;
    for (k = 0; k < n; k++) {
        f[k] = 0; // Mark all processes as unfinished
    }
    
    // Calculating Need Matrix
    int need[n][m];
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    
    int y = 0;
    for (k = 0; k < n; k++) { // Loop to find safe sequence
        for (i = 0; i < n; i++) {
            if (f[i] == 0) { // Process i is not finished
                int flag = 0;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        flag = 1;
                        break;
                    }
                }
                
                if (flag == 0) { // All needs of process i can be satisfied
                    ans[ind++] = i; // Add process i to the safe sequence
                    for (y = 0; y < m; y++) {
                        avail[y] += alloc[i][y];
                    }
                    f[i] = 1; // Mark process i as finished
                }
            }
        }
    }
  
    // Checking if system is in safe state
    int safe = 1;
    for (i = 0; i < n; i++) {
        if (f[i] == 0) { // If any process is not finished
            safe = 0;
            printf("The system is not in a safe state.\n");
            break;
        }
    }
    
    if (safe == 1) {
        printf("The system is in a safe state.\nSafe sequence is: ");
        for (i = 0; i < n - 1; i++) {
            printf("P%d -> ", ans[i]);
        }
        printf("P%d\n", ans[n - 1]);
    }
    
    return 0;
}
