#pragma once
#include <Wt/WApplication>
#include <Wt/WStackedWidget>
#include "business/datamanager.h"
using namespace Wt;

class MyApplication : public WApplication
{
public:
	MyApplication(const WEnvironment& env):WApplication(env){}

	void handle(const std::string & str);
	void SetMainStack(WStackedWidget* _stack);

private:
	WStackedWidget* m_stack;
};
