//hello world
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
  //  FILE* f = fopen("/home/felix/.cache/codetags/logs/test.log", "a");


    //NOTE: Test writing to a file.
    // char r[100] = "hello world\n";
    // char debug[100] = "TEST LOG LINE APPEND : SUCCESS ";
    // snprintf(debug+strlen(debug), strlen(r)+1, "%s\n", r);
    // fputs(debug, f);
    // fclose(f);
    // system("cat /home/felix/.cache/codetags/test.log");

    //NOTE: Testing reading from log file to string.
    


    FILE* f = fopen("/home/felix/.cache/codetags/logs/trace.log", "r");
    fseek(f, 0, SEEK_END); //NOTE:Sets the filebuffer to the end of the file.

    long position = ftell(f);
    if (position == 0) { fclose(f); return 0;}
    fseek(f, --position, SEEK_SET);

    while (position > 0) {
        fseek(f, --position, SEEK_SET);
        if (fgetc(f) == '\n') {            
            break;
        }
    }

    long old_pos = position;

    char tfl[30] = "";
    while (fgetc(f) != '|') {
        fseek(f, old_pos++, SEEK_SET);
        char nc = fgetc(f);
        snprintf(tfl+strlen(tfl), strlen(&nc), "%c", nc);
    }

    fclose(f);

    int tfli = atoi(tfl);
    int tfl2 = tfli + 2;

    
    printf("or: %i n: %i\n", tfli, tfl2);
    return 0;
}

