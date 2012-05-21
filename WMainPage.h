#pragma once
#include <Wt/WContainerWidget>
#include <Wt/WStackedWidget>
#include <Wt/WRectArea>
#include <Wt/WImage>
#include <Wt/WTemplate>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WString>
#include <Wt/WText>
#include "MyApplication.h"
#include "WChoisePage.h"
#include "WDocsPage.h"
#include "WSpecsPage.h"
#include "WDateWidget.h"
#include "WTimeChoise.h"
using namespace std;
class WMainPage : public Wt::WContainerWidget 
{
public:
	WMainPage(WContainerWidget* root){
		
		WTemplate *temp = new WTemplate(tr("main-templ"), root);	
		//HEADER
		WImage* image = new WImage("./header.jpg");	
		WLink _link (WLink::InternalPath, "/0");
		WRectArea* area = new WRectArea(0, 0, 100, 100);
		area->setToolTip("Home");
		area->setLink(_link);
		image->addArea(area);	
		//HIST
		m_hist = new WText();
		m_hist->setText("Select option");
		//BODY
		m_stack = new WStackedWidget();
		WSpecsWidget* _specs = new WSpecsWidget();
		WChoiseWidget* _choise = new WChoiseWidget();
		WDocsWidget* _docs = new WDocsWidget();
		WContainerWidget* _wempt = new WContainerWidget();
		WDateWidget* _wdate = new WDateWidget();
		WTimeWidget* _wtime = new WTimeWidget();
		m_stack->addWidget(_choise);
		m_stack->addWidget(_specs);
		m_stack->addWidget(_wempt); //CARDS WIDGET
		m_stack->addWidget(_docs);
		m_stack->addWidget(_wdate);
		m_stack->addWidget(_wtime);
		//FOOTER
		WContainerWidget* footer = new WContainerWidget();
		m_next = new WPushButton("Next", footer);
		m_next->clicked().connect(this, &WMainPage::nextClicked);
		m_next->disable();
		temp->bindWidget("head-ph", image);
		temp->bindWidget("hist-ph", m_hist);
		temp->bindWidget("page-ph", m_stack);
		temp->bindWidget("foot-ph", footer);
	}
	void makeTransition(unsigned int page_id, map<string, boost::any>& params)
	{
		if(!m_stack)
			return;
		if(page_id < m_stack->children().size()){
			WPageBase* _widget = static_cast<WPageBase*>(m_stack->children()[page_id]);
			if(_widget){
				_widget->setPageParams(params);
				m_stack->setCurrentIndex(page_id);
				updatePage();
			}
		}
	}
	void nextClicked(const WMouseEvent& evt){
		WPageBase* _widget = static_cast<WPageBase*>(m_stack->currentWidget());
		if (_widget && !_widget->getNextLink().empty()){			
			WApplication::instance()->setInternalPath(_widget->getNextLink(), true);			
		}
	}
	void updatePage() 
	{
		WPageBase* _widget = static_cast<WPageBase*>(m_stack->currentWidget());
		if (_widget && !_widget->getNextLink().empty()){			
			m_next->enable();
		}else
			m_next->disable();
	}

private:	
	WStackedWidget* m_stack;	
	WText* m_hist;
	WPushButton* m_next;
};
