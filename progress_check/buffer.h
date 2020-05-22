#include <iostream>
#pragma once
#define CAPACITY 1024*1024
#define OUT 4*1024
class Circular_buffer {
public:
	Circular_buffer() :
		capacity_(CAPACITY)
	{
        buffer_ = new char [CAPACITY];
    }

	int put(int fd)
	{
		//std::lock_guard<std::mutex> lock(mutex_);
        //printf("I AM IN READ\n" );

        if (full_)
        {
            //wait for free
        }

        //printf("TAIL %d\n", tail_ );

		int ch_read = read(fd, buffer_ + tail_, OUT);
        mutex_.lock();
        tail_ = (tail_ + ch_read) % capacity_;
        mutex_.unlock();
		// if(full_)
		// {
		// 	tail_ = (tail_ + 1) % capacity_;
		// }

		//head_ = (head_ + 1) % capacity_;

		full_ = head_ == tail_;
        return ch_read;
	}

	int get(int fd)
	{
		//std::lock_guard<std::mutex> lock(mutex_);
        int ch_write = 0;
		if(empty())
		{
			//printf("EMPTY\n" );//return T();
            return 0;
		}
        if (size() < OUT)
            ch_write = write(fd, buffer_ + head_, size());
        else ch_write = write(fd, buffer_ + head_, OUT);
        mutex_.lock();
        head_ = (head_ + ch_write) % capacity_;
        mutex_.unlock();
		full_ = false;

        return ch_write;
	}

	void reset()
	{
		std::lock_guard<std::mutex> lock(mutex_);
		head_ = tail_;
		full_ = false;
	}

	bool empty() const
	{
		//if head and tail are equal, we are empty
		return (!full_ && (head_ == tail_));
	}

	bool full() const
	{
		//If tail is ahead the head by 1, we are full
		return full_;
	}

	size_t capacity() const
	{
		return capacity_;
	}

	size_t size() const
	{
		size_t size = capacity_;

		if(!full_)
		{
			if(tail_ >= head_)
			{
				size = tail_ - head_;
			}
			else
			{
				size = capacity_ + tail_ - head_;
			}
		}

		return size;
	}

char *buffer_;
private:
	std::mutex mutex_;
	size_t head_ = 0;
	size_t tail_ = 0;
	const size_t capacity_;
	bool full_ = false;
};
