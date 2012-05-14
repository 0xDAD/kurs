#pragma once
#include "doctor.h"
#include "patient.h"
#include "card.h"
#include "specialization.h"
#include <fstream>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/nvp.hpp>

using namespace std;
class datamanager
{
public:
	static datamanager& GetInstance(){
		return ginst;
	}	
	list<patient> LOP;
	list<doctor> LOD;
	list<card> m_loc;
	list<specialization> m_los;
	template <class Tlist>
	void _loadData(std::string file, std::string title, Tlist& list){
		using boost::serialization::make_nvp;
		ifstream ifs;
		ifs.open(file.c_str(), std::ios::in);
		if (ifs.good()){			
			boost::archive::xml_iarchive xmlp(ifs);
			xmlp >> make_nvp(title.c_str(), list);
		}
	}
	template <class Tlist>
	void _saveData(std::string file, std::string title, Tlist& list){
		using boost::serialization::make_nvp;
		ofstream ofs;
		ofs.open(file.c_str(), std::ios::out);
		if (ofs.good())
		{
			boost::archive::xml_oarchive xml(ofs);
			xml << make_nvp(title.c_str(), list);
		}
	}
	bool load(std::string  base_path){
		_loadData(base_path + "/patients.xml", "patients", LOP);
		_loadData(base_path + "/doctors.xml", "doctors", LOD);
		_loadData(base_path + "/cards.xml", "cards", m_loc);
		_loadData(base_path + "/specs.xml", "specs", m_los);
		return true;
	}

	bool save(std::string base_path){
		_saveData(base_path + "/patients.xml", "patients", LOP);
		_saveData(base_path + "/doctors.xml", "doctors", LOD);
		_saveData(base_path + "/cards.xml", "cards", m_loc);
		_saveData(base_path + "/specs.xml", "specs", m_los);
		return true;
	}
private:
	datamanager(){}
	static datamanager ginst;
	friend class boost::serialization::access;

	bool find_spec_doc (int spec_id, list<doctor>& spec_doc)
	{
		list<doctor>::iterator i;
		for(i = LOD.begin(); i!=LOD.end(); i++)
		{
			if(i->get_sid() == spec_id)
				spec_doc.push_back(*i);
		}
		if(spec_doc.size())
			return true;
		else
			return false;
	}
	bool find_doc_wt (int doc_id, list<card>& free_card)
	{
		list<card>::iterator i;
		for(i = m_loc.begin(); i!=m_loc.end(); i++)
			if(i->get_did() == doc_id && !i->get_pid())
				free_card.push_back(*i);

			if(free_card.size())
				return true;
			else
				return false;
		
	}
	void appointment (int card_id, int pat_id)
	{
		list<card>::iterator i;
		for(i = m_loc.begin(); i!=m_loc.end(); i++)
			if(i->get_cid() == card_id && !i->get_pid())
				i->set_pid(pat_id);
	}
};

datamanager datamanager::ginst;
datamanager& GetDM(){
	return datamanager::GetInstance();
}
