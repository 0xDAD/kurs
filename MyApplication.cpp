#include "MyApplication.h"
#include <errno.h>

using namespace Wt;

WApplication *createApplication(const WEnvironment& env)
{
	MyApplication* app = new MyApplication(env);
	app->messageResourceBundle().use(app->appRoot() + "templ");
	app->useStyleSheet("style.css");
	app->internalPathChanged().connect(app, &MyApplication::handle);	
	app->createMainWidget();	
	return app;
}

void MyApplication::handle( const std::string & str )
{		
		int idx = atol(str.c_str() + 1);
		if(errno != EINVAL){
			m_wmain->makeTransition(idx, 0);
		}
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
}

int main(int argc, char **argv)
{
  GetDM().load(".");
  return WRun(argc, argv, &createApplication);
  GetDM().save(".");
}