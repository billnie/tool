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
	BOOL ConnectTest(char * m_server, int m_port)
	{

		struct hostent* host = NULL;
		struct sockaddr_in saddr;
		unsigned int s = 0;
		BOOL  ret;
		time_t start;
		int error;
		host = gethostbyname(m_server);
		if (host == NULL)return  FALSE;

		saddr.sin_family = AF_INET;
		saddr.sin_port = htons(m_port);
		saddr.sin_addr = *((struct in_addr*)host-> h_addr);


		if ((s = socket(AF_INET, SOCK_STREAM, 0))<0) {
			return FALSE;
		}

		unsigned long ul = 1;
		ret = ioctlsocket(s, FIONBIO, (unsigned long*)&ul);
		if (ret == SOCKET_ERROR)return 0;

		if (connect(s, (struct sockaddr*)&saddr, sizeof(saddr)) == -1) {
			error = errno;
			if (errno == EINPROGRESS) {// it is in the connect process
				struct timeval tv;
				fd_set writefds;
				tv.tv_sec = 2;
				tv.tv_usec = 0;
				FD_ZERO(&writefds);
				FD_SET(s, &writefds);
				if (select(s + 1, NULL, &writefds, NULL, &tv)> 0) {
					int len = sizeof(int);
					//下面的一句一定要，主要针对防火墙
					getsockopt(s, SOL_SOCKET, SO_ERROR,(char*) &error, &len);
					if (error == 0) ret = TRUE;
					else ret = FALSE;
				}
				else   ret = FALSE;//timeout or error happen
			}
			else ret = FALSE;
		}
		else    ret = TRUE;

	//	close(s);
		return ret;
	}
	int post(const string& host, const string& port, const string& page, const string& data, string& reponse_data)
	{
		try
		{
//			ConnectTest("192.168.1.1", 80);
			DT(host.c_str());
			boost::asio::io_service io_service;
			//如果io_service存在复用的情况
			if (io_service.stopped())
				io_service.reset();

			//// 从dns取得域名下的所有ip
			tcp::resolver resolver(io_service);
			tcp::resolver::query query(host, port);
			tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
			// 尝试连接到其中的某个ip直到成功 
			tcp::socket socket(io_service);

	//		boost::system::error_code ec;
	//		int sc;
	//		socket.open(boost::asio::ip::tcp::v4());
	//		sc = socket.native();
	//		unsigned long ul = 1;
	//		int ret = ioctlsocket(sc, FIONBIO, (unsigned long*)&ul);
	//		if (ret == SOCKET_ERROR)return 0;
	//		struct timeval timeo = { 3, 0 };
	//		socklen_t len = sizeof(timeo);
	////		setsockopt(sc, SOL_SOCKET, SO_SNDTIMEO,&timeo,len);
	//		// 设为非阻塞  
	//		socket.io_control(boost::asio::ip::tcp::socket::non_blocking_io(true));
	//		// connect时必须指定error_code参数，否则会有异常抛出  
	//		socket.connect(
	//			boost::asio::ip::tcp::endpoint(
	//				boost::asio::ip::address::from_string("192.168.1.2"), 80)
	//			, ec);
	//		fd_set fdWrite;
	//		FD_ZERO(&fdWrite);
	//		FD_SET(socket.native(), &fdWrite);
	//		timeval tv = { 5 };    // 5秒超时  
	//		if (select(0, NULL, &fdWrite, NULL, &tv) <= 0
	//			|| !FD_ISSET(socket.native(), &fdWrite))
	//		{
	//			std::cout << "超时/出错啦" << std::endl;
	//			socket.close();
	//			return 0;
	//		}
	//		// 设回阻塞  
	//		socket.io_control(boost::asio::ip::tcp::socket::non_blocking_io(false));
	//		std::cout << "连接成功" << std::endl;

	//		try
	//		{
	//			#if 0
	//			socket.set_option(boost::asio::ip::tcp::no_delay(true));
	//			socket.set_option(boost::asio::socket_base::keep_alive(true));
	//			#else
	//			socket.set_option(boost::asio::ip::tcp::no_delay(true));
	//			socket.set_option(boost::asio::socket_base::keep_alive(true));
	//			socket.native();
	//			#endif
	//		}
	//		catch (std::exception& e)
	//		{
	//			DT(e.what());
	//		}
			
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
				buffer[len] = '\0';
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
	int MinnerSetReqst::read(char*buffer, int size) {
		int ret;
		data = xpoolset(host,data, ret);
		if (ret == 0 && data.length() < size) {
			memcpy(buffer, data.c_str(), data.length());
			return data.length();
		}
		return 0;
	}
	void AnsyncMinerRequst::initdevs(string host, boost::function<void(int, string, string,void*)> f) {
		alloclen = 2048;
		buffer = std::unique_ptr<char[]>(new char[alloclen]);
		std::fill(buffer.get(), buffer.get() + alloclen, 0);
		reader.init(std::unique_ptr<ByteSourceBase>(new DevsReqst(host)));
		reader.start_read(buffer.get(), alloclen);
		len = reader.finish_read();
		string data;
		data = buffer.get();
		f(cmdDevs,host,data,obj);
		reader.start_read(buffer.get()+len, alloclen-len);
	}
	void AnsyncMinerRequst::initgetminnser(string host, boost::function<void(int, string, string, void*)> f) {
		alloclen = 2048;
		buffer = std::unique_ptr<char[]>(new char[alloclen]);
		std::fill(buffer.get(), buffer.get() + alloclen, 0);
		reader.init(std::unique_ptr<ByteSourceBase>(new MinnerReqst(host)));
		reader.start_read(buffer.get(), alloclen);
		len = reader.finish_read();
		string data;
		data = buffer.get();
		f(cmdgetMinner, host, data, obj);
		reader.start_read(buffer.get() + len, alloclen - len);
	}
	void AnsyncMinerRequst::initsaveminner(string host, string data,boost::function<void(int, string, string, void*)> f) {
		alloclen = 2048;
		buffer = std::unique_ptr<char[]>(new char[alloclen]);
		std::fill(buffer.get(), buffer.get()+alloclen, 0);
		reader.init(std::unique_ptr<ByteSourceBase>(new MinnerSetReqst(host,data)));
		reader.start_read(buffer.get(), alloclen);
		len = reader.finish_read();
		string da;
		da = buffer.get();
		f(cmdsaveMinner, host, da, obj);
		reader.start_read(buffer.get() + len, alloclen - len);
	}
	void AnsyncMinerRequst::initdevslist(string host,int start, int end, boost::function<void(int, string, string, void*)> f) {
		alloclen = 2048;
		buffer = std::unique_ptr<char[]>(new char[alloclen]);
		std::fill(buffer.get(), buffer.get() + alloclen, 0);
		int i;
		string ss;
		for (i = start; i <= end; i++) {
			AsynchronousReader rd;
			ss = str::format("%s.%d",host.c_str(), i);
			rd.init(std::unique_ptr<ByteSourceBase>(new DevsReqst(ss)));
			rd.start_read(buffer.get(), alloclen);
			len = rd.finish_read();
			string data;
			if(len >0) data = buffer.get();
			f(cmdDevs, ss, data, obj);
			rd.start_read(buffer.get() + len, alloclen - len);
		}
	}
}

