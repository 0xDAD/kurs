#pragma once
#include "MyApplication.h"
#include <Wt/WContainerWidget>
#include <Wt/WLink>
#include <Wt/WAnchor>

class WChoiseWidget : public Wt::WContainerWidget 
{
public:
	WChoiseWidget(){
		WLink _link1 (WLink::InternalPath, "/2");
		WAnchor* _anchor1 = new WAnchor(_link1, "Add ticket <br/>");	
		WLink _link2 (WLink::InternalPath, "/3");
		WAnchor* _anchor2 = new WAnchor(_link2, "Change ticket");	
		//WLink _link3 (WLink::InternalPath, "/100");
		//WAnchor* _anchor3 = new WAnchor(_link3, "*Generate");	
		this->addWidget(_anchor1);
		this->addWidget(_anchor2);
		//this->addWidget(_anchor3);
	}
};