#pragma once
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <utility>
#include <cstdio>
#include <exception>
#ifndef CSV_IO_NO_THREAD
#include <mutex>
#include <thread>
#include <condition_variable>
#endif
#include <memory>
#include <cassert>
#include <cerrno>
#include <istream>
#include <boost/bind.hpp>  
#include <boost/function.hpp>  
using namespace std;
namespace bitminner {
	string xdevs(string host, int &ret);
	string xgetminner(string host, int &ret);
	string xpoolset(string host, string data, int &ret);
	string xnet(string host, int &ret);
	string xnetset(string host, string data, int &ret);
	class ByteSourceBase {
	public:
		ByteSourceBase() { len = 0; }
		virtual int read(char*buffer, int size) = 0;
		virtual ~ByteSourceBase() {}
		int len;
		string data;
	};
	
	class DevsReqst : public ByteSourceBase {
	public:
		explicit DevsReqst(string host) :host(host) {}
		int read(char*buffer, int size);
		~DevsReqst() {}
	private:string host;
	};
	class MinnerReqst : public ByteSourceBase {
	public:
		explicit MinnerReqst(string host) :host(host) {}
		int read(char*buffer, int size);
		~MinnerReqst() {}
	private:string host;
	};
	class AsynchronousReader {
	public:
		void init(std::unique_ptr<ByteSourceBase>arg_byte_source) {
			std::unique_lock<std::mutex>guard(lock);
			byte_source = std::move(arg_byte_source);
			desired_byte_count = -1;
			termination_requested = false;
			worker = std::thread(
				[&] {
				std::unique_lock<std::mutex>guard(lock);
				try {
					for (;;) {
						read_requested_condition.wait(
							guard,
							[&] {
							return desired_byte_count != -1 || termination_requested;
						}
						);
						if (termination_requested)
							return;

						read_byte_count = byte_source->read(buffer, desired_byte_count);
						desired_byte_count = -1;
						if (read_byte_count == 0)
							break;
						read_finished_condition.notify_one();
					}
				}
				catch (...) {
					read_error = std::current_exception();
				}
				read_finished_condition.notify_one();
			}
			);
		}

		bool is_valid()const {
			return byte_source != nullptr;
		}

		void start_read(char*arg_buffer, int arg_desired_byte_count) {
			std::unique_lock<std::mutex>guard(lock);
			buffer = arg_buffer;
			desired_byte_count = arg_desired_byte_count;
			read_byte_count = -1;
			read_requested_condition.notify_one();
		}

		int finish_read() {
			std::unique_lock<std::mutex>guard(lock);
			read_finished_condition.wait(
				guard,
				[&] {
				return read_byte_count != -1 || read_error;
			}
			);
			if (read_error)
				std::rethrow_exception(read_error);
			else
				return read_byte_count;
		}

		~AsynchronousReader() {
			if (byte_source != nullptr) {
				{
					std::unique_lock<std::mutex>guard(lock);
					termination_requested = true;
				}
				read_requested_condition.notify_one();
				worker.join();
			}
		}
	private:
		std::unique_ptr<ByteSourceBase>byte_source;

		std::thread worker;

		bool termination_requested;
		std::exception_ptr read_error;
		char*buffer;
		int desired_byte_count;
		int read_byte_count;

		std::mutex lock;
		std::condition_variable read_finished_condition;
		std::condition_variable read_requested_condition;
	};
	class AnsyncMinerRequst {
	public:
		int len,alloclen;
		void *obj;
		AnsyncMinerRequst() { len = 0; obj = NULL; };
		AsynchronousReader reader;
		std::unique_ptr<char[]>buffer;
		void initdevs(string host,boost::function<void(int, string, string, void*)> f);
		void initdevslist(string host,int start,int end, boost::function<void(int, string, string, void*)> f);
	};
}