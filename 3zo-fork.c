//zombie
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    pid_t pid;
    pid = fork();
    int status;

    if (pid != 0) {//parent processs
        // Parent Process
        sleep(2); // Allow child to complete first, creating a zombie state
        system("ps"); // Display processes to show zombie child
        wait(&status); // Reap the child process to avoid permanent zombie

        printf("\nThis is Parent Process\n");
        printf("Parent process ID = %d\n", getppid());
        printf("Parent child ID = %d\n", getpid());

        // Sort the array
        bubbleSort(arr, n);
        printf("Parent sorted array: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

        system("ps"); // Show process states after wait
    } 
    else {
        // Child Process
        printf("\nThis is Child Process\n");
        printf("Child process ID = %d\n", getpid());
        printf("Child Parent ID = %d\n", getppid());

        // Sort the array
        bubbleSort(arr, n);
        printf("Child sorted array: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

        exit(0); // Child exits, becoming a zombie until parent waits
   }
}


//orphan
//Orphan

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

void bubblesort(int arr[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

void main() {

	int n;

	printf("Enter the number of elelments:");
	scanf("%d",&n);

	int arr[n];

	 printf("Enter the elements:\n");
         for (int i = 0; i < n; i++) {
             scanf("%d", &arr[i]);
         }
//fork -> system call -> replica (child process)
	pid_t pid;
	pid=fork();

	if(pid!=0) { //parent process
		printf("\n This is parent process");
		printf("Parent process id =%d\n",getppid());//parent process id
		printf("Parent child id=%d\n",getpid());//current process id equal

			bubblesort(arr,n);
			printf("\n Parent sorted array");
			for(int i=0; i<n; i++) {
				printf("%d",arr[i]);
			}
			printf("\n"); //execute
			sleep(1);   
		}
		else { //child process
			sleep(2);
			printf("\n This is child processs");
			printf("CHild process id=%d\n ",getpid());
			printf("child parent id=%d\n",getppid());//equal

			bubblesort(arr,n);
			printf("Child sorted array");
			for(int i=0; i<n; i++) {
				printf("%d",arr[i]);
			}
			printf("\n");
  
		}
	}
