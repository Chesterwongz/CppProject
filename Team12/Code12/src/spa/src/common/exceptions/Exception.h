#pragma once

#include <exception>
#include <string>

class Exception : public std::exception {
private:
    std::string msg;
protected:
    explicit Exception(std::string msg);
public:
    [[nodiscard]] const char* what() const noexcept override;
};
