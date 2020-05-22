#include <iostream>
#include <future>
#include <thread>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <mutex>
#include "buffer.h"

using namespace std;

#define CAP 1024*1024
#define OUT 100


long size_of_file(int text);
void show_file (char* name);

int main(int argc, char* argv[])
{
    //Circular_buffer buf;

    // FILE* file_1 = fopen(argv[1], "rb");
    // FILE* file_2 = stdout;

    // if (argc == 1)
    // {
    //     while (n != 0)
    //     {
    //         auto fut1 = async(std::launch::async,[](char* string){
    //             return read(0, string, MAX_OUT);
    //         }, string);
    //
    //         auto fut2 = async(std::launch::async,[&fut1](char* string){
    //         return write(1, string, MAX_OUT);
    //         }, string);
    //     }
    // }

    {
        for (int i = 1; i < argc; i++)
        		{
        			show_file(argv[i]);
        		}
    }

    return 0;
}


void show_file (char* name)
{
	int symbols = 0;
	int fd = open(name, O_RDONLY);
	long sz = size_of_file(fd);

    Circular_buffer buf;

    std::promise<int> pr_read;
    std::future<int> fut_write = pr_read.get_future();

    std::thread thread_read([](Circular_buffer& buf, int file_read, int sz) {
        int readen = 0;
        while(readen != sz)
        {
            readen += buf.put(file_read);
        }

    }, std::ref(buf), fd, sz);

    std::thread thread_write([](Circular_buffer& buf, int file_write, int sz) {
        int written = 0;
        //file_write = open("kek.cpp", O_CREAT);
        //printf("file_write %d\n", file_write );
        while(written != sz)
        {
            written += buf.get(1);
        }
    }, std::ref(buf), fd, sz);

    thread_read.join();
    thread_write.join();
	if (fd < 0)
		perror ("No such file or directory\n");
	close (fd);
}


long size_of_file(int text)
{
	long current = 0;
	current = lseek(text, 0, SEEK_CUR);

	long number_of_symbols = 0;

	number_of_symbols = lseek(text, 0, SEEK_END);
	lseek(text, current, SEEK_SET);

	return number_of_symbols;
}
