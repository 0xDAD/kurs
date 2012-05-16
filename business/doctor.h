#pragma once
#include <boost/serialization/list.hpp>
#include <boost/serialization/nvp.hpp>

class doctor
{
protected: 
public:
	doctor(int id, std::string& FIO, std::string& phone, int sid):d_id(id), d_FIO(FIO), d_phone(phone), m_spec_id(sid){}
	doctor(){}

	int sid()const
	{return m_spec_id;}
	int id ()const
	{
		return d_id;
	}
	std::string name() const{
		return d_FIO;
		return "";
	}
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
