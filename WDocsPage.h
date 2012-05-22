#pragma once
#include <Wt/WSelectionBox>
#include <Wt/WTemplate>
#include <Wt/WStringListModel>
#include <boost/any.hpp>
#include "MyApplication.h"
#include "WPageBase.h"

using namespace Wt;
class WDocsWidget : public WPageBase
{
public: 
	void onComboChanged(int nItem){				
		int id = m_ids[nItem];
		m_params["did"] = boost::any(boost::lexical_cast<string>(id));
	}
public:
	WDocsWidget(){
		WTemplate *templ = new WTemplate(tr("choose-doc-templ"), this);
		m_box = new Wt::WSelectionBox();
		m_box->activated().connect(this, &WDocsWidget::onComboChanged);
		templ->bindWidget("sel-box", m_box);
		m_snextbase = "/4";
	}
	void update(){
		int idx = 0;
		int nsid = 0;

		if(m_params.find("sid") != m_params.end()){
			nsid = boost::lexical_cast<int>(boost::any_cast<string>(m_params["sid"]));
		}
		list<doctor> docs;
		WStringListModel* _model = new WStringListModel();
		GetDM().find_spec_doc(nsid, docs);
		for (list<doctor>::const_iterator it = docs.begin(); it != docs.end(); ++it){	
			_model->insertString(idx, it->name());
			m_ids.push_back(it->id());
			idx++;
		}
		m_box->setModel(_model);
		m_box->setVerticalSize(_model->rowCount());
		if(m_params.find("did")  != m_params.end())	{
			std::vector<int>::iterator it = m_ids.begin();
			idx = 0;			
			for(;it != m_ids.end(); ++it, idx++)
				if(*it == boost::any_cast<int>(m_params["did"])){
					m_box->setCurrentIndex(idx);
					break;
				}
		}
	}
private:
	WSelectionBox* m_box;
	std::vector<int> m_ids;
};