#pragma once
#include <boost/serialization/list.hpp>
#include <boost/serialization/nvp.hpp>
using namespace Wt;
class patient
{
protected: 
	patient(){}
public:
	patient(int id, std::string name, int age, int sex, std::string phone, std::string pass):m_id(id), m_name(name), m_age(age),m_sex(sex), m_phone(phone), m_pass(pass){
	}
	enum sex{
		Male,
		Female
	};

private:
	int m_id;
	std::string m_pass;
	std::string m_name;
	int m_age;
	int m_sex;
	std::string m_phone;
public:
	int id() const	{
		return m_id;
	}
	std::string pass() const{
		return m_pass;
	}
private:
	friend class boost::serialization::access;
	template<class archive>
	void serialize(archive& ar, const unsigned int version)
    {
        using boost::serialization::make_nvp;
		ar & make_nvp("ID", m_id);
		ar & make_nvp("Pass", m_pass);
        ar & make_nvp("Name", m_name);
        ar & make_nvp("Age", m_age);
		ar & make_nvp("Sex", m_sex);
		ar & make_nvp("Phone", m_phone);
    }
};
