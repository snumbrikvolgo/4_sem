#pragma once
#include <iostream>
#include <utility>
#include <future>

#define CAPACITY 1024
#define OUT 4

class Circular_buffer {
	public:
		Circular_buffer() :
			capacity_(CAPACITY)
	{
		buffer_ = new char [CAPACITY];
		almost_full.second = almost_full.first.get_future();
		almost_empty.second = almost_empty.first.get_future();
	}

		int put(int fd, int sz)
		{


			int ch_read = read(fd, buffer_ + tail_, OUT);

			// if (ch_read == sz % capacity_ || sz >= 0)
			// {
			// 	almost_full.first.set_value(0);
			// }
			mutex_.lock();
			tail_ = (tail_ + ch_read) % capacity_;
			mutex_.unlock();
			// if(full_)
			// {
			// 	tail_ = (tail_ + 1) % capacity_;
			// }

			//head_ = (head_ + 1) % capacity_;

			full_ = head_ == tail_;

			if (size() == capacity_)
			{
				printf("WRITE FULL\n");
				almost_empty.second.get();

				almost_empty.first = std::promise<int>();
				almost_empty.second = almost_empty.first.get_future();
			}
			else if (size() > 0.8*capacity_)
			{
				printf("WRITE BIG\n");
				almost_full.first.set_value(0);
			}

			//almost_full.first.set_value(0);
			return ch_read;

		}

		int get(int fd)
		{
			//std::lock_guard<std::mutex> lock(mutex_);
			int ch_write = 0;

			// if (sz % capacity_ < 0.8*capacity_){
			//
			// }
			if (size() < OUT)
				ch_write = write(fd, buffer_ + head_, size());
			else ch_write = write(fd, buffer_ + head_, OUT);

			mutex_.lock();
			head_ = (head_ + ch_write) % capacity_;
			mutex_.unlock();
			full_ = false;


			if(empty())
			{
				printf("GET EMPTY\n");
				almost_full.second.get();
				almost_full.first = std::promise<int>();
				almost_full.second = almost_full.first.get_future();
			}

			else if(size() < 0.2*capacity_)
			{
				printf("GET ALMOST EMPTY\n");
				almost_empty.first.set_value(0);
			}

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
			return (!full_ && (head_ == tail_) && size() == 0);
		}

		bool full() const
		{
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
