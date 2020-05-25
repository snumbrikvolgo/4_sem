#include <iostream>
#include <future>
#include <thread>
#include <unistd.h>
#include <cstring>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <atomic>
#include <mutex>
#include "buffer.h"

using namespace std;

long size_of_file(int text);
void show_file (const char* name);

int main(int argc, char* argv[])
{
    circular_buffer buf;
    buf.almost_empty.first.set_value(0);
    atomic<bool> is_eof(false);
    //is_eof = false;
    std::thread thread_read([](circular_buffer &buf, atomic<bool>& is_eof) {
        int ch_read = -1;
        while(ch_read != 0)
        {
            buf.mutex_.lock();
            int sz = buf.size();
            //printf("size %d\n", sz);
            buf.mutex_.unlock();

            if (sz == buf.max_size_)
            {
                printf("I AM FULL, WAIT UNTILL WMPTY\n");
                buf.almost_empty.second.get();
                buf.almost_empty.first = std::promise<int>();
                buf.almost_empty.second = buf.almost_empty.first.get_future();
            }

            ch_read = read(0, buf.buf_ + buf.head_, OUT);
            buf.plus(ch_read);
            is_eof = buf.buf_[buf.head_] == EOF;
            if (is_eof)
            {
                buf.almost_full.first.set_value(0);
                break;
            }

            if (10*sz > 80*buf.max_size_)
            {
                printf("I AM ALMOST FULL SEND SIGNAL\n" );
                buf.almost_full.first.set_value(0);
            }
        }
        //buf.almost_empty.first.set_value_at_thread_exit(0);

    }, std::ref(buf), std::ref(is_eof));
    std::thread thread_write([](circular_buffer &buf, atomic<bool>& is_eof) {
        int ch_write = -1;
        while(ch_write != 0)
        {
            buf.mutex_.lock();
            int sz = buf.size();
            //printf("size %d\n", sz);
            buf.mutex_.unlock();

            if (sz == 0 && !is_eof)
            {
                printf("I AM SIZE == 0, WAIT\n");
                buf.almost_full.second.get();
                buf.almost_full.first = std::promise<int>();
                buf.almost_full.second = buf.almost_full.first.get_future();
            }

            if (sz < OUT)
            {
                ch_write = write(1, buf.buf_ + buf.tail_, sz);

            }
            else ch_write = write(1, buf.buf_ + buf.tail_, OUT);
            buf.minus(ch_write);

            if (10*sz < 20*buf.max_size_)
            {
                printf("I AM LESS THAN 20, SET SIGNAL\n");
                buf.almost_empty.first.set_value(0);
            }
        }

    }, std::ref(buf), std::ref(is_eof));

    thread_read.join();
    thread_write.join();
    return 0;
}

void show_file (const char* name) {

}

long size_of_file(int text) {
    long current = 0;
    current = lseek(text, 0, SEEK_CUR);

    long number_of_symbols = 0;

    number_of_symbols = lseek(text, 0, SEEK_END);
    lseek(text, current, SEEK_SET);

    return number_of_symbols;
}
