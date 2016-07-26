#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#define MYFIFO "myfifo"
#define BUFFER_SIZE PIPE_BUF
#define TEN_MEG (1024*1024*10)
