#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define _GNU_SOURCE


#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <sys/inotify.h>
#include <wchar.h>


int main(int argc, char **argv) {

    enum log_level {
        TRACE, DEBUG, INFO, ERROR, WARNING, CRITICAL
    };
    enum log_level lvl;
    lvl = DEBUG;


    FILE* f;
    char r[300] = "hello world";
    char debug[500] = "";
    char tmp[500] = "";
    char log_time[500] = "";

    time_t* t;
    time_t nt = time(t);
    t = &nt;

    char* ntime = ctime(t);
    char antime[500] = "";
    snprintf(antime, strlen(ntime)+1, "%s", ntime);

    snprintf(debug+strlen(debug), strlen(antime), "%s", antime);

    switch(lvl) {
        case TRACE:
            strcat(log_time, " || TRACE || ");
            f = fopen("/home/felix/.cache/codetags/logs/trace.log", "a");    
            break;
        case DEBUG:
            strcat(log_time, " || DEBUG: ");
            f = fopen("/home/felix/.cache/codetags/logs/debug.log", "a");    
            break;
        case INFO:
            strcat(log_time, " || INFO: ");
            f = fopen("/home/felix/.cache/codetags/logs/info.log", "a");    
            break;
        case ERROR:
            strcat(log_time, " || ERROR: ");
            f = fopen("/home/felix/.cache/codetags/logs/error.log", "a");    
            break;
        case WARNING:
            strcat(log_time, " || WARNING: ");
            f = fopen("/home/felix/.cache/codetags/logs/warning.log", "a");    
            break;
        case CRITICAL:
            strcat(log_time, " || CRITICAL: ");
            f = fopen("/home/felix/.cache/codetags/logs/critical.log", "a");    
            break;
        default:
            strcat(log_time, " || INFO: ");
            f = fopen("/home/felix/.cache/codetags/logs/info.log", "a");    
            break;
    }


    snprintf(debug+strlen(debug), strlen(log_time)+1, "%s", log_time);
    snprintf(debug+strlen(debug), strlen(r)+1, "%s\n", r);
    printf("%s\n", debug);
    fputs(debug, f);
    fclose(f);
}
