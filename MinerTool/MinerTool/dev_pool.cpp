
#include	"stdafx.h"
#include "dev_pool.h"
static unsigned char hexchars[] = "0123456789ABCDEF";
char *php_url_encode(char const *s, int len, int *new_length)
{
	register unsigned char c;
	unsigned char *to, *start;
	unsigned char const *from, *end;

	from = (unsigned char *)s;
	end = (unsigned char *)s + len;
	start = to = (unsigned char *)calloc(1, 3 * len + 1);

	while (from < end)
	{
		c = *from++;

		if (c == ' ')
		{
			*to++ = '+';
		}
		else if ((c < '0' && c != '-' && c != '.') ||
			(c < 'A' && c > '9') ||
			(c > 'Z' && c < 'a' && c != '_') ||
			(c > 'z'))
		{
			to[0] = '%';
			to[1] = hexchars[c >> 4];
			to[2] = hexchars[c & 15];
			to += 3;
		}
		else
		{
			*to++ = c;
		}
	}
	*to = 0;
	if (new_length)
	{
		*new_length = to - start;
	}
	return (char *)start;
}
string dev_pool::urlcodestring() {
	string s;
	if (bPrefix) {
		s = prefix.c_str();
	}
	s += url.c_str();
	s += "|";
	s += username.c_str();
	s += "|";
	s += password.c_str();
	//	s += "|";
	return s;
}
string dev_pool::pool2string() {
	string s;
	if (bPrefix) {
		s = prefix.c_str();
	}
	s += url.c_str();
	s += "|";
	s += username.c_str();
	s += "|";
	s += password.c_str();
//	s += "|";
	return s;
}
string dev_pools::jsonpools() {
	string s,ss;
	int i = 1;
	char buf[255] = { 0 };
	vector<dev_pool>::iterator it;
	s = "{";
	for (it = pools.begin(); it != pools.end();) {
		sprintf(buf, "\"Pool%d\":", i);
		s += buf; s += "\"";
		ss= it->pool2string();
		s += ss; s += "\"";
		s += ",";
		it++;	i++;
	}
	s += "\"Frequency\":";
	sprintf(buf, "%d", Frequency);
	s += buf;	s += "}";
	return s;
}
string dev_pools::urlcodestring() {
	string s, ss;
	int i = 1;
	char buf[255] = { 0 };
	vector<dev_pool>::iterator it;
	s = "";
	int tlen;
	char *sz;
	for (it = pools.begin(); it != pools.end();) {
		sprintf(buf, "Pool%d=", i);
		s += buf; 
		ss = it->pool2string();
		sz = php_url_encode(ss.c_str(), ss.length(), &tlen);
		if (sz) {
			s += sz; free(sz);
		}
		 
		s += "&";
		it++;	i++;
	}
	s += "&Frequency=";
	sprintf(buf, "%d", Frequency);
	s += buf;	
	return s;
}