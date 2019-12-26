#ifndef IO_STREAMWRAPPER_HPP_2019_12_15_17_47
#define IO_STREAMWRAPPER_HPP_2019_12_15_17_47

#include <Stream.h>
#include <type_traits>
#include <utility>
#include <cstddef>

namespace io{
    enum class status : stream_status{
        ok = IO_status_OK,
        eof = IO_status_EOF,
        error = IO_status_ERROR
    };
    struct input_stream{
    private:
        InputStream* wrapped;
    public:
        template<typename... Args> input_stream(const StreamCalls* calls,Args&&... args):wrapped{InputStream_new(calls,static_cast<std::remove_reference_t<Args>>(std::forward<Args>(args))...)}{}
        input_stream(input_stream&& stream):wrapped{std::exchange(stream.wrapped,nullptr)}{}
        input_stream(const input_stream&)=delete;
        input_stream& operator=(input_stream&& stream){
            std::swap(wrapped,stream.wrapped);
            return *this;
        }
        input_stream& operator=(const input_stream&)=delete;
        ~input_stream(){
            if(wrapped)
                InputStream_destroy(wrapped);
        }
        
        std::size_t read(void* v,std::size_t sz){
            return InputStream_read(wrapped,v,sz);
        }
        
        int32_t read(){
            return InputStream_readByte(wrapped);
        }
        
        status stream_status()const noexcept{
            return static_cast<status>(InputStream_checkError(wrapped));
        }
        
        void clear_status(){
            InputStream_clearError(wrapped);
        }
        
        explicit operator bool()const noexcept{
            return stream_status()==0;
        }
        
        bool operator!()const noexcept{
            return stream_status()!=0;
        }
        
        template<typename Byte,std::size_t N,typename=std::enable_if_t<sizeof(Byte)==1&&(std::is_integral_v<Byte>||std::is_enum_v<Byte>)&&!std::is_const_v<Byte>>>
            std::size_t readBytes(Byte(&arr)[N]){
                return read(arr,N);
            }
    };
}

#endif
