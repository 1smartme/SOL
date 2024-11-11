#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

struct data {
	char s[100];
	int flag;
};

void main() {
	// Create a unique key for shared memory
	key_t key = ftok("memory.txt", 'A');

	// Access the shared memory segment
	int shmid = shmget(key, 1024, 0777 | IPC_CREAT);

	// Attach to the shared memory segment
	struct data * d = shmat(shmid, NULL, 0);

	// Initialize flag to indicate no data received
	d->flag = 0;

	// Wait until flag is set to 1 by the sender
	while (d->flag != 1) {
		printf("\nWaiting...");
		//	sleep(2); // Optionally add sleep to reduce CPU usage
	}

	// Display the received data
	printf("\nThe data sent is: %s", d->s);

	// Set flag to -1 to signal to the sender that data has been read
	d->flag = -1;

	// Display shared memory segments
	system("ipcs -m");

	// Detach from the shared memory
	shmdt(d);
}



#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

struct data {
	char s[100];
	int flag;
};

void main() {
	// Create a unique key for shared memory
	key_t key = ftok("memory.txt", 'A');

	// Access the shared memory segment
	int shmid = shmget(key, 1024, 0777 | IPC_CREAT);

	// Attach to the shared memory segment
	struct data * d = shmat(shmid, NULL, 0);

	// Initialize flag to indicate data has not been sent yet
	d->flag = 0;

	// Input the data to send
	printf("\nEnter the data to be sent: ");
	gets(d->s);

	// Update the flag to indicate data is ready
	d->flag = 1;

	// Wait until the receiver has read the data
	while (d->flag != -1) {
		printf("\nWaiting...");
		sleep(2); // Optionally add sleep to reduce CPU usage
	}

	// Display shared memory segments
	system("ipcs -m");

	// Detach from the shared memory
	shmdt(d);

	// Remove shared memory segment after data is read
	shmctl(shmid, IPC_RMID, NULL);
	system("ipcs -m");
}
