#pragma once
#include <iostream>
#include <utility>
#include <future>

#define CAPACITY 1024*1024
#define OUT 4*1024

class Circular_buffer {
public:
	Circular_buffer() :
		capacity_(CAPACITY)
	{
        buffer_ = new char [CAPACITY];
        almost_full.second = almost_full.first.get_future();
        almost_empty.second = almost_empty.first.get_future();
    }

	int put(int fd)
	{
        mutex_.lock();
		//std::lock_guard<std::mutex> lock(mutex_);
        //printf("I AM IN READ\n" );

        if (size() == capacity_)
        {
            almost_empty.second.get();

            almost_empty.first = std::promise<int>();
            almost_empty.second = almost_empty.first.get_future();
        }
        if (size() > 0.8*capacity_)
        {
            almost_full.first.set_value(0);
            //almost_full.
            //wait for free
        }
        //printf("TAIL %d\n", tail_ );

		int ch_read = read(fd, buffer_ + tail_, OUT);

        tail_ = (tail_ + ch_read) % capacity_;

		// if(full_)
		// {
		// 	tail_ = (tail_ + 1) % capacity_;
		// }

		//head_ = (head_ + 1) % capacity_;

		full_ = head_ == tail_;
        mutex_.unlock();
        return ch_read;

	}

	int get(int fd)
	{
		//std::lock_guard<std::mutex> lock(mutex_);
        int ch_write = 0;
        mutex_.lock();

        if(size() < 0.2*capacity_)
        {
            almost_empty.first.set_value(0);
        }
		if(empty())
		{
			almost_full.second.get();
            almost_full.first = std::promise<int>();
            almost_full.second = almost_full.first.get_future();
		}
        if (size() < OUT)
            ch_write = write(fd, buffer_ + head_, size());
        else ch_write = write(fd, buffer_ + head_, OUT);

        head_ = (head_ + ch_write) % capacity_;

		full_ = false;
        mutex_.unlock();
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
    std::pair<std::promise<int>, std::future<int>> almost_full;
    std::pair<std::promise<int>, std::future<int>> almost_empty;

	std::mutex mutex_;
	size_t head_ = 0;
	size_t tail_ = 0;
	const size_t capacity_;
	bool full_ = false;
};
