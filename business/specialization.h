#pragma once
using namespace std;

class specialization{
	string m_title;
	int m_spec_id;
public:
	specialization(){}
	specialization(string& title, int id):m_title(title),m_spec_id(id){}

private:

	friend class boost::serialization::access;
	template<class archive>
	void serialize(archive& ar, const unsigned int version)
    {
        using boost::serialization::make_nvp;
		ar & make_nvp("Title", m_title);
        ar & make_nvp("SpecID", m_spec_id);
	}
};