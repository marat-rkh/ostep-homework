#include <stdio.h>
#include <sys/time.h>

void bench_gettimeofday() {
    const int MAX_TIMES = 100000;
    struct timeval current_time[MAX_TIMES];
    for (int i = 0; i < MAX_TIMES; ++i) {
        gettimeofday(&current_time[i], NULL);
    }
    printf("seconds: %ld\nmicro_seconds: %d\n", current_time[0].tv_sec, current_time[0].tv_usec);
    printf("seconds: %ld\nmicro_seconds: %d\n", current_time[MAX_TIMES - 1].tv_sec, current_time[MAX_TIMES - 1].tv_usec);
    printf("the average time of a gettimeofday function call is: %f us\n", (current_time[MAX_TIMES - 1].tv_usec - current_time[0].tv_usec) / (double)MAX_TIMES);
}

void bench_syscall() {
    const int MAX_TIMES = 1000000;
    struct timeval timestamps[2];
    FILE* file = fopen("main.c", "r");
    if (file == NULL) {
        return;
    }
    int num = 0;
    gettimeofday(&timestamps[0], NULL);
    for (int i = 0; i < MAX_TIMES; ++i) {
        fread(&num, sizeof(int), 0, file);
    }
    gettimeofday(&timestamps[1], NULL);
    fclose(file);

    printf("seconds: %ld\nmicro_seconds: %d\n", timestamps[0].tv_sec, timestamps[0].tv_usec);
    printf("seconds: %ld\nmicro_seconds: %d\n", timestamps[1].tv_sec, timestamps[1].tv_usec);
    printf("the average time of a zero byte fread syscall is: %f us\n", (timestamps[1].tv_usec - timestamps[0].tv_usec) / (double)MAX_TIMES);
}

int main(int argc, char *argv[]) {
    bench_syscall();
    return 0;
}