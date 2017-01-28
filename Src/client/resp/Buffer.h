/*************************************************************************
	> File Name: Buffer.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月21日 星期六 10时15分18秒
 ************************************************************************/

#ifndef _BUFFER_H
#define _BUFFER_H
#include <string>
#include <cstring>
#include <cstdlib>

namespace resp{
class Buffer{
public:
    Buffer():capacity_(0),data_(0),size_(0){}
    Buffer(char const* ptr):capacity_(0),data_(const_cast<char*>(ptr)),size_(std::strlen(ptr)){
        
    }
    Buffer(std::string const& str)
    :capacity_(0),data_(const_cast<char*>(str.data())),size_(str.size()){}
    Buffer(char const* ptr,size_t size):capacity_(0),data_(const_cast<char*>(ptr)),size_(size_){}
    Buffer(Buffer const& other):capacity_(other.capacity_),data_(0),size_(other.size_){
        if(other.is_ref()){
            data_ = other.data_;
        }else if(other.is_small()){
            data_ = small_;
        }else{
            data_ = (char *)std::malloc(capacity_);
            if(data_ == 0){
                throw std::bad_alloc();
            }
        }
        if(!is_ref()){
            std::memcpy(data_,other.data_,size_);
        }
}
    static void move(Buffer& des,Buffer& src){
        des.reset();
        if(src.is_ref()){
            des.data_ = src.data_;
            des.size_ = src.size_;
        }else if(src.is_small()){
            des.capacity = RESP_SMALL_BUFFER_SIZE;
            des.data_ = des.small_;
            des.size_ = src.size_;
            std::memcpy(des.data_,src.data_,des.size_);
        }else{
            des.capacity_ = src.capacity_;
            des.data_ = src.data_;
            des.size_ = src.size_;
        }
        src.capacity_ = 0;
        src.data_ = 0;
        src.size_ = 0;
    }
    ~Buffer(){
        dealloc();
    }
    Buffer& operator = (Buffer const& rhs){
        if(this != &rhs){
            if(rhs.is_ref()){
                dealloc();
                capacity_ = 0;
                data_ = rhs.data_;
            }else if(rhs.is_small()){
                dealloc();
                capacity_ = RESP_SMALL_BUFFER_SIZE;
                data_ = small_;
            }else{
                if(rhs.capacity_ > capacity_){
                    if(is_ref() || is_small()){
                        data_ = 0;
                    }
                    data_ = (char*)std::realloc(data_,rhs.capacity_);
                    if(data_ == 0){
                        throw std::bad_alloc();
                    }
                    capacity_ = rhs.capacity_;
                }
            }
            size_ = rhs.size_;
            if(!is_ref()){
                std::memcpy(data_,rhs.data_,size_);
            }
        }
        return *this;
    }
public:
    char const* data() const{
        return data_;
    }
    char* data(){
        return data_;
    }
    size_t size() const{
        return size_;
    }
    bool empty() const{
       return size_ == 0; 
    }
    bool is_ref() const{
        return capacity_ == 0;
    }
    bool is_small() const{
        return capacity_ > 0 && capacity_ <= RESP_SMALL_BUFFER_SIZE;
    }
    bool is_large() const{
        return capacity_ > RESP_SMALL_BUFFER_SIZE;
    }
    bool operator == (char const* rhs)const{
        if(std::strlen(rhs) != size_){
            return false;
        }
        return std::memcmp(data_,rhs,size_) == 0;
    }
    bool operator == (std::string const& rhs) const{
        if(rhs.size() != size_){
            return false;
        }
        return std::memcpy(data_,rhs.data(),size_) == 0;
    }
    void clear(){
        size_ = 0;
    }
    void reset(){
        dealloc();
        capacity_ = 0;
        size_ = 0;
        data_ = 0;
    }
    //reserve只能按照RESP_SMALL_BUFFER_SIZE成倍数增加其大小
    void reserve(size_t capacity){
        if(capacity > capacity_){
            capacity = 
            capacity % RESP_SMALL_BUFFER_SIZE == 0 ? 
            capacity:RESP_SMALL_BUFFER_SIZE * (capacity / RESP_SMALL_BUFFER_SIZE +1);
            if(is_ref() || is_small()){
                char const* ptr = data_;
                bool is_small_before = is_small();
                if(capacity > RESP_SMALL_BUFFER_SIZE){
                    capacity_ = capacity;
                    data_ = (char *)std::malloc(capacity_);
                    if(data_ == 0){
                        throw std::bad_alloc();
                    }
                }else{
                    capacity_ = RESP_SMALL_BUFFER_SIZE;
                    data_ = small_;
                }
                if(!(is_small_before && is_small())){
                    std::memcpy(data_,ptr,size_);
                }
            }else{
                capacity_ = capacity;
                data_ = (char *)std::realloc(data_,capacity_);
            }
        }
    }
    void resize(size_t size){
        reserve(size);
        size_ = size;
    }
    void append(Buffer const& other){
        reserve(size_ + other.size_);
        std::memcpy(data_ size_,other.data_,other.size_);
        size_ += other.size_;
    }
    void append(char c){
        reserve(size_ +1);
        data_[size_] = c;
        size_ += 1;
    }
    void append(char const* str){
        size_t len = std::strlen(str);
        append(str,len);
    }
    void append(char const* str,size_t size){
        reserve(size_ + size);
        std::memcpy(data_ + size_,str,size);
        size_ += size;
    }
    void append(std::string const& str){
        size_t len = str.size();
        reserve(size_ + len);
        std::memcpy(data_ + size_,str.data(),len);
        size_ += len;
    }
private:
    void dealloc(){
        if(is_large() && data_ != 0){
            std::free(data_);
            data_ = 0;
        }
    }
private:
    size_t capacity_;
    char small_[RESP_SMALL_BUFFER_SIZE];
    char* data_;
    size_t size_;
    
};
}
#endif
