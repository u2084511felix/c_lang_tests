#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <sys/inotify.h>
#include <wchar.h>

int main(int argc, char **argv) {

    // char* cat = "cat /home/felix/.cache/codetags/watch.log";
    // FILE *fd = popen(cat, "r");

    FILE *f = fopen("/home/felix/.cache/codetags/watch.log", "r");

    
    if(f == NULL) {
        fprintf(stderr, "Could not open file.\n");
        return 1;
    }

    fseek(f, 0, SEEK_END); //NOTE:Sets the filebuffer to the end of the file.

    long position = ftell(f);
    if (position == 0) { fclose(f); system("notify-send 'error: file empty'"); return 0;}
    fseek(f, --position, SEEK_SET);


    while (position > 0) {
        fseek(f, --position, SEEK_SET);

        if (fgetc(f) == '\n') {
            break;
        }
    }

    char buffer[10000];

    strcpy(buffer,"notify-send '\t\t\t\t\t====== Watch Log ======' ");

    char tmp[10000];

    fgets(tmp, sizeof(tmp), f);    

    fclose(f);
  
    snprintf(buffer+strlen(buffer), strlen(tmp)+3, "'%s'", tmp);

    system(buffer);


    return 0;
}
