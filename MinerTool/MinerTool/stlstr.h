#include <stdarg.h>
#include <string>
#include <vector>
#include <cassert>

//#pragma once
#ifndef __STR_STR_HPP_INCLUDED_
#define __STR_STR_HPP_INCLUDED_
namespace str
{
	int initlog(std::string file);
    //�ַ�����ʽ������
    std::string format(const char *fmt,...);
    
	int log(int lvl, char *fmt, ...);
    //�ַ�����ʽ������
    std::wstring format(const wchar_t *fmt,...);
    
	//�ж��Ƿ�Ϊip
	bool isregxip(std::string str);
}
#endif