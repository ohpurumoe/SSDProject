#pragma once
#include <exception>
#include <string>

class StorageException :
    public std::exception
{
public:
    StorageException(const std::string& msg);
    const char* what() const noexcept override;

private:
    std::string message;
};

