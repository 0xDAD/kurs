#pragma once
#include "MyApplication.h"
#include <Wt/WException>
#include <Wt/WDialog>
#include <Wt/WText>
#include <Wt/WPushButton>
#include <Wt/WBreak>

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

	  Wt::WDialog dialog("Exception");
	  new Wt::WText(what_, dialog.contents());
	  new Wt::WBreak(dialog.contents());
	  Wt::WPushButton ok("Ok", dialog.contents());			  
	  ok.clicked().connect(&dialog, &Wt::WDialog::accept);
	  dialog.exec();

	  return what_.c_str();
  }

  void setMessage(const std::string& msg){
	  what_= msg;
  }

private:
  std::string what_;
};
 