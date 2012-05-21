#pragma once
#include <Wt/WCalendar>
using namespace Wt;
class WCardCalendar: public WCalendar
{
public:
	WCardCalendar(){

	}
protected:
	WWidget * renderCell( 	WWidget *  	widget,	const WDate &  	date ) {
		WWidget* _widget = WCalendar::renderCell(widget, date);	
		WDate cur = WDate::currentDate();		
		bool bInActive = date < cur || cur.daysTo(date) > 30;
		_widget->setDisabled(bInActive);
		std::string style;
		if(date.month() == currentMonth())
			style += (bInActive? "forbid" : "avail");
		else
			style += "nicm";
		if(isSelected(date))
			style += " Wt-cal-sel";
		
		_widget->setStyleClass(style);
		return _widget;
	}
};