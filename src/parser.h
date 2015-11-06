/*
 * parser.h
 *
 *  Created on: Nov 5, 2015
 *      Author: ZZ
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include <fstream>
#include <assert.h>

#include "Tweet.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;

void parser(string js, Tweet& tweet, string name1, string name2){
	Document d;
	d.Parse(js.c_str());

	assert(d.IsObject());



	if(d.HasMember(name1.c_str())){
		assert(d[name1.c_str()].IsString());
		tweet.name1 = name1;
		tweet.value1 = d[name1.c_str()].GetString();
	}
	else
		tweet.value1.clear();

	if(d.HasMember(name2.c_str())){
		assert(d[name2.c_str()].IsString());

		tweet.name2 = name2;
		tweet.value2 = d[name2.c_str()].GetString();
	}
	else
		tweet.value2.clear();
}

bool isUnicode (char c) {
    return !(c>=0 && c <128);
}


bool cleanUnicode(string& s){
	size_t old_length = s.size();
	s.erase(remove_if(s.begin(),s.end(), isUnicode), s.end());
	bool hasUnicode = old_length != s.size();
	return hasUnicode;
}

void cleanEscape(string& s){
	if(s.empty() || s.size() <= 1)
		return;
	for(size_t i = 0; i < s.size(); i++){
		if(s[i] == '\n' || s[i] == '\t')
			s[i] = ' ';
	}
}






#endif /* PARSER_H_ */
