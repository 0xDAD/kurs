#include "MyApplication.h"
#include "WChoisePage.h"

#include <Wt/WImage>


WApplication *createApplication(const WEnvironment& env)
{
	MyApplication* app = new MyApplication(env);
	
	WImage* image = new WImage("./header.jpg");

	app->root()->addWidget(image);
	WStackedWidget* _stack = new WStackedWidget();
	WChoiseWidget* _choise = new WChoiseWidget();
	_stack->addWidget(_choise);
	app->root()->addWidget(_stack);
	app->SetMainStack(_stack);
	app->internalPathChanged().connect(app, &MyApplication::handle);
	return app;
}

int main(int argc, char **argv)
{
  GetDM().load(".");
  return WRun(argc, argv, &createApplication);
  GetDM().save(".");
}


void MyApplication::handle( const std::string & str )
{
	if(m_stack){
		int idx;
		m_stack->setCurrentIndex(idx);
	}
}

void MyApplication::SetMainStack( WStackedWidget* _stack )
{
	m_stack = _stack;
}