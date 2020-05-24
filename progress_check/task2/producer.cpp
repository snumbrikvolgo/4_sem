#include <iostream>
#include <future>
#include <thread>
#include <unistd.h>
#include <cstring>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <mutex>
#include "buffer.h"

using namespace std;

long size_of_file(int text);
void show_file (const char* name);

int main(int argc, const char* argv[]) {
    if (argc == 1) {
        const char* name = "stdin";
        show_file(name);
    } else {
        for (int i = 1; i < argc; i++) {
            show_file(argv[i]);
        }
    }

    return 0;
}


void show_file (const char* name) {
    int fd = 0;
    long sz = 0;

    if (!strcmp(name, "stdin")) {
        fd = 0;
        sz = 1;
    } else {
        fd = open(name, O_RDONLY);
        sz = size_of_file(fd);
    }

    if (fd < 0) {
        perror("No such file or directory\n");
        close(fd);
        return;
    }

    Circular_buffer buf;

    std::thread thread_read([](Circular_buffer &buf, int file_read, int sz) {
        int readen = 0;
        int ch_read = 0;

        buf.flag = 1;
        while (readen != sz) {
            //printf("\nheheheh\n\n");
            ch_read = buf.put(file_read, sz);
            if (ch_read == -5) {
                break;
            }

            readen += ch_read;
            //printf("\nreaden %d, ch_read %d\n\n", readen, ch_read);
            //readen += result;
        }

        buf.flag = 0;
        //printf("\nread goodbye\n\n");
    }, std::ref(buf), fd, sz);

    std::thread thread_write([](Circular_buffer &buf, int file_write, int sz) {
        int written = 0;
        int ch_write = 0;
        while (written != sz) {
            ch_write = buf.get(1);
            if (ch_write == -5) {
                break;
            }

            written += ch_write;
            //printf("\nwritten %d, ch_write %d\n\n", written, ch_write);
            //written += result;
        }

        //printf("\nwrite goodbye\n\n");
    }, std::ref(buf), fd, sz);

    thread_read.join();
    thread_write.join();

    close(fd);
}


long size_of_file(int text) {
    long current = 0;
    current = lseek(text, 0, SEEK_CUR);

    long number_of_symbols = 0;

    number_of_symbols = lseek(text, 0, SEEK_END);
    lseek(text, current, SEEK_SET);

    return number_of_symbols;
}
