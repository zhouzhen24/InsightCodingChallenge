/*
 * parser2.h
 *
 *  Created on: Nov 5, 2015
 *      Author: ZZ
 */

#ifndef SRC_PARSER2_H_
#define SRC_PARSER2_H_

#include <iostream>
#include <stdio.h>

#include "Tweet2.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace std;
using namespace rapidjson;

bool parser2(string js, Tweet2& tweet){
	tweet.hashtags.clear();

	Document d;
	d.Parse(js.c_str());

	assert(d.IsObject());

	//add timestamp_ms
	if(!d.IsObject() || !d.HasMember("timestamp_ms") || !d["timestamp_ms"].IsString() || !d.HasMember("entities")){
		printf("Cannot read this Tweet\n");
		return false;
	}
	assert(d["timestamp_ms"].IsString());
	string tmp = d["timestamp_ms"].GetString();
	//printf("timestamp_ms: %s\n", tmp.c_str());
	tweet.timestamp_ms = atol(tmp.c_str());

	Value& hts = d["entities"]["hashtags"];

	for (SizeType i = 0; i < hts.Size(); i++)
		tweet.hashtags.push_back(hts[i]["text"].GetString());

	return true;
}


#endif /* SRC_PARSER2_H_ */
