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
		m_params["sid"] = boost::any(boost::lexical_cast<string>(id));
	}
public:
	WSpecsWidget(){
		WTemplate *templ = new WTemplate(tr("choose-spec-templ"), this);
		m_box = new Wt::WSelectionBox();
		m_box->activated().connect(this, &WSpecsWidget::onComboChanged);
		templ->bindWidget("sel-box", m_box);
		m_snextbase = "/3";
	}
	void update(){
		int idx = 0;
		WStringListModel* _model = new WStringListModel();
		for (list<spec>::const_iterator it = GetDM().specs().begin(); it != GetDM().specs().end(); ++it){			
//			m_box->insertItem(idx, it->title());
			_model->addString(it->title());
			m_ids.push_back(it->id());
			idx++;
		}
		m_box->setModel(_model);
		if(m_params.size() && m_params.find("sid")  != m_params.end()){
			std::vector<int>::iterator it = m_ids.begin();
			idx = 0;
			for(;it != m_ids.end(); ++it, idx++)
				if(*it == boost::any_cast<int>(m_params["sid"])){
					m_box->setCurrentIndex(idx);
					break;
				}
		}
	}
private:
	WSelectionBox* m_box;
	std::vector<int> m_ids;
};