#include "MyApplication.h"
//#include <Wt\WTime>
//#include <Wt\WDateTime>
#include <errno.h>
#include "helper.h"



using namespace Wt;

WApplication *createApplication(const WEnvironment& env)
{	
	MyApplication* app = new MyApplication(env);
	app->setCssTheme("polished");
	app->messageResourceBundle().use(app->appRoot() + "templ");
	app->setTitle(WWidget::tr("title"));
	app->useStyleSheet("style.css");
	app->internalPathChanged().connect(app, &MyApplication::handle);	
	app->createMainWidget();
	
	return app;
}

void MyApplication::handle( const std::string & str )
{		
		int idx = atol(str.c_str() + 1);
		/*if(idx == 100){
			list<doctor>::const_iterator it = GetDM().doctors().begin();
			int cardid = 1;					
			WDateTime initdt = WDateTime::currentDateTime();
			initdt.setTime(WTime(8, 0));
			for(;it != GetDM().doctors().end(); ++it){								
				WDateTime dt;
				for (int day = 0; day < 31; day++)
				{
					dt = initdt.addDays(day);
					for(int cards = 0; cards < 20; cards++){						
						card cr(cardid++, 0, it->id(), dt.toPosixTime(), 15);
						GetDM().cards().push_back(cr);
						dt = dt.addSecs(15 * 60);
					}
					dt = dt.addSecs(30 * 60);
					for(int cards = 0; cards < 10; cards++){						
						card cr(cardid++, 0, it->id(), dt.toPosixTime(), 15);
						GetDM().cards().push_back(cr);
						dt = dt.addSecs(15 * 60);
					}
				}				
			}
			GetDM().save(".");
			return;
		}*/
		if(errno != EINVAL){
			map<string, boost::any> params;
			makeparams(str, params);
			m_wmain->makeTransition(idx, params);
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
 try{
  GetDM().load(".");
 }
 catch(WMyException& ex){
	 cout << "Unable to load environment. Reason: "<< ex.what();
 }
  return WRun(argc, argv, &createApplication);
}