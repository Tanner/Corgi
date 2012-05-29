#ifndef CORGI_DEBUG_H_

#define CORGI_DEBUG_H_

#ifdef DEBUG
	#define DALOG(fmt, ...) printf("%s:%d in %s - "fmt"\n", __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__);
	#define DLOG(string) printf("%s:%d in %s - "string"\n", __FILE__, __LINE__, __FUNCTION__);
#else
	#define DALOG(fmt, ...)
	#define DLOG(string)
#endif

#endif