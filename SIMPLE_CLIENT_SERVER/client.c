#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFER 200

int main(int argc, char *argv[]) {

    char input[BUFFER]={0};
    int out_fd=open("clientToServer.fifo", O_WRONLY);

    if (out_fd==-1) {
        perror("open error");
    }

    while (1) {

        printf("What would you like to send to server? (send Quit to quit)\n");
        fgets(input, BUFFER, stdin);
        if (input[strlen(input)-1]=='\n') {
            input[strlen(input)-1]='\0';
        }

        if (strcmp(input, "Quit")==0) {
            printf("Bye!");
            break;
        }

        if (write(out_fd, input, strlen(input))==-1) {
            perror("write error");
        }
    }

    return 1;
}
