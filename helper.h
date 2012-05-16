#pragma once
#include <boost/any.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <algorithm>
#include <map>
using namespace boost::algorithm;

int makeparams(std::string surl, map<string, boost::any>& params){
	if(!surl.size())
		return 0;

	std::string::iterator fi = std::find(surl.begin(), surl.end(), '?');
	if(fi == surl.end())
		return 0;
	fi++;
	int cnt = 0;
	boost::regex re("&");
	boost::sregex_token_iterator i(fi, surl.end(), re, -1);
	boost::sregex_token_iterator j;
	
	while(i != j){
		boost::regex re1("\\s*=\\s*");
		string s1 (*i++);
		boost::sregex_token_iterator i1(s1.begin(),s1.end(), re1, -1);
		string key;		
		if(i1 != j){
			key = *i1++;
			if(i1 != j){				
				params.insert(make_pair(key, boost::any(string(*i1))));
				cnt++;
			}
		}		
	}	
	
	return cnt;
}
string makeparurl(map<string, boost::any>& params, std::string& baseurl){
	string surl = baseurl;
	if(!params.size())
		return surl;
	surl += "?";
	map<string, boost::any>::iterator it = params.begin();
	for (;it != params.end(); ){
		surl += it->first;
		surl += "=";
		surl += boost::any_cast<string>(it->second);
		++it;
		if(it != params.end())
			surl += "&";
	}
	return surl;
}