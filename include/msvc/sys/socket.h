
#ifndef _MSVC_SYS_SOCKET_H_
#define _MSVC_SYS_SOCKET_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // !WIN32_LEAN_AND_MEAN

#include <stdint.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <time.h>

#include <libsmb2.h>

#ifdef EBADF
#undef EBADF
#define EBADF WSAENOTSOCK
#endif

typedef SSIZE_T ssize_t;

struct iovec
{
  unsigned long iov_len; // from WSABUF
  void *iov_base;        
};

inline int writev(t_socket sock, struct iovec *iov, int nvecs)
{
  DWORD ret;

  int res = WSASend(sock, (LPWSABUF)iov, nvecs, &ret, 0, NULL, NULL);

  if (res == 0) {
    return (int)ret;
  }
  return -1;
}

inline int readv(t_socket sock, struct iovec *iov, int nvecs)
{
  DWORD ret;
  DWORD flags = 0;

  int res = WSARecv(sock, (LPWSABUF)iov, nvecs, &ret, &flags, NULL, NULL);

  if (res == 0) {
    return (int)ret;
  }
  return -1;
}

inline int close(t_socket sock)
{
  return closesocket(sock);
}

inline void gettimeofday(struct timeval* tp, void* tzp)
{
    time_t clock;
    struct tm time;
    SYSTEMTIME wtm;
    GetLocalTime(&wtm);
    time.tm_year = wtm.wYear - 1900;
    time.tm_mon = wtm.wMonth - 1;
    time.tm_mday = wtm.wDay;
    time.tm_hour = wtm.wHour;
    time.tm_min = wtm.wMinute;
    time.tm_sec = wtm.wSecond;
    time.tm_isdst = -1;
    clock = mktime(&time);
    tp->tv_sec = clock;
    tp->tv_usec = wtm.wMilliseconds * 1000;
    return;
}

#ifdef __cplusplus
}
#endif
#endif /* !_MSVC_SYS_SOCKET_H_ */
