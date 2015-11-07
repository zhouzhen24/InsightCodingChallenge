/*
 * FeatureTwo.h
 *
 *  Created on: Nov 6, 2015
 *      Author: ZZ
 */

#ifndef SRC_FEATURETWO_H_
#define SRC_FEATURETWO_H_

#include "Hashtag.h"
#include "parser2.h"
#include "Tweet2.h"

#include <assert.h>
#include <unordered_map>

using namespace std;

bool featureTwo(string inputName, string outputName){
	inputName = "tweet_input/" + inputName;
	outputName = "tweet_output/" + outputName;
	string line;
	unordered_map<string, Hashtag*> allHashtags;
	vector<Edge*> allEdges;


	ifstream input_file(inputName.c_str());
//	if(!input_file){
//		printf("Warning! cannot read input file\n");
//	}
//	else
//		printf("Read input file\n");

	assert(input_file);

	ofstream output_file(outputName.c_str());
	assert(output_file);



	for(int line_no = 1; getline(input_file, line); line_no++){
		if(!(line_no >= 1 && line_no <= 50))
			break;
		printf("Line %5d\n", line_no);
		printf("line :%s\n", line.c_str());

		Tweet2 t;
		parser2(line, t);

	//		if(t.hashtags.empty())
	//			continue;
		//if only one hashtage
		if(!t.hashtags.empty() && t.hashtags.size() == 1){
			string message = t.hashtags.front();
			if(allHashtags.find(message) != allHashtags.end())
				allHashtags[message]->updateTime(t.timestamp_ms);
			else{
				Hashtag* ht = new Hashtag(t.timestamp_ms, message);
				allHashtags.insert(make_pair(message, ht));
			}
		}

		//if we have edges
		else if (!t.hashtags.empty()){
			vector<pair<string, string> > pairs;
			t.convertToPairs(pairs);
			for(pair<string, string> p : pairs)
				printf("#%s <-> #%s | ", p.first.c_str(), p.second.c_str());
			printf("\n");
			for(pair<string, string> p : pairs){
				unordered_map<string, Hashtag*>::iterator it1 = allHashtags.find(p.first), it2 = allHashtags.find(p.second);
				Hashtag *ht1, *ht2;
				if(it1 == allHashtags.end()){
					ht1 = new Hashtag(t.timestamp_ms, p.first);
					allHashtags.insert(make_pair(p.first, ht1));
				}
				else
					ht1 = it1->second;
				if(it2 == allHashtags.end()){
					ht2 = new Hashtag(t.timestamp_ms, p.second);
					allHashtags.insert(make_pair(p.second, ht2));
				}
				else
					ht2 = it2->second;

				//update time
				ht1->time = t.timestamp_ms;
				ht2->time = t.timestamp_ms;
				Edge* e = ht1->getEdge(ht2);
				if(e != NULL){
					e->updateTime(t.timestamp_ms);
					continue;
				}
				e = new Edge(t.timestamp_ms, ht1, ht2);
				allEdges.push_back(e);

			}

		}
		//printf("Line %d\n", line_no);
		printf("Hashtags: \n");
		for(unordered_map<string, Hashtag*>::iterator ht = allHashtags.begin(); ht != allHashtags.end(); ht++)
			printf("#%s ", ht->second->text.c_str());
		printf("\nEdges :\n");
		for(Edge* e : allEdges)
			printf("#%s <-> #%s\n", e->hashtags[0]->text.c_str(), e->hashtags[1]->text.c_str());

		//compute degree
//		double degree = (double)allHashtags.size() / (double)allEdges.size();
		printf("%u hashtags, %u edges\n", allHashtags.size(), allEdges.size());
		printf("\n");
	}
	for(Edge* e : allEdges)
		delete e;
	for(unordered_map<string, Hashtag*>::iterator ht = allHashtags.begin(); ht != allHashtags.end(); ht++)
		delete ht->second;
	input_file.close();
	output_file.close();


	return true;
}




#endif /* SRC_FEATURETWO_H_ */
