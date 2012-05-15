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
#include "WSpecsPage.h"

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
		m_stack->addWidget(_choise);
		m_stack->addWidget(_specs);
		//FOOTER
		//m_next = new WPushButton("Next");
		temp->bindWidget("head-ph", image);
		temp->bindWidget("hist-ph", m_hist);
		temp->bindWidget("page-ph", m_stack);
		temp->bindWidget("foot-ph", new WContainerWidget());
	}
	void makeTransition(unsigned int page_id, int page_data )
	{
		if(!m_stack)
			return;
		if(page_id < m_stack->children().size()){
			WPageBase* _widget = static_cast<WPageBase*>(m_stack->children()[page_id]);
			if(_widget){
				_widget->setPageData(page_data);
				m_stack->setCurrentIndex(page_id);
			}
		}
	}
private:
	
	WStackedWidget* m_stack;
	//WPushButton* m_next;
	WText* m_hist;
};
