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
#include <list>
#include <unordered_map>
#include <unordered_set>

#include "Tweet2.h"
#include "Hashtag.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace std;
using namespace rapidjson;

#define window_size 60*1000//timestamp unit: ms

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




void maintainDataInWindow(long int time, unordered_map<string, Hashtag*>& hashtags, list<Edge*>& edges){
	//delete edges
	for(list<Edge*>::iterator it = edges.begin(); it != edges.end();){
		if((time - (*it)->time) > window_size){
			delete (*it);
			it = edges.erase(it);
		}
		else
			it++;
	}

	//delete hashtags
	for(unordered_map<string, Hashtag*>::iterator it = hashtags.begin(); it != hashtags.end();){
		if((time - it->second->time) > window_size){
					delete (it->second);
					it = hashtags.erase(it);
		}
		else
			it++;
	}

}






#endif /* SRC_PARSER2_H_ */
