#ifndef DATA_STRUCTURE_EXCEPTION_HPP
#define DATA_STRUCTURE_EXCEPTION_HPP

#include <iostream>

namespace DataStructure {
    class Exception : public std::exception {
    protected:
        const char *error;
    public:
        Exception() noexcept = delete;
        explicit Exception(const char *error = "Exception!") noexcept : error(error) {}
        explicit Exception(const std::string &error = std::string("Exception!")) noexcept : error(error.c_str()) {}
        Exception(const Exception &) noexcept = default;
        Exception(Exception &&other) noexcept : error(other.error) {}
        Exception &operator=(const Exception &) noexcept = default;
        Exception &operator=(Exception &&other) noexcept {
            this->error = other.error;
            return *this;
        }
        ~Exception() override = default;
        const char *what() const noexcept override {
            return this->error;
        }
    };
    class RuntimeException : public Exception {
    public:
        RuntimeException() noexcept = delete;
        explicit RuntimeException(const char *error = "Runtime Exception!") noexcept : Exception(error) {}
        explicit RuntimeException(const std::string &error = std::string("Runtime Exception!")) noexcept
                : Exception(error) {}
        RuntimeException(const RuntimeException &) noexcept = default;
        RuntimeException(RuntimeException &&other) noexcept : Exception(other.error) {}
        RuntimeException &operator=(const RuntimeException &) noexcept = default;
        RuntimeException &operator=(RuntimeException &&other) noexcept {
            this->error = other.error;
            return *this;
        }
        ~RuntimeException() override = default;
    };
    class LogicException : public Exception {
    public:
        LogicException() noexcept = delete;
        explicit LogicException(const char *error = "Logic Exception!") noexcept : Exception(error) {}
        explicit LogicException(const std::string &error = std::string("Logic Exception!")) noexcept
                : Exception(error) {}
        LogicException(const LogicException &) noexcept = default;
        LogicException(LogicException &&other) noexcept : Exception(other.error) {}
        LogicException &operator=(const LogicException &) noexcept = default;
        LogicException &operator=(LogicException &&other) noexcept {
            this->error = other.error;
            return *this;
        }
        ~LogicException() override = default;
    };
}

#endif //DATA_STRUCTURE_EXCEPTION_HPP
