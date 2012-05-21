#pragma once
#include <Wt/WTemplate>
#include <boost/any.hpp>
#include "WCardCalendar.h"
#include "MyApplication.h"
#include "WPageBase.h"

using namespace Wt;
class WDateWidget : public WPageBase
{
public: 

public:
	WDateWidget(){
		WTemplate *templ = new WTemplate(tr("choose-date-templ"), this);
		m_cal = new WCardCalendar();		
		templ->bindWidget("cal-ph", m_cal);
		m_cal->selectionChanged().connect(this, &WDateWidget::onSelChanged);
		m_snextbase = "/5";
	}
	void update(){
		
	}
	void onSelChanged(){				
		m_params["tdate"] = boost::any(boost::lexical_cast<string>(m_cal->selection().begin()->toString()));
	}
private:
	WCardCalendar* m_cal;
	std::vector<int> m_ids;
};