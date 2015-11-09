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

	string line;
	unordered_map<string, Hashtag*> allHashtags;
	list<Edge*> allEdges;

	ofstream error_file("error_log/f2_error_" + inputName);
	assert(error_file);

	inputName = "tweet_input/" + inputName;
	outputName = "tweet_output/" + outputName;
	ifstream input_file(inputName.c_str());
	if(!input_file){
		printf("Warning! cannot read input file : %s\n", inputName.c_str());
		return false;
	}
	
	ofstream output_file(outputName.c_str());
	assert(output_file);
	output_file.precision(2);
	output_file << fixed;



	for(int line_no = 1; getline(input_file, line); line_no++){
//		printf("Line %5d\n", line_no);
//		printf("line :%s\n", line.c_str());
		Tweet2 t;
		if(!parser2(line, t)){
			printf("line %d: Feature 2 parser fail!\n", line_no);
			printf("JSON: %s\n", line.c_str());
			error_file << line_no << " " << line << endl;
			continue;
		}
		//if we have edges
		if(t.hashtags.size() > 1) {
			vector<pair<string, string> > pairs;
			t.convertToPairs(pairs);
			for(pair<string, string> p : pairs){
				unordered_map<string, Hashtag*>::iterator it1 = allHashtags.find(p.first), it2 = allHashtags.find(p.second);
				Hashtag *ht1, *ht2;
				if(it1 == allHashtags.end()){
					ht1 = new Hashtag(t.timestamp, p.first);
					allHashtags.insert(make_pair(p.first, ht1));
				}
				else
					ht1 = it1->second;
				if(it2 == allHashtags.end()){
					ht2 = new Hashtag(t.timestamp, p.second);
					allHashtags.insert(make_pair(p.second, ht2));
				}
				else
					ht2 = it2->second;

				//update time
				ht1->time = t.timestamp;
				ht2->time = t.timestamp;
				Edge* e = ht1->getEdge(ht2);
				if(e != NULL){
					e->updateTime(t.timestamp);
					continue;
				}
				e = new Edge(t.timestamp, ht1, ht2);
				allEdges.push_back(e);

			}

		}


		maintainDataInWindow(t.timestamp, allHashtags, allEdges);
		//compute degree
		float degree =  0;
		if(!allEdges.empty())
			degree = (float)allHashtags.size() / (float)allEdges.size() / 2.0;
        //round to hundredth
        degree = float(int(degree * 100 + 0.5)) / 100;
		printf("%lu hashtags, %lu edges\nAverage degree : %.2f\n", allHashtags.size(), allEdges.size(), degree);
		output_file << degree << endl;
	}
	for(Edge* e : allEdges)
		delete e;
	for(unordered_map<string, Hashtag*>::iterator ht = allHashtags.begin(); ht != allHashtags.end(); ht++)
		delete ht->second;
	input_file.close();
	output_file.close();
	printf("End of Feature 2\n");

	return true;
}




#endif /* SRC_FEATURETWO_H_ */
