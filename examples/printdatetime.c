#include <sys/types.h>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>

void print_time(time_t mytime, int print_sleep) {
    char *humantime = ctime(&mytime);

    printf("The datetime is: %s", humantime);

    if (print_sleep > 1)
        printf("Go to sleep!\n");
}

int main(int argc, char **argv) {
    time_t mytime;
    mytime = time(NULL);

    print_time(mytime, argc);

    return 0;
}
