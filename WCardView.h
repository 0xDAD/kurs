#pragma once
#include <Wt/WTemplate>
#include <Wt/WSelectionBox>
#include <Wt/WDateTime>
#include <Wt/WTime>
#include <Wt/WTableView>
#include <Wt/WStandardItemModel>

#include <boost/any.hpp>
#include "MyApplication.h"
#include "WPageBase.h"
#include "Wt/WStringStream"

using namespace Wt;
class WCardView : public WPageBase
{
public: 

public:
	WCardView(){
		WTemplate *templ = new WTemplate(tr("card-templ"), this);		
		m_table = new Wt::WTableView();
		templ->bindWidget("cards-lv", m_table);
		m_snextbase = "/0";
	}
	void update(){	
		int pid = 0;
		if(m_params.find("pid") != m_params.end()){			
			pid = boost::lexical_cast<int>(boost::any_cast<string>(m_params["pid"]));
		}
		if(!pid)
			return;
		vector<card> cards;
		GetDM().get_patient_cards(pid, cards);
		WStandardItemModel* _model = new WStandardItemModel();
		for (int i = 0; i < cards.size(); i++)
		{
			WStandardItem* _item1 = new WStandardItem(boost::lexical_cast<string>(cards[i].id()));
			//добавить имя врача, время и день приема
			//WStandardItem* _item2= new WStandardItem(boost::lexical_cast<string>(cards[i].()));
			 //	WStandardItem* _item3 = new WStandardItem(boost::lexical_cast<string>(cards[i].id()));
			//WStandardItem* _item4 = new WStandardItem(boost::lexical_cast<string>(cards[i].id()));
			_model->appendRow(_item1);			
		}
		
		m_table->setModel(_model);
		m_table->resize(200, 300);
	}
	void onleave(){
		GetDM().save(".");
		m_params.clear();
	}

private:
	WTableView* m_table;
	
};