#pragma once
#include "MyApplication.h"
#include <Wt/WContainerWidget>
#include "helper.h"
using namespace std;
class WPageBase : public Wt::WContainerWidget 
{
public:
	WPageBase(){
	}

	void setPageParams(map<string, boost::any>& params){
		m_params = params;
		update();
	}

	virtual string getNextLink(){
		return makeparurl(m_params, m_snextbase);
	}
	virtual string getNextBase(){
		return m_snextbase;
	}
	virtual void update(){}
	protected:
	map<string, boost::any> m_params;
	string m_snextbase;
};