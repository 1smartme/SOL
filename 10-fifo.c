//FILE 1

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
int main() 
{
    char *fifo1 = "fifo1";
    char *fifo2 = "fifo2";
    char ch, buffer[100];
    int d1, i = 0;
    mkfifo(fifo1, 0666);
    d1 = open(fifo1, O_WRONLY);
    printf("\nEnter data (end with #): ");
    ch = getchar();
    while (ch != '#') 
    {
        buffer[i] = ch;
        i++;
        ch = getchar();
    }
    buffer[i] = '#';
    write(d1, buffer, sizeof(buffer));
    close(d1);
    sleep(2);
    int d2 = open(fifo2, O_RDONLY);
    char buffer2[100];
    read(d2, buffer2, sizeof(buffer2));
    printf("User2: %s\n", buffer2);
    close(d2);
    FILE *fptr = fopen(buffer2, "r");
    if (fptr == NULL) 
    {
        perror("Error opening file");
        return 1;
    }
    while ((ch = fgetc(fptr)) != EOF) 
    {
        printf("%c", ch);
    }
    fclose(fptr);
    return 0;
}


//File 2

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
int main() {
    char *fifo1 = "fifo1";
    char *fifo2 = "fifo2";
    char buffer1[100];
    int d1, d2, i = 0, cc = 0, ln = 0, wc = 0;
    d1 = open(fifo1, O_RDONLY);
    read(d1, buffer1, sizeof(buffer1));
    while (buffer1[i] != '#' && buffer1[i] != '\0') 
    {
    if (buffer1[i] == ' ') 
    {
        wc++;
    } 
    else if (buffer1[i] == '\n') 
    {
        ln++;
        wc++;
    }   
    else 
    {
        cc++;
    }
    i++;
    }
    FILE *fp = fopen("Memory.txt", "w");
    if (fp == NULL) 
    {
        perror("Error opening file");
        return 1;
    }
    fprintf(fp, "\nLine count = %d", ln);
    fprintf(fp, "\nWord count = %d", wc);
    fprintf(fp, "\nCharacter count = %d", cc);
    fclose(fp);
    mkfifo(fifo2, 0666);
    d2 = open(fifo2, O_WRONLY);
    write(d2, "Memory.txt", 14);
    close(d2);
    return 0;
}
