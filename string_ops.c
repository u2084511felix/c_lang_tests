#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <sys/inotify.h>
#include <wchar.h>

//TODO: seperate into other files [CT-3-cbe0d0eb]
//WARN: codetags is bnroken [CT-4-ce8757df]
int main(int argc, char **argv) {

    char a[200] = "";
    char* b = "hello world";
    strcpy(a, b);

    // char c[200] = "\0";
    // char d[200] = "hello mars\0";




    printf("%s\n", a);

    return 0;
} 
