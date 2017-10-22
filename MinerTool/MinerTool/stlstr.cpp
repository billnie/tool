

#include	 "stlstr.h"
#include "StdAfx.h"

#include <iostream>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>

#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/common.hpp>
   
#include <boost/xpressive/xpressive_dynamic.hpp>  
using namespace boost::xpressive;
namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;
namespace str
{
	int initlog(std::string file) {
		// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
		//  执行此操作
		char tempbuf[128];
		char strtm[32] = { 0 };

		time_t rawtime;
		struct tm * timeinfo;
		time(&rawtime);

		timeinfo = localtime(&rawtime);

		strftime(tempbuf, 128, ".\\log\\%Y%m%d_%H%M%S_1.log", timeinfo);
		boost::log::add_file_log(
			keywords::auto_flush = true,
			keywords::file_name = tempbuf,// "log_%N.log",// AppHolder::Instance().config().log_folder + "/sign_%Y-%m-%d_%H-%M-%S.%N.log",
			keywords::rotation_size = 10 * 1024 * 1024,
			keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
			keywords::min_free_space = 3 * 1024 * 1024,
			keywords::format = "[%TimeStamp%]: %Message%"
			);
		//	logging::add_file_log("log.log");
		//	logging::core::get()->set_logging_enabled(true);
		boost::log::add_common_attributes();
		//SetFilter1();
		BOOST_LOG_TRIVIAL(trace) << "---欢迎使用dofus游戏辅助!---";
		return 0;
	}
	int log(int lvl, char *fmt, ...) {
		std::string strResult = "";
		if (NULL != fmt)
		{
			va_list marker = NULL;
			va_start(marker, fmt);                            //初始化变量参数 
			size_t nLength = _vscprintf(fmt, marker) + 1;    //获取格式化字符串长度
			std::vector<char> vBuffer(nLength, '\0');        //创建用于存储格式化字符串的字符数组
			int nWritten = _vsnprintf_s(&vBuffer[0], vBuffer.size(), nLength, fmt, marker);
			if (nWritten > 0)
			{
				strResult = &vBuffer[0];
			}
			va_end(marker);                                    //重置变量参数
			switch (lvl) {
			case 0:
				BOOST_LOG_TRIVIAL(trace) << strResult;
				break;
			case 1:
				BOOST_LOG_TRIVIAL(trace) << strResult;
				break;
			default:
				BOOST_LOG_TRIVIAL(trace) << strResult;
			}
		}
		return 0;
	}
	std::string format(const char *fmt, ...)
	{
		std::string strResult = "";
		if (NULL != fmt)
		{
			va_list marker = NULL;
			va_start(marker, fmt);                            //初始化变量参数 
			size_t nLength = _vscprintf(fmt, marker) + 1;    //获取格式化字符串长度
			std::vector<char> vBuffer(nLength, '\0');        //创建用于存储格式化字符串的字符数组
			int nWritten = _vsnprintf_s(&vBuffer[0], vBuffer.size(), nLength, fmt, marker);
			if (nWritten > 0)
			{
				strResult = &vBuffer[0];
			}
			va_end(marker);                                    //重置变量参数
		}
		return strResult;
	}
	//字符串格式化函数
	std::wstring format(const wchar_t *fmt, ...)
	{
		std::wstring strResult = L"";
		if (NULL != fmt)
		{
			va_list marker = NULL;
			va_start(marker, fmt);                            //初始化变量参数
			size_t nLength = _vscwprintf(fmt, marker) + 1;    //获取格式化字符串长度
			std::vector<wchar_t> vBuffer(nLength, L'\0');    //创建用于存储格式化字符串的字符数组
			int nWritten = _vsnwprintf_s(&vBuffer[0], vBuffer.size(), nLength, fmt, marker);
			if (nWritten > 0)
			{
				strResult = &vBuffer[0];
			}
			va_end(marker);                                    //重置变量参数
		}
		return strResult;
	}

	bool isregxip(std::string str) {
		cregex reg_ip = cregex::compile("(25[0-4]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[1-9])[.](25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])[.](25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])[.](25[0-4]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[1-9])");
		return  regex_match(str.c_str(), reg_ip);
	}
}