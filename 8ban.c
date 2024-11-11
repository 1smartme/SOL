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


alloc[0][0] = 0   alloc[0][1] = 1   alloc[0][2] = 0
alloc[1][0] = 2   alloc[1][1] = 0   alloc[1][2] = 0
alloc[2][0] = 3   alloc[2][1] = 0   alloc[2][2] = 2
alloc[3][0] = 2   alloc[3][1] = 1   alloc[3][2] = 1
alloc[4][0] = 0   alloc[4][1] = 0   alloc[4][2] = 2

max[0][0] = 7   max[0][1] = 5   max[0][2] = 3
max[1][0] = 3   max[1][1] = 2   max[1][2] = 2
max[2][0] = 9   max[2][1] = 0   max[2][2] = 2
max[3][0] = 2   max[3][1] = 2   max[3][2] = 2
max[4][0] = 4   max[4][1] = 3   max[4][2] = 3

avail[0] = 3
avail[1] = 3
avail[2] = 2

need[0][0] = 7   need[0][1] = 4   need[0][2] = 3
need[1][0] = 1   need[1][1] = 2   need[1][2] = 2
need[2][0] = 6   need[2][1] = 0   need[2][2] = 0
need[3][0] = 0   need[3][1] = 1   need[3][2] = 1
need[4][0] = 4   need[4][1] = 3   need[4][2] = 1

P1 -> P3 -> P4 -> P0 -> P2

