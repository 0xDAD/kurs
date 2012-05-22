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
		val->setMandatory(true);
		templ->bindWidget("name-edit", m_name);

		m_pass = new WLineEdit();		
		val  = new WLengthValidator(8, 10, m_pass);
		val->setMandatory(true);
		templ->bindWidget("pass-edit", m_pass);
		
		m_age = new WLineEdit();		
		WIntValidator* ival  = new WIntValidator(15, 120, m_age);	
		m_age->setValidator(ival);
		templ->bindWidget("age-edit", m_pass);

		m_phone = new WLineEdit();		
		WRegExpValidator* reval  = new WRegExpValidator("([0-9\(\)\/\+ \-]*)", m_phone);
		templ->bindWidget("phone-edit", m_phone);
		
		m_snextbase = "/7";
	}
	void update(){
		
	}
	
private:
	WComboBox* m_box;
	WLineEdit* m_name;
	WLineEdit* m_pass;
	WLineEdit* m_age;
	WLineEdit* m_phone;
};