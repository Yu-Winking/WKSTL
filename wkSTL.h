#pragma once

#include <queue>
#include <mutex>
#include <deque>
#include <string>
#include <iomanip>

namespace wkSTL
{
	using namespace std;

	template <class T>
	class Queue
	{
	public:
		Queue(Queue const&) = delete;
		Queue(Queue&&) = delete;
		Queue& operator=(Queue const&) = delete;
		Queue& operator=(Queue&&) = delete;

		Queue()
			: queue_(), mutex_()
		{}

		virtual ~Queue()
		{
			while (!queue_.empty())
				queue_.pop();
		}

		void push(T _record)
		{
			lock_guard<mutex> lock(mutex_);
			queue_.emplace(move(_record));
		}

		bool pop(T& _record)
		{
			lock_guard<mutex> lock(mutex_);

			if (queue_.empty())
				return false;

			_record = move(queue_.front());
			queue_.pop();

			return true;
		}

		size_t size()
		{
			lock_guard<mutex> lock(mutex_);
			return queue_.size();
		}

		bool isEmpty()
		{
			lock_guard<mutex> lock(mutex_);
			return queue_.empty();
		}

		void clear()
		{
			lock_guard<mutex> lock(mutex_);
			while (!queue_.empty())
				queue_.pop();
		}

	private:
		queue<T> queue_;
		mutex mutex_;
	};

	class Pipeline
	{
	public:
		Pipeline(Pipeline const&) = delete;
		Pipeline(Pipeline&&) = delete;
		Pipeline& operator=(Pipeline const&) = delete;
		Pipeline& operator=(Pipeline&&) = delete;

		Pipeline()
		{}

		virtual ~Pipeline()
		{
			deque_.clear();
		}

		size_t push(uint8_t _in)
		{
			lock_guard<mutex> lock(mutex_);
			deque_.push_back(_in);

			return deque_.size();
		}

		template <typename T>
		size_t push(const T& _in)
		{
			uint8_t* add = (uint8_t*)(&_in);

			lock_guard<mutex> lock(mutex_);
			deque_.resize(deque_.size() + sizeof(T));
			copy_backward(add, add+sizeof(T), deque_.end());

			return sizeof(T);
		}

		size_t push(const char* _buf, int _len)
		{
			lock_guard<mutex> lock(mutex_);

			deque_.resize(deque_.size() + _len);
			copy_backward(_buf, _buf + _len, deque_.end());

			return static_cast<size_t>(_len);
		}

		template <typename T>
		size_t push(const vector<T>& _vector)
		{
			size_t pushCount{ 0 };

			lock_guard<mutex> lock(mutex_);
			for (auto it: _vector)
			{
				uint8_t* add = (uint8_t*)(&it);

				deque_.resize(deque_.size() + sizeof(T));
				copy_backward(add, add+sizeof(T), deque_.end());

				pushCount += sizeof(T);
			}

			return pushCount;
		}

		size_t push(const string& _str)
		{
			lock_guard<mutex> lock(mutex_);

			size_t strLen = _str.length();

			deque_.resize(deque_.size() + strLen);
			copy_backward(_str.begin(), _str.end(), deque_.end());

			return strLen;
		}

		size_t push(const vector<string>& _vector)
		{
			size_t pushCount{ 0 };
			for (auto it: _vector)
				pushCount += push(it);

			return pushCount;
		}

		template <typename T>
		const deque<uint8_t>::iterator search(const T& _in)
		{
			uint8_t* add = (uint8_t*)(&_in);

			deque<uint8_t> temp;
			temp.resize(sizeof(T));
			copy_backward(add, add+sizeof(T), temp.end());

			return std::search(deque_.begin(), deque_.end(), temp.begin(), temp.end());
		}

		const deque<uint8_t>::iterator search(const char* _buf, const int _len)
		{
			deque<uint8_t> temp;
			temp.resize(_len);
			copy_backward(_buf, _buf+_len, temp.end());

			return std::search(deque_.begin(), deque_.end(), temp.begin(), temp.end());
		}

		const deque<uint8_t>::iterator search(const vector<string>& _vector)
		{
			deque<uint8_t> temp{};

			for (auto it : _vector)
			{
				temp.resize(temp.size() + it.length());
				copy_backward(it.begin(), it.end(), temp.end());
			}

			return std::search(deque_.begin(), deque_.end(), temp.begin(), temp.end());
		}

		template <typename T>
		const deque<uint8_t>::iterator search(const vector<T>& _vector)
		{
			deque<uint8_t> temp;

			for (auto it: _vector)
			{
				uint8_t* add = (uint8_t*)(&it);

				temp.resize(temp.size() + sizeof(T));
				copy_backward(add, add+sizeof(T), temp.end());
			}

			return std::search(deque_.begin(), deque_.end(), temp.begin(), temp.end());
		}

		const deque<uint8_t>::iterator search(const string& _str)
		{
			deque<uint8_t> temp;
			temp.resize(_str.length());
			copy_backward(_str.begin(), _str.end(), temp.end());

			return std::search(deque_.begin(), deque_.end(), temp.begin(), temp.end());
		}

		long long at(deque<uint8_t>::iterator _it)
		{
			if (_it != deque_.end())
				return std::distance(deque_.begin(), _it);

			return -1;
		}

		size_t pop(char* _buf, int _len)
		{
			lock_guard<mutex> lock(mutex_);

			size_t dSize(deque_.size());

			if (_len >= static_cast<int>(dSize))
			{
				copy(deque_.begin(), deque_.end(), _buf);
				deque_.erase(deque_.begin(), deque_.end());
			}
			else
			{
				copy(deque_.begin(), deque_.begin() + _len, _buf);
				deque_.erase(deque_.begin(), deque_.begin() + _len);

				dSize = _len;
			}

			return dSize;
		}

		size_t isEmpty() const
		{
			lock_guard<mutex> lock(mutex_);
			return deque_.empty();
		}

		void clear()
		{
			lock_guard<mutex> lock(mutex_);
			deque_.clear();
		}

		size_t length() const
		{
			lock_guard<mutex> lock(mutex_);
			return deque_.size();
		}

		friend ostream& operator<<(ostream& _os, Pipeline& _pipeline)
		{
			ios_base::fmtflags f{ _os.flags() };

			for (auto i:_pipeline.deque_)
			{
				_os << right << setw(2) << setfill('0') << hex << +(i) << ' ';
			}

			_os.flags(f);
			//_os << endl;

			return _os;
		}

	private:
		deque<uint8_t> deque_;
		mutable mutex mutex_;
	};
}
