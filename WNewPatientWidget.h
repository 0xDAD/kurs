#pragma once
#include <Wt/WTemplate>
#include <Wt/WComboBox>
#include <Wt/WDateTime>
#include <Wt/WTime>
#include <Wt/WDialog>
#include <Wt/WLineEdit>
#include <Wt/WLengthValidator>
#include <Wt/WIntValidator>
#include <Wt/WRegExpValidator>
#include <boost/any.hpp>
#include "MyApplication.h"
#include "WPageBase.h"
#include "Wt/WStringStream"

using namespace Wt;
class WNewPatientWidget : public WPageBase
{
public: 

public:
	WNewPatientWidget(){
		WTemplate *templ = new WTemplate(tr("new-patient-templ"), this);
		
		m_box = new Wt::WComboBox();
		m_box->insertItem(0, tr("male"));
		m_box->insertItem(0, tr("female"));
		templ->bindWidget("sex-sel", m_box);
		
			
		m_name = new WLineEdit();		
		WLengthValidator* val  = new WLengthValidator(10, 100, m_name);	
		m_name->setValidator(val);
		templ->bindWidget("name-edit", m_name);

		m_pass = new WLineEdit();		
		val  = new WLengthValidator(8, 10, m_pass);
		m_pass->setValidator(val);
		templ->bindWidget("pass-edit", m_pass);
		
		m_age = new WLineEdit();		
		WIntValidator* ival  = new WIntValidator(15, 120, m_age);	
		m_age->setValidator(ival);
		templ->bindWidget("age-edit", m_age);

		m_phone = new WLineEdit();		
		WRegExpValidator* reval  = new WRegExpValidator("([0-9\(\)\/\+ \-]*)", m_phone);
		m_phone->setValidator(reval);
		templ->bindWidget("phone-edit", m_phone);
		
		m_snextbase = "/2";
	}
	void update(){
		
	}
	bool onleave(){
		int pid =  boost::lexical_cast<int>(boost::any_cast<string>(m_params["pid"]));
		if(!pid){
			m_snextbase = "/0";
			return false;
		}
		
		try{
			validate();
			patient new_pat(pid, m_name->text().toUTF8(), 
				boost::lexical_cast<int>(m_age->text().toUTF8()),
				m_box->currentIndex(), m_phone->text().toUTF8(), m_pass->text().toUTF8());
			int cid = boost::lexical_cast<int>(boost::any_cast<string>(m_params["cid"]));
			GetDM().patients().push_back(new_pat);
			GetDM().appointment(cid, pid);	
			m_snextbase = "/2";
		}
		catch(WMyException& ex)
		{
			Wt::log("exception") << "Unable to make appointment because " << ex.what();			
			return false;
		}
		return true;
	}
	void validate(){
		if(m_name->validate() != WValidator::Valid)
			throw WMyException("incorrect name entered");
		if(m_age->validate() != WValidator::Valid)
			throw WMyException("incorrect age entered");
		if(m_pass->validate() != WValidator::Valid)
			throw WMyException("incorrect passport number");
		if(m_phone->validate() != WValidator::Valid)
			throw WMyException("incorrect phone entered");
	}
private:
	WComboBox* m_box;
	WLineEdit* m_name;
	WLineEdit* m_pass;
	WLineEdit* m_age;
	WLineEdit* m_phone;
};