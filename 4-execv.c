//file1 (EXECVE)
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void bubbleSort(int* arr, int len) {
	int temp;
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len - i - 1; j++) {
			if (arr[j + 1] < arr[j]) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
	printf("Sorted array: ");
	for (int i = 0; i < len; i++) {
		printf("%d \t", arr[i]);
	}
	printf("\n");
}

int binarySearch(int* arr, int start, int end, int num) {
	if (end >= start) {
		int mid = start + (end - start) / 2;
		if (arr[mid] == num) return mid;
		if (arr[mid] > num) return binarySearch(arr, start, mid - 1, num);
		return binarySearch(arr, mid + 1, end, num);
	}
	return -1;
}

int main(int argc, char** argv) {
	int len = argc - 1;
	int arr[20];
	int num;
	printf("Length is %d\n", len);

	for (int i = 1; i < argc; i++) {
		arr[i - 1] = atoi(argv[i]);
	}

	bubbleSort(arr, len);

	printf("Reversed array: ");
	for (int i = len - 1; i >= 0; i--) {
		printf("%d \t", arr[i]);
	}
	printf("\n");

	printf("Enter Number to Search: ");
	scanf("%d", &num);

	int val = binarySearch(arr, 0, len - 1, num);
	if (val != -1) {
		printf("The Number is present\n");
	} else {
		printf("The Number is Absent\n");
	}

	printf("BS process id: %d\n", getpid());
	printf("BS parent process id: %d\n", getppid());

	return 0;
}





//file 2 (NO EXECVE)

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	int status, i;

	// Ensure that the number of arguments is valid
	if (argc < 2) {
		fprintf(stderr, "Usage: %s <program_to_execute> [args...]\n", argv[0]);
		return 1;
	}

	// Create an array to hold command-line arguments for execv
	char* temp[argc];
	for (i = 0; i < argc - 1; i++) {
		temp[i] = argv[i + 1]; // Copy arguments from argv (skipping the program name)
	}
	temp[argc - 1] = NULL; // Null-terminate the argument list for execv

	pid_t pid = fork();
	if (pid < 0) {
		perror("Fork failed");
		return 1;
	}

	if (pid == 0) { // Child process
		// Execute the target program
		if (execv(temp[0], temp) == -1) {
			perror("execv failed"); // Print error if execv fails
			exit(1);
		}
	} else { // Parent process
		// Wait for the child process to complete
		wait(&status);
		if (WIFEXITED(status)) {
			printf("\nChild process exited with status = %d\n", WEXITSTATUS(status));
		}
		printf("Parent process id = %d\n", getpid());
	}

	return 0;
}

