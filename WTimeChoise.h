#pragma once
#include <Wt/WTemplate>
#include <boost/any.hpp>
#include "MyApplication.h"
#include "WPageBase.h"

using namespace Wt;
class WTimeWidget : public WPageBase
{
public: 

public:
	WTimeWidget(){
		WTemplate *templ = new WTemplate(tr("choose-date-templ"), this);		
		
		m_snextbase = "/6";
	}
	void update(){

	}
	void onSelChanged(){				
		//m_params["tdate"] = boost::any(boost::lexical_cast<string>(m_cal->selection().begin()->toString()));
	}
private:

	std::vector<int> m_ids;
};