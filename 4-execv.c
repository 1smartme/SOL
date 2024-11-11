//file1 (EXECVE)
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// ex1.c and bs1.c both are needed
int bubleSort(int* arr,int len) {
	int temp;
	for(int i=0; i<len; i++) {
		for(int j=0; j<len-i-1; j++) {
			if(arr[j+1] < arr[j]) {
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
	printf("Sorted array:");
	for(int i=0; i<len; i++) {
		printf("%d \t",arr[i]);
	}
}
int binarySearch(int* arr, int start, int end, int num) {
	if(end >= start) {
		int mid = start + (end - start)/2;
		if(arr[mid] == num) return mid;
		if(arr[mid] > num) return binarySearch(arr, start, mid-1, num);
		if(arr[mid] < num) return binarySearch(arr, mid+1, end, num);
	} else {
		return -1;
	}
}
int main(int argc, char** argv) {
	int len = argc-1;
	int arr[20];
	int num;
	printf("\nLength is %d\n", len-1);

	for(int i=1; i<argc; i++) {
		arr[i-1] = atoi(argv[i]);
	}
	bubleSort(arr,len);

	printf("Reversed array:");
	for(int i=len; i>=0; i--) {
		printf("%d \t", arr[i]);
	}

	printf("\nEnter Number to Search: ");
	scanf("%d", &num);
	int val = binarySearch(arr, 0, len-1, num);
	if(val != -1) {
		printf("\nThe Number is present\n");
	} else {
		printf("\nThe Number is Absent\n");
	}
	printf("BS process id: %d \n", getpid());
	printf("BS parent process id: %d", getppid());
	return 0;
}




//file 2 (NO EXECVE)

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
// ex1.c and bs1.c both are needed
int main(int argc, char* argv[]) {
	int status,i;
	int count;
	count = argc;
	char* temp[count];
	for(i=0; i<count; i++) {
		temp[i] = argv[i+1];
	}
	temp[i] = NULL;
	pid_t pid;
	pid = fork();
	if(pid == 0) {
		execv(temp[0],temp);
		printf("Helii");
	} else {
		wait(&status);
		printf("\n Parent process id = %d", getpid());
	}

}
