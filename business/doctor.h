#pragma once
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/nvp.hpp>

class doctor
{
protected: 
	doctor(){}
public:
	doctor(int id, std::string& FIO, std::string& phone, int sid):d_id(id), d_FIO(FIO), d_phone(phone), m_spec_id(sid){}
	int get_sid()
	{return m_spec_id;}
private:
	int d_id;
	std::string d_FIO;
	std::string d_phone;
	int m_spec_id;

	friend class boost::serialization::access;

	template<class archive>
	void serialize(archive& ar, const unsigned int version)
    {
        using boost::serialization::make_nvp;
		ar & make_nvp("id", d_id);
        ar & make_nvp("name", d_FIO);
		ar & make_nvp("phone", d_phone);
		ar & make_nvp("spec", m_spec_id);
    }
};
