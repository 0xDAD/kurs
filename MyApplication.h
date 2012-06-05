#pragma once
#include <Wt/WApplication>
#include "WKursException.h"
#include "business/datamanager.h"
#include "WMainPage.h"

using namespace Wt;
class MyApplication : public WApplication
{
public:
	MyApplication(const WEnvironment& env):WApplication(env), m_wmain(NULL){
	
	}
	void createMainWidget(){
		if(!m_wmain)
			m_wmain = new WMainPage(this->root());
	}
	void handle(const std::string & str);
private:	
	WMainPage* m_wmain;
};
