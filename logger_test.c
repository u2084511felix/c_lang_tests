#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include <stdint.h>

int dbc = 0;

void print_debug() {
    dbc += 1;
    printf("SEGF BELOW %i\n", dbc);
}
//NOTE: Extended in prod. [CT-7-e2642a81]
enum log_level {
    TRACE, DEBUG, INFO, ERROR, WARNING, CRITICAL,
    TRACE1, DEBUG1, INFO1, ERROR1, WARNING1, CRITICAL1
};

int get_last_log_ts(char* fp) {
    FILE* f = fopen(fp, "a+");
    fseek(f, 0, SEEK_END); 

    unsigned int position = ftell(f);
    if (position == 0) { 
        fclose(f); 
        return 0;
    }
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
    return tfli;

}

int limit_logger(int a, int b, int limit) {
    if (a > 0) {
        int df = b - a;
        if (df < limit) {
            return 1;
        } else return 0;
    } else return 0;
}


void log_ct(enum log_level lvl,  char* r) {

    FILE* f;
    char debug[500] = "\n";
    char log_time[20] = "";
    int use_limiter = 0;

    struct tm *tmp;
    time_t t;
    t = time(NULL);
    tmp = localtime(&t);

    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    

    //printf("%-25s: %jd
    intmax_t utime = ts.tv_sec;    
    char timestr1[200] = ""; 
    snprintf(timestr1+strlen(timestr1), 200, "%jd", utime);

    char timestr[200] = "";
    char* args = "|%d:%m:%Y|%T";
    strftime(timestr, sizeof(timestr), args, tmp);

    snprintf(debug+strlen(debug), strlen(timestr1)+1, "%s", timestr1);
    snprintf(debug+strlen(debug), strlen(timestr)+1, "%s", timestr);

    char filepath[200] = "/home/felix/c_lang_tests/log_tests/";
    char* file_name = "";


    switch(lvl) {
        case TRACE:
            strcat(log_time, "><TRACE: ");
            file_name = "trace.log";    
            break;
        case DEBUG:
            strcat(log_time, "><DEBUG: ");
            file_name = "debug.log";    
            break;
        case INFO:
            strcat(log_time, "><INFO: ");
            file_name = "info.log";    
            break;
        case ERROR:
            strcat(log_time, "><ERROR: ");
            file_name = "error.log";    
            break;
        case WARNING:
            strcat(log_time, "><WARNING: ");
            file_name = "warning.log";    
            break;
        case CRITICAL:
            strcat(log_time, "><CRITICAL: ");
            file_name = "critical.log";    
            break;
        case TRACE1:
            use_limiter = 1;
            strcat(log_time, "><TRACE: ");
            file_name = "trace.log";    
            break;
        case DEBUG1:
            use_limiter = 1;
            strcat(log_time, "><DEBUG: ");
            file_name = "debug.log";    
            break;
        case INFO1:
            use_limiter = 1;
            strcat(log_time, "><INFO: ");
            file_name = "info.log";    
            break;
        case ERROR1:
            use_limiter = 1;
            strcat(log_time, "><ERROR: ");
            file_name = "error.log";    
            break;
        case WARNING1:
            use_limiter = 1;
            strcat(log_time, "><WARNING: ");
            file_name = "warning.log";    
            break;
        case CRITICAL1:
            use_limiter = 1;
            strcat(log_time, "><CRITICAL: ");
            file_name = "critical.log";    
            break;
        default:
            strcat(log_time, "><INFO: ");
            file_name = "info.log";    
            break;
    }


    snprintf(filepath+strlen(filepath), 50, "%s", file_name);
    snprintf(debug+strlen(debug), strlen(log_time)+1, "%s", log_time);
    snprintf(debug+strlen(debug), strlen(r)+1, "%s", r);

    int llts = get_last_log_ts(filepath);

    if (limit_logger(llts, utime, use_limiter) > 0) {
        return;
    }


    f = fopen(filepath, "a");
    fputs(debug, f);
    fclose(f);
}


int main(int argc, char **argv) {
    for (;;) {

        log_ct(TRACE1, "Test..");
        log_ct(DEBUG, "Test..");
        log_ct(INFO, "Test..");
        log_ct(ERROR, "Test..");
        log_ct(WARNING, "Test..");
        log_ct(CRITICAL, "Test..");
    }
}
