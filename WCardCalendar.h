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
		return WCalendar::renderCell(widget, date);
	}
};