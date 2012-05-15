#pragma once
#include "MyApplication.h"
#include <Wt/WContainerWidget>

class WPageBase : public Wt::WContainerWidget 
{
public:
	WPageBase():m_pageData(0){
	}
	int getPageData(){
		return m_pageData;
	}
	void setPageData(int nData){
		m_pageData = nData;
	}
	//virtual void nextPage() = 0;
//	virtual void prevPage() = 0;
	protected:
	int m_pageData;
};