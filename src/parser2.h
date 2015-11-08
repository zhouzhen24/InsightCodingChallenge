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


	assert(d.HasMember("created_at"));
	assert(d["created_at"].IsString());
	tweet.timestamp = d["created_at"].GetString();

	return true;
}




void maintainDataInWindow(long int time, unordered_map<string, Hashtag*>& hashtags, list<Edge*>& edges){
	//delete edges
	vector<string> hashtagsToDeleted;
	for(list<Edge*>::iterator it = edges.begin(); it != edges.end();){
		if((time - (*it)->time) > window_size){
			Hashtag* ht1 = (*it)->hashtags[0];
			Hashtag* ht2 = (*it)->hashtags[1];
			delete (*it);
			it = edges.erase(it);
			if(ht1->edges.empty())
				hashtagsToDeleted.push_back(ht1->text);
			if(ht2->edges.empty())
				hashtagsToDeleted.push_back(ht2->text);
		}
		else
			it++;
	}

	//delete hashtags
//	for(unordered_map<string, Hashtag*>::iterator it = hashtags.begin(); it != hashtags.end();){
//		if((time - it->second->time) > window_size){
//					delete (it->second);
//					it = hashtags.erase(it);
//		}
//		else
//			it++;
//	}

	for(string s : hashtagsToDeleted){
		delete hashtags[s];
		hashtags.erase(s);
	}

}


long long int dateToStamp(string& date){
//	split date to vector
//	grab year, month, day, hour, minute, second
//	convert to timestamp in second
	vector<string> tokens;
	string line;
	char delim = ' ';
	istringstream ss(date);
	while(getline(ss, line, delim)){
		tokens.push_back(line);
	}


//	tokens[0] : Thu
//	tokens[1] : Oct
//	tokens[2] : 29
//	tokens[3] : 17:51:01
//	tokens[4] : +0000
//	tokens[5] : 2015

	int year = atoi(tokens[5].c_str());
	int day = atoi(tokens[2].c_str());
	int hour = atoi(tokens[3].substr(0, 2).c_str());
	int minute = atoi(tokens[3].substr(3, 2).c_str());
	int second = atoi(tokens[3].substr(5, 2).c_str());



	return 0;
}



#endif /* SRC_PARSER2_H_ */
