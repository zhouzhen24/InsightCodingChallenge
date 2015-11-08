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

#include "parser.h"
#include "Tweet2.h"
#include "Hashtag.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace std;
using namespace rapidjson;

#define window_size 60//timestamp unit: ms

bool parser2(string js, Tweet2& tweet){
	tweet.hashtags.clear();

	Document d;
	d.Parse(js.c_str());

	//add timestamp_ms
	if(!d.IsObject() || !d.HasMember("created_at") || !d["created_at"].IsString() || !d.HasMember("entities")){
		printf("Cannot read this Tweet\n");
		return false;
	}

	string created_time = d["created_at"].GetString();
	tm *time_struct = new tm();
	if(strptime(created_time.c_str(), "%a %b %d %H:%M:%S +0000 %Y", time_struct))
		tweet.timestamp = timegm(time_struct);
	else{
		printf("Error: Not valid time!!!");
		return false;
	}

	Value& hts = d["entities"]["hashtags"];

    for (SizeType i = 0; i < hts.Size(); i++){
        string ht = hts[i]["text"].GetString();
        cleanUnicode(ht);
        cleanEscape(ht);
		tweet.hashtags.push_back(ht);
    }

	return true;
}




void maintainDataInWindow(time_t time, unordered_map<string, Hashtag*>& hashtags, list<Edge*>& edges){
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
	for(string s : hashtagsToDeleted){
		delete hashtags[s];
		hashtags.erase(s);
	}
}


#endif /* SRC_PARSER2_H_ */
