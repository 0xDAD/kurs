#pragma once
#include <Wt/WException>

using namespace Wt;

class  WMyException : public std::exception
{
public:
  explicit WMyException(const std::string& what):what_(what){

  }
  WMyException(const std::string& what, const std::exception& wrapped):what_(what + "\nCaused by exception: " + wrapped.what()){
  } 
 

  virtual ~WMyException() throw(){}
  virtual const char *what() const throw(){
	  return what_.c_str();
  }

  void setMessage(const std::string& msg){
	  what_= msg;
  }

private:
  std::string what_;
};
 