#include <iostream>
#include <string.h>
#include <thread>
#include <chrono>
#include <future>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>

using namespace std;

#define MAX_STRING 2*1024
#define MAX_OUT 1024

#define LOW 20
#define HIGH 80

long size_of_file(int text);
void show_file (char* name);

int main(int argc, char* argv[])
{
    char string[MAX_STRING];

    int n = -1;
    if (argc == 1)
    {
        while (n != 0)
        {
            auto fut1 = async(std::launch::async,[](char* string){
                return read(0, string, MAX_OUT);
            }, string);

            auto fut2 = async(std::launch::async,[&fut1](char* string){
            return write(1, string, MAX_OUT);
            }, string);
        }
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

void show_file (char* name)
{
    std::atomic<bool> buffel_lock;
	int symbols = 0;
	int fd = open(name, O_RDONLY);
	long sz = size_of_file(fd);

	char string[MAX_STRING];
	int n = 0;

	while (symbols < sz)
	{  //std::future<int>
        auto fut1 = async(std::launch::async,[](char* string, int fd){
            //if (strlen(string) < LOW*MAX_STRING/100)
            {
                //printf("TRUE\n" );
                return read(fd, string, MAX_OUT);
            }

            //else return static_cast<long> (0);

        }, string, fd);


        //std::cout << symbols << std::endl;
        //printf("strlen %d\n", strlen(string));
        auto fut2 = async(std::launch::async,[&fut1](char* string){
            //if (strlen(string) > HIGH*MAX_STRING/100)
            {
                printf("strlen %d\n", strlen(string));
                std::this_thread::sleep_for(std::chrono::seconds(1));
                //printf("TRUE\n" );
                return write(1, string, MAX_OUT);
            }
            //else
            //return static_cast<long> (0);
        }, string);

        int res = static_cast<int>(fut1.get());
		symbols += static_cast<int>(res);
	}

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
