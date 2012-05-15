#include "MyApplication.h"
#include "WChoisePage.h"
#include "WSpecsPage.h"
#include <Wt/WRectArea>
#include <Wt/WImage>
#include <errno.h>


WApplication *createApplication(const WEnvironment& env)
{
	MyApplication* app = new MyApplication(env);
	
	WImage* image = new WImage("./header.jpg");
	WLink _link (WLink::InternalPath, "/0");
	WRectArea* area = new WRectArea(0, 0, 100, 100);
	area->setToolTip("Home");
	area->setLink(_link);
	image->addArea(area);

	app->root()->addWidget(image);
	
	WStackedWidget* _stack = new WStackedWidget();
	WSpecsWidget* _specs = new WSpecsWidget();
	WChoiseWidget* _choise = new WChoiseWidget();


	_stack->addWidget(_choise);
	_stack->addWidget(_specs);

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
		int idx = atol(str.c_str() + 1);
		if(errno != EINVAL){
			//if(idx == 100){
			//	specialization spec(std::string("lor"), 1);
			//	GetDM().m_listSpecs.push_back(spec);
			//	for (int i = 0; i < 50; i++){			
			//		doctor doc(i + 1, std::string("Ivanov Ivan Ivanovi4"), std::string("802974362482"), 1);
			//		GetDM().m_listDoctors.push_back(doc);
			//		//	patient(int id, std::string& name, int age, int sex, std::string& phone):m_id(id), m_name(name), m_age(age),m_sex(sex), m_phone(phone){
			//		patient pat(i + 1, std::string("Petrov Petr Petrovi4"), 100, 0, std::string("8029746436"));
			//		GetDM().m_listPatients.push_back(pat);
			//		
			//	}				
			//	GetDM().save(".");
			//	return;
			//}
			m_stack->setCurrentIndex(idx);
		}
	}
}

void MyApplication::SetMainStack( WStackedWidget* _stack )
{
	m_stack = _stack;
}