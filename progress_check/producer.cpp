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

int main(int argc, const char* argv[])
{
	if (argc == 1)
	{
		const char* name = "stdin";
		show_file(name);
	}
	else
	{
		for (int i = 1; i < argc; i++)
		{
			show_file(argv[i]);
		}
	}

	return 0;
}


void show_file (const char* name)
{
	int fd = 0;
	long sz = 0;
	if (!strcmp(name, "stdin"))
	{
		fd = 0;
		sz = -1;

	} else
	{
		fd = open(name, O_RDONLY);
		sz = size_of_file(fd);
	}

	if (fd < 0)
	{
		perror ("No such file or directory\n");
		close(fd);
		return;
	}

	Circular_buffer buf;

	std::thread thread_read([](Circular_buffer& buf, int file_read, int sz) {
			int readen = 0;
			while(readen != sz)
			{
				readen += buf.put(file_read, sz);
			}
			buf.read_live = false;
			}, std::ref(buf), fd, sz);

	std::thread thread_write([](Circular_buffer& buf, int file_write, int sz) {
			int written = 0;
			while(written != sz)
			{
				written += buf.get(1);
			}
			}, std::ref(buf), fd, sz);

	thread_read.join();
	thread_write.join();

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
