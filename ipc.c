#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MSG_SIZE 100

int main(){
    printf("Name: Kameshvar Balan V\nRegNo: 22BCE3296\n\n");
    int fd[2];
    pid_t pid;
    char write_msg[MSG_SIZE];
    char read_msg[MSG_SIZE];
    printf("Enter message to pass: ");
    fgets(write_msg, sizeof(write_msg), stdin);
    write_msg[strcspn(write_msg, "\n")] = '\0';
    if(pipe(fd)==-1){
        printf("Pipe creation failed\n");
        exit(1);
    }
    pid = fork();
    if(pid<0){
        printf("Pipe connection failed\n");
        exit(1);
    }
    if(pid>0){
        close(fd[0]);
        printf("Parent Process id: %d\n", getpid());
        printf("Writing message to child: %s\n", write_msg);
        write(fd[1], write_msg, strlen(write_msg) + 1);
        close(fd[1]);
        wait(NULL);
    }
    else{
        close(fd[1]);
        read(fd[0], read_msg, MSG_SIZE);
        printf("Child Process id: %d\n", getpid());
        printf("Received message: %s\n", read_msg);
        close(fd[0]);
    }
    return 0;
}
