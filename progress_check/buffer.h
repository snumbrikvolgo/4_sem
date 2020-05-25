#include <cstdio>
#include <memory>
#include <mutex>

#define CAPACITY 1024*1024
#define OUT 4*1024

class circular_buffer {
public:
	explicit circular_buffer() :
		buf_((new char [CAPACITY] )),
		max_size_(CAPACITY)
	{
		almost_full.second = almost_full.first.get_future();
        almost_empty.second = almost_empty.first.get_future();
	}

	int plus(int num)
	{
		std::lock_guard<std::mutex> lock(mutex_);

		//1buf_[head_] = item;

		// if(full_)
		// {
		// 	tail_ = (tail_ + 1) % max_size_;
		// }

		head_ = (head_ + num) % max_size_;
		full_ = head_ == tail_;
	}

	int minus(int num)
	{
		std::lock_guard<std::mutex> lock(mutex_);

		if(empty())
		{
			return char();
		}

		tail_ = (tail_ + num) % max_size_;
		full_ = false;
	}

	void reset()
	{
		std::lock_guard<std::mutex> lock(mutex_);
		head_ = tail_;
		full_ = false;
	}

	bool empty() const
	{
		return (!full_ && (head_ == tail_));
	}

	bool full() const
	{
		return full_;
	}

	size_t capacity() const
	{
		return max_size_;
	}

	size_t size() const
	{
		size_t size = max_size_;

		if(!full_)
		{
			if(head_ >= tail_)
			{
				size = head_ - tail_;
			}
			else
			{
				size = max_size_ + head_ - tail_;
			}
		}

		return size;
	}

	char* buf_;
	size_t head_ = 0;
	size_t tail_ = 0;
	const size_t max_size_;
	bool full_ = 0;
	std::mutex mutex_;
	std::pair<std::promise<int>, std::future<int>> almost_full;
    std::pair<std::promise<int>, std::future<int>> almost_empty;


private:


};
