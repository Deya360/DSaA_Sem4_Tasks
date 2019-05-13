#ifndef TREEEXCEPTION_H
#define TREEEXCEPTION_H

#include <iostream>

class TreeException : public std::exception {

private:
    std::string msg;

public:
   TreeException(const std::string & message =""):exception(), msg(message) {}
   ~TreeException() noexcept {}

   virtual const char* what() const noexcept {
       return msg.c_str();
   }

};

#endif // TREEEXCEPTION_H


