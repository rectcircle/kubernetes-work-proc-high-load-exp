// 静态编译并申请 100MB 内存
// gcc -static mem-alloc.c -o mem-alloc && ./mem-alloc 100
// sudo cp mem-alloc /usr/local/bin
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const size_t MB = 1024 * 1024;

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        printf("usage: %s <alloc memory size mb> <delay seconds, default 10>\n", argv[0]);
        return 1;
    }
    size_t allocSize = atoi(argv[1]) * MB;
    if (allocSize == 0) {
        printf("error: alloc memory size mb must greate than 0\n");
        return 1;
    }
    int sleepSec = 0;
    if (argc == 3) {
        sleepSec = atoi(argv[2]);
    }
    if (sleepSec == 0) {
        sleepSec = 10;
    }
    // 睡眠再申请内存
    sleep(sleepSec);
    // 申请内存 （VSZ）
    char *m = (char *)malloc(allocSize * sizeof(char));
    if (m == NULL) {
        printf("error: alloc %dMB size memory failed\n", allocSize / MB);
        return 1;
    }
    // 使用内存 （RSS）
    for (size_t i = 0; i < allocSize; i++) {
        m[i] = i % 256;
    }
    while(1) {
        sleep(1);
    }
}