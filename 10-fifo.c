#include <stdio.h>

struct Page {
    int position;
    int value;
};

int main() {
    int n, pagefaults = 0, hits = 0;
    struct Page frames[3]; // Fixed frame size of 3
    for (int i = 0; i < 3; i++) {
        frames[i].value = -1; // Initialize frames with an invalid value
        frames[i].position = -1;
    }

    printf("Enter the number of pages: ");
    scanf("%d", &n);
    
    struct Page pages[n];
    for (int i = 0; i < n; i++) {
        printf("Enter page value for position %d: ", i);
        scanf("%d", &pages[i].value);
        pages[i].position = i;
    }

    // Page Replacement Simulation
    for (int i = 0; i < n; i++) {
        int pagefound = 0;
        
        // Check if page is already in frames
        for (int j = 0; j < 3; j++) {
            if (frames[j].value == pages[i].value) {
                hits++;
                frames[j].position = i; // Update position for LRU tracking
                pagefound = 1;
                break;
            }
        }

        // If page is not found, we have a page fault
        if (!pagefound) {
            pagefaults++;
            int min_index = 0;
            
            // Find the LRU page
            for (int k = 1; k < 3; k++) {
                if (frames[k].position < frames[min_index].position) {
                    min_index = k;
                }
            }
            
            // Replace the LRU page
            frames[min_index].value = pages[i].value;
            frames[min_index].position = i;
        }
    }

    printf("\nFinal Frame Contents: ");
    for (int i = 0; i < 3; i++) {
        printf("%d ", frames[i].value);
    }
    
    printf("\nTotal Page Faults: %d\n", pagefaults);
    printf("Total Hits: %d\n", hits);

    return 0;
}
