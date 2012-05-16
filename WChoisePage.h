#pragma once
#include <Wt/WLink>
#include <Wt/WAnchor>
#include "WPageBase.h"
using namespace Wt;

class WChoiseWidget : public WPageBase
{
public:
	WChoiseWidget(){
		WTemplate *templ = new WTemplate(tr("choise-templ"), this);
		WLink _link1 (WLink::InternalPath, "/1");
		WAnchor* _anchor1 = new WAnchor(_link1, tr("link1"));	
		WLink _link2 (WLink::InternalPath, "/2");
		WAnchor* _anchor2 = new WAnchor(_link2, tr("link2"));			
		templ->bindWidget("link1-ph", _anchor1);
		templ->bindWidget("link2-ph", _anchor2);
		/*this->addWidget(_anchor1);
		this->addWidget(_anchor2);*/
	}
};