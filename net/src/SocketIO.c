#include <Socket.h>
#include <sys/socket.h>
#include <stdarg.h>
#include <stdlib.h>

static size_t Socket_write(const void* buf,size_t sz,void* data){
    return write(*((int*)data),buf,sz);
}
static void Socket_writeByte(uint8_t byte,void* data){
    Socket_write(&byte,1,data);
}

static size_t Socket_read(void* out,size_t sz,void* data){
    return read(*((int*)data),out,sz);
}

static int32_t Socket_readByte(void* data){
    uint8_t byte;
    if(Socket_read(&byte,1,data)!=1)
        return -1;
    else
        return byte&0xff;
}

void* Socket_construct(stream_type _unused,va_list args){
    int* ret = (int*) malloc(sizeof(int));
    *ret = va_arg(args,int);
    return ret;
}

void Socket_destroy(void* v){
    free(v);
}
