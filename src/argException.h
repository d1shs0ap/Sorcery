#ifndef ARG_EXCEPTION_H
#define ARG_EXCEPTION_H

#include <string>

struct ArgException{
    std::string message;
    ArgException(std::string message);
};

#endif
