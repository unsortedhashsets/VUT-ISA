#include<stdio.h>
#include<time.h>
#include<sys/utsname.h>

void returnSystemInformation();
void returnLoginString();
void returnReadWriteInt32();
int returnTimeInRFC3339();

void returnSystemInformation(){
    struct utsname detect;

    uname(&detect);

    printf("%s\n", detect.release);
}

void returnLoginString(){
    printf("xabram00\n");
}

void returnReadWriteInt32(){
    printf("5\n");
}

int returnTimeInRFC3339(){
    time_t now = time(NULL);
    struct tm *tm;
    int off_sign;
    int off;

    if ((tm = localtime(&now)) == NULL) {
        return -1;
    }
    off_sign = '+';
    off = (int) tm->__tm_gmtoff;
    if (tm->__tm_gmtoff < 0) {
        off_sign = '-';
        off = -off;
    }
    printf("%d-%d-%dT%02d:%02d:%02d%c%02d:%02d\n",
           tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
           tm->tm_hour, tm->tm_min, tm->tm_sec,
           off_sign, off / 3600, off % 3600);
    return 1;
}

int main(void){
    returnSystemInformation();
    returnLoginString();
    returnReadWriteInt32();
    returnTimeInRFC3339();
    return 0;
}

