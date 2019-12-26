#ifndef UTIL_NET_SOCKET_H_2019_12_03_11_36
#define UTIL_NET_SOCKET_H_2019_12_03_11_36

#include <Stream.h>

#ifdef __cplusplus
extern"C"{
#endif

/*
* Returns a set of Stream Calls that sends and recieves data on a Stream Socket.
* Both constructors take a single int fd, which shall be an open file descriptor bound to a socket
*  with type SOCK_STREAM or SOCK_RAW.
*/
const StreamCalls* IO_streamSocket();


#ifdef __cplusplus
};
#endif

#endif
