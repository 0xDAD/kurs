#pragma once
#include "../WKursException.h"
#include "doctor.h"
#include "patient.h"
#include "card.h"
#include "specialization.h"
#include <fstream>

#include <boost/archive/xml_woarchive.hpp>
#include <boost/archive/xml_wiarchive.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/nvp.hpp>

using namespace std;
class datamanager
{
public:
	static datamanager& getInstance(){
		return m_sinstance;
	}	
	bool load(std::string  base_path){
		loadData(base_path + "/patients.xml", "patients", m_listPatients);
		loadData(base_path + "/doctors.xml", "doctors", m_listDoctors);
		loadData(base_path + "/cards.xml", "cards", m_listCards);
		loadData(base_path + "/specs.xml", "specs", m_listSpecs);
		return true;
	}
	bool save(std::string base_path){
		saveData(base_path + "/patients.xml", "patients", m_listPatients);
		saveData(base_path + "/doctors.xml", "doctors", m_listDoctors);
		saveData(base_path + "/cards.xml", "cards", m_listCards);
		saveData(base_path + "/specs.xml", "specs", m_listSpecs);
		return true;
	}
//	bool load(std::wstring  base_path){
//		loadData(base_path + L"/patients.xml",	"patients", m_listPatients);
//		loadData(base_path + L"/doctors.xml",	"doctors", m_listDoctors);
////		loadData(base_path + L"/cards.xml",		"cards", m_listCards);
////		loadData(base_path + L"/specs.xml",		"specs", m_listSpecs);
//		return true;
//	}
//	bool save(std::wstring base_path){
//		saveData(base_path + L"/patients.xml", "patients", m_listPatients);
//		saveData(base_path + L"/doctors.xml",  "doctors", m_listDoctors);
//		saveData(base_path + L"/cards.xml",	   "cards", m_listCards);
//		saveData(base_path + L"/specs.xml",	   "specs", m_listSpecs);
//		return true;
//	}
private:
	//template <class Tlist>
	//void loadData(std::wstring file, std::string title, Tlist& list){
	//	using boost::serialization::make_nvp;
	//	wifstream ifs;
	//	ifs.open(file.c_str(), std::ios::in);
	//	if (ifs.good()){			
	//		boost::archive::xml_wiarchive xmlp(ifs);

	//		xmlp >> make_nvp(title.c_str(), list);
	//	}
	//}
	//template <class Tlist>
	//void saveData(std::wstring file, std::string title, Tlist& list){
	//	using boost::serialization::make_nvp;
	//	wofstream ofs;
	//	ofs.open(file.c_str(), std::ios::out);
	//	if (ofs.good())
	//	{
	//		boost::archive::xml_woarchive xml(ofs);
	//		xml << make_nvp(title.c_str(), list);
	//	}
	//}
	template <class Tlist>
	void loadData(std::string file, std::string title, Tlist& list){
		using boost::serialization::make_nvp;
		ifstream ifs;
		ifs.open(file.c_str(), std::ios::in);
		if (ifs.good()){			
			boost::archive::xml_iarchive xmlp(ifs);
			
			xmlp >> make_nvp(title.c_str(), list);
		}
	}
	template <class Tlist>
	void saveData(std::string file, std::string title, Tlist& list){
		using boost::serialization::make_nvp;
		ofstream ofs;
		ofs.open(file.c_str(), std::ios::out);
		if (ofs.good())
		{
			boost::archive::xml_oarchive xml(ofs);
			xml << make_nvp(title.c_str(), list);
		}
	}
private:
	datamanager(){}
	static datamanager m_sinstance;
	friend class boost::serialization::access;

private:
	list<patient> m_listPatients;
	list<doctor> m_listDoctors;
	list<card> m_listCards;
	list<spec> m_listSpecs;

public:	
	bool find_spec_doc (int spec_id, list<doctor>& spec_doc)
	{
		list<doctor>::iterator i;
		for(i = m_listDoctors.begin(); i!=m_listDoctors.end(); i++)
		{
			if(!spec_id || i->sid() == spec_id)
				spec_doc.push_back(*i);
		}
		if(spec_doc.size())
			return true;
		else
			return false;
	}
	bool find_cards_for_doc_date(int doc_id, boost::posix_time::ptime stime, list<card>& cards ){
		list<card>::iterator i;
		for(i = m_listCards.begin(); i!=m_listCards.end(); i++){
			boost::gregorian::date dt = i->get_dt().date();
			string str = boost::gregorian::to_simple_string(dt);
			str = boost::gregorian::to_simple_string(stime.date());
			if(i->get_dt().date() == stime.date() && i->get_did() == doc_id && !i->get_pid())
				cards.push_back(*i);
		}

		if(cards.size())
			return true;
		else
			return false;
	}
	int get_free_patid(){
		int max = 0;
		for (list<patient>::const_iterator it = m_listPatients.begin(); m_listPatients.end()!=it; ++it){
			if(it->id() > max)
				max = it->id();
		}
		return max + 1;
	}
	int get_patient_id(string strid){
		for (list<patient>::const_iterator it = m_listPatients.begin(); m_listPatients.end() != it; ++it)
		{
			if(strid == it->pass())
			{
				return it->id();
			}
		}
		return 0;
	}
	bool get_patient_cards(int pid, vector<card>& pcards){
		if(!pid)
			return false;
		list<card>::iterator i;
		for(i = m_listCards.begin(); i!=m_listCards.end(); i++)
			if(i->get_pid() == pid)
				pcards.push_back(*i);
		if(pcards.size())
			return true;
		else
			return false;
	}
	bool find_doc_wt (int doc_id, list<card>& free_card)
	{
		list<card>::iterator i;
		for(i = m_listCards.begin(); i!=m_listCards.end(); i++)
			if(i->get_did() == doc_id && !i->get_pid())
				free_card.push_back(*i);

			if(free_card.size())
				return true;
			else
				return false;
		
	}
	void appointment (int card_id, int pat_id)
	{
		if(!card_id && !pat_id)
			throw new WMyException("Incorrect card or patient ID");
		list<card>::iterator i;
		for(i = m_listCards.begin(); i!=m_listCards.end(); i++)
			if(i->id() == card_id && !i->get_pid())
				i->set_pid(pat_id);
	}

	 list<patient>& patients() {
		return m_listPatients;
	}
	 list<doctor>& doctors() {
		return m_listDoctors;
	}
	list<card>& cards() {
		return m_listCards;
	}
	 list<spec>& specs() {
		return m_listSpecs;
	}
};

datamanager datamanager::m_sinstance;

datamanager& GetDM(){
	return datamanager::getInstance();
}
