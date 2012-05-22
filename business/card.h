#pragma once
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/nvp.hpp>

using namespace boost::posix_time;
class card{
	int m_card_id;
	int m_p_id;
	int m_d_id;
	boost::posix_time::ptime m_stime;
	int m_duration;
public:
	card(){};
	card(int id, int pid, int did,/*, boost::gregorian::date date, */ptime stime/*, boost::posix_time::ptime etime*/, int duration):m_card_id(id), m_p_id(pid), m_d_id(did)/*, m_date(date)*/, m_stime(stime),/* m_etime(etime)*/ m_duration(duration){}
	int id()const{return m_card_id;}
	int get_did()const{return m_d_id;}
	int get_pid()const{return m_p_id;}
	void set_pid(int pid){m_p_id = pid;}

	boost::posix_time::ptime get_dt() const{
		return m_stime;
	}

	private:
	friend class boost::serialization::access;
	template<class Archive>
	void save(Archive& ar, const unsigned int version) const 
    {
        using boost::serialization::make_nvp;
		ar << make_nvp("ID", m_card_id);
        ar << make_nvp("Patient", m_p_id);
        ar << make_nvp("Doctor", m_d_id);
		ar << make_nvp("StartTime", to_iso_string(m_stime));
		ar << make_nvp("Duration", m_duration);
    }
	template<class Archive>
	void load(Archive& ar, const unsigned int version)
    {
        using boost::serialization::make_nvp;
		ar >> make_nvp("ID", m_card_id);
        ar >> make_nvp("Patient", m_p_id);
        ar >> make_nvp("Doctor", m_d_id);
		std::string isotime;
		ar >> make_nvp("StartTime", isotime);
		m_stime = from_iso_string(isotime);
		ar >> make_nvp("Duration", m_duration);
    }
	template<class Archive>                                          
void serialize(                                                  
    Archive &ar,                                                
    const unsigned int file_version                             
){                                                              
    boost::serialization::split_member(ar, *this, file_version);
}    
};