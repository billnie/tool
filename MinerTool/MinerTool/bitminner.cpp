#include "stdafx.h"
#include "bitminner.h"
#include <process.h>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "stlstr.h"
using boost::asio::ip::tcp;
void DT(const char * strOutputString, ...);
namespace bitminner {

	int post(const string& host, const string& port, const string& page, const string& data, string& reponse_data)
	{
		try
		{
			DT(host.c_str());
			boost::asio::io_service io_service;
			//如果io_service存在复用的情况
			if (io_service.stopped())
				io_service.reset();

			// 从dns取得域名下的所有ip
			tcp::resolver resolver(io_service);
			tcp::resolver::query query(host, port);
			tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
			// 尝试连接到其中的某个ip直到成功 
			tcp::socket socket(io_service);
			boost::asio::connect(socket, endpoint_iterator);

			// Form the request. We specify the "Connection: close" header so that the
			// server will close the socket after transmitting the response. This will
			// allow us to treat all data up until the EOF as the content.
			boost::asio::streambuf request;
			std::ostream request_stream(&request);
			request_stream << "POST " << page << " HTTP/1.0\r\n";
			request_stream << "Host: " << host << ":" << port << "\r\n";
			request_stream << "Accept: */*\r\n";
			request_stream << "Content-Length: " << data.length() << "\r\n";
			request_stream << "Content-Type: application/x-www-form-urlencoded\r\n";
			request_stream << "Connection: close\r\n\r\n";
			request_stream << data;

			// Send the request.
			boost::asio::write(socket, request);

			// Read the response status line. The response streambuf will automatically
			// grow to accommodate the entire line. The growth may be limited by passing
			// a maximum size to the streambuf constructor.
			boost::asio::streambuf response;
			boost::asio::read_until(socket, response, "\r\n");
			// Check that response is OK.
			std::istream response_stream(&response);
			std::string http_version;
			response_stream >> http_version;
			unsigned int status_code;
			response_stream >> status_code;
			std::string status_message;
			std::getline(response_stream, status_message);
			if (!response_stream || http_version.substr(0, 5) != "HTTP/")
			{
				reponse_data = "Invalid response";
				return -2;
			}
			// 如果服务器返回非200都认为有错,不支持301/302等跳转
			if (status_code != 200)
			{
				reponse_data = "Response returned with status code != 200 ";
				return status_code;
			}

			// 传说中的包头可以读下来了
			std::string header;
			std::vector<string> headers;
			while (std::getline(response_stream, header) && header != "\r")
				headers.push_back(header);

			// 读取所有剩下的数据作为包体
			boost::system::error_code error;
			while (boost::asio::read(socket, response,
				boost::asio::transfer_at_least(1), error))
			{
			}
			//响应有数据
			if (response.size())
			{
				std::istream response_stream(&response);
				std::istreambuf_iterator<char> eos;
				reponse_data = string(std::istreambuf_iterator<char>(response_stream), eos);
			}

			if (error != boost::asio::error::eof)
			{
				reponse_data = error.message();
				return -3;
			}
		}
		catch (std::exception& e)
		{
			reponse_data = e.what();
			return -4;
		}
		return 0;
	}

	string xdevs(string host, int &ret)
	{
		string port = "80";
		string page = "/devs";
		string data = "";
		string reponse_data;
		ret = post(host, port, page, data, reponse_data);
		if (ret != 0)
			std::cout << "error_code:" << ret << std::endl;
		std::cout << reponse_data << std::endl;
		DT(reponse_data.c_str());
		return reponse_data;
	}
	string xgetminner(string host, int &ret)
	{
		string port = "80";
		string page = "/getminer";
		string data = "";
		string reponse_data;

		ret = post(host, port, page, data, reponse_data);
		if (ret != 0)
			std::cout << "error_code:" << ret << std::endl;
		std::cout << reponse_data << std::endl;
		DT(reponse_data.c_str());
		return reponse_data;
	}
	string xpoolset(string host, string data, int &ret)
	{
		string port = "80";
		string page = "/saveminner";
		string reponse_data;

		ret = post(host, port, page, data, reponse_data);
		if (ret != 0)
			std::cout << "error_code:" << ret << std::endl;
		std::cout << reponse_data << std::endl;
		DT(reponse_data.c_str());
		return reponse_data;
	}

	string xnet(string host, int &ret)
	{
		string port = "80";
		string page = "/net";
		string reponse_data;
		ret = post(host, port, page, "", reponse_data);
		if (ret != 0)
			std::cout << "error_code:" << ret << std::endl;
		std::cout << reponse_data << std::endl;
		DT(reponse_data.c_str());
		return reponse_data;
	}
	string xnetset(string host, string data, int &ret)
	{
		string port = "80";
		string page = "/netset";
		string reponse_data;

		ret = post(host, port, page, data, reponse_data);
		if (ret != 0)
			std::cout << "error_code:" << ret << std::endl;
		std::cout << reponse_data << std::endl;
		DT(reponse_data.c_str());
		return reponse_data;
	}
	int DevsReqst::read(char*buffer, int size) {
		if (len == 0) {
			int ret;
			data = xdevs(host,ret);
			len = data.length();
			if (ret ==0 && data.length() < size) {
				memcpy(buffer, data.c_str(), data.length());
				return data.length();
			}
		}
		return 0;
	}
	int MinnerReqst::read(char*buffer, int size) {
		int ret;
		data = xgetminner(host,ret);
		if (ret == 0&&  data.length() < size) {
			memcpy(buffer, data.c_str(), data.length());
			return data.length();
		}
		return 0;
	}
	void AnsyncMinerRequst::initdevs(string host, boost::function<void(int, string, string,void*)> f) {
		alloclen = 2048;
		buffer = std::unique_ptr<char[]>(new char[alloclen]);
		reader.init(std::unique_ptr<ByteSourceBase>(new DevsReqst(host)));
		reader.start_read(buffer.get(), alloclen);
		len = reader.finish_read();
		string data;
		data = buffer.get();
		f(1,host,data,obj);
		reader.start_read(buffer.get()+len, alloclen-len);
		len++;
	}
	void AnsyncMinerRequst::initdevslist(string host,int start, int end, boost::function<void(int, string, string, void*)> f) {
		alloclen = 2048;
		buffer = std::unique_ptr<char[]>(new char[alloclen]);
		int i;
		string ss;
		for (i = start; i < end; i++) {
			AsynchronousReader rd;
			ss = str::format("%s.%d",host.c_str(), i);
			rd.init(std::unique_ptr<ByteSourceBase>(new DevsReqst(ss)));
			rd.start_read(buffer.get(), alloclen);
			len = rd.finish_read();
			string data;
			if(len >0) data = buffer.get();
			f(1, ss, data, obj);
			rd.start_read(buffer.get() + len, alloclen - len);
		}
		len++;
	}
}

