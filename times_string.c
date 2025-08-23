#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <stdint.h>

int main(int argc, char **argv) {


    //UNIXTIME:
    //
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    printf("%-25s: %jd\n", "UNIXTIME", (intmax_t) ts.tv_sec);

    struct timeval tv;
    int tod = gettimeofday(&tv, NULL);
    char utstr[100] = "";

    snprintf(utstr+strlen(utstr), 100, "%jd\n", tv.tv_sec);
    printf("snprintf test: %s\n", utstr);
    printf("%-25s: %jd\n", "UNIXTIME-GTOD", (intmax_t) tv.tv_sec);

    //STD TIME / CALENDAR FORMATTING
    
    struct tm *tmp;
    time_t t;
    t = time(NULL);
    tmp = localtime(&t);
    char outstr[200] = "";
    
    char* args = "%s | %d:%m:%Y | %T";
    strftime(outstr, sizeof(outstr), args, tmp);
    printf("%s\n", outstr);
}
