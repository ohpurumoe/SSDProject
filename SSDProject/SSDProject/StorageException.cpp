#include "StorageException.h"

// 생성자 구현
StorageException::StorageException(const std::string& msg) : message(msg) {}

// what() 메서드 구현
const char* StorageException::what() const noexcept {
    return message.c_str();
}