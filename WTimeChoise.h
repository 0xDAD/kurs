#pragma once
#include <Wt/WTemplate>
#include <Wt/WSelectionBox>
#include <Wt/WDateTime>
#include <Wt/WTime>
#include <Wt/WDialog>
#include <boost/any.hpp>
#include "MyApplication.h"
#include "WPageBase.h"
#include "Wt/WStringStream"

using namespace Wt;
class WTimeWidget : public WPageBase
{
public: 

public:
	WTimeWidget(){
		WTemplate *templ = new WTemplate(tr("choose-time-templ"), this);
		m_box = new Wt::WSelectionBox();
		m_box->activated().connect(this, &WTimeWidget::onComboChanged);
		templ->bindWidget("sel-box", m_box);
		m_snextbase = "/2";
	}
	void update(){
		WDateTime tdate;
		int nDoc = 0;		
		if(m_params.find("tdate") != m_params.end() && m_params.find("did") != m_params.end()){
			 tdate.setDate(WDate::fromString(boost::any_cast<string>(m_params["tdate"])));
			 nDoc = boost::lexical_cast<int>(boost::any_cast<string>(m_params["did"]));
		}
		WStringListModel* _model = new WStringListModel();
		list<card> cards;
		int idx = 0;
		m_ids.clear();
		GetDM().find_cards_for_doc_date(nDoc, tdate.toPosixTime(), cards); 
		for (list<card>::const_iterator it = cards.begin(); it != cards.end(); ++it){	
			WDateTime dt = WDateTime::fromPosixTime(it->get_dt());						
			_model->insertString(idx, dt.time().toString("hh:mm"));
			m_ids.push_back(it->id());
			idx++;
		}
		m_box->setModel(_model);
		m_box->setCurrentIndex(0);
		m_box->setVerticalSize(_model->rowCount());

	}
	void onComboChanged(int nItem){				
		m_params["cid"] = boost::any(boost::lexical_cast<string>(m_ids[nItem]));
	}
	void onleave(){
		onComboChanged(m_box->currentIndex());
		Wt::WDialog dialog(tr("dlgheader1"));
		new Wt::WText(tr("dlgpromt1"), dialog.contents());
		Wt::WLineEdit edit(dialog.contents());
		new Wt::WBreak(dialog.contents());

		Wt::WPushButton ok("Ok", dialog.contents());		
		edit.enterPressed().connect(&dialog, &Wt::WDialog::accept);
		ok.clicked().connect(&dialog, &Wt::WDialog::accept);
		if (dialog.exec() == Wt::WDialog::Accepted){			
			int pid = 0;
			pid = GetDM().get_patient_id(edit.text().toUTF8());
			if(!pid){				
				pid = GetDM().get_free_patid();
				m_snextbase = "/6";
			}else
			{
				m_snextbase = "/2";
				int cid = boost::lexical_cast<int>(boost::any_cast<string>(m_params["cid"]));
				try{
				GetDM().appointment(cid, pid);
				}
				catch(WMyException& ex){
					Wt::log("exception")<<ex.what();
				}
			}
			m_params["pid"] = boost::any(boost::lexical_cast<string>(pid));
		}
	}

private:
	WSelectionBox* m_box;
	std::vector<int> m_ids;
};