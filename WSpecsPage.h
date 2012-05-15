#pragma once
#include <Wt/WSelectionBox>
#include <Wt/WTemplate>
#include <Wt/WStandardItemModel>
#include <Wt/WStandardItem>
#include <boost/any.hpp>
#include "MyApplication.h"
#include "WPageBase.h"

using namespace Wt;
class WSpecsWidget : public WPageBase
{
public: 
	void onComboChanged(int nItem){				
		int id = m_ids[nItem];
	}
public:
	WSpecsWidget(){
		WTemplate *templ = new WTemplate(tr("choose-spec-templ"), this);
		m_box = new Wt::WSelectionBox();
		int idx = 0;
		for (list<spec>::const_iterator it = GetDM().specs().begin(); it != GetDM().specs().end(); ++it){			
			m_box->insertItem(idx, it->title());
			m_ids.push_back(it->id());
			idx++;
		
		}
		if(m_pageData)
		{
			std::vector<int>::iterator it = m_ids.end();
			idx = 0;
			for(;it != m_ids.end(); ++it, idx++)
			if(*it == m_pageData){
				m_box->setCurrentIndex(idx);
				break;
			}
		}
		m_box->activated().connect(this, &WSpecsWidget::onComboChanged);
		templ->bindWidget("sel-box", m_box);
	}
	Signal<int>& completed(){return _completed;}
private:
	Signal<int> _completed;
	WSelectionBox* m_box;
	std::vector<int> m_ids;
};