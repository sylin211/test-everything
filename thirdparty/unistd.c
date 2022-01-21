
#include <time.h>
#include <openssl/ssl.h>
#include <windows.h>

#ifdef _MSC_VER

int gettimeofday(struct timeval* tp, void* tzp)
{
	time_t clock;
	struct tm tm;
	SYSTEMTIME wtm;
	GetLocalTime(&wtm);
	tm.tm_year = wtm.wYear - 1900;
	tm.tm_mon = wtm.wMonth - 1;
	tm.tm_mday = wtm.wDay;
	tm.tm_hour = wtm.wHour;
	tm.tm_min = wtm.wMinute;
	tm.tm_sec = wtm.wSecond;
	tm.tm_isdst = -1;
	clock = mktime(&tm);
	tp->tv_sec = clock;
	tp->tv_usec = wtm.wMilliseconds * 1000;
	return (0);
}

unsigned int sleep(unsigned seconds)
{
	Sleep(seconds * 1000);
}

int SSL_connect_ptime(SSL* ssl, time_t ssl_time)
{
	SSL_connect(ssl);
}

#endif