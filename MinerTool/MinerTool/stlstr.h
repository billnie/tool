#include <stdarg.h>
#include <string>
#include <vector>
#include <cassert>
void DT(const char * strOutputString, ...);
//#pragma once
#ifndef __STR_STR_HPP_INCLUDED_
#define __STR_STR_HPP_INCLUDED_
namespace str
{
	int read_file(std::vector<std::string> &data, std::string szFile);
	int initlog(std::string file);
    //字符串格式化函数
    std::string format(const char *fmt,...);
    
	int log(int lvl, char *fmt, ...);
    //字符串格式化函数
    std::wstring format(const wchar_t *fmt,...);
    
	//判断是否为ip
	bool isregxip(std::string str);
}
#endif