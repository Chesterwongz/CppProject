#include "Exception.h"

#include <utility>

Exception::Exception(std::string msg) : msg(std::move(msg)) {}

const char *Exception::what() const noexcept {
    return msg.c_str();
}
