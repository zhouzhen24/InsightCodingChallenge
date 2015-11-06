/*
 * Edge.h
 *
 *  Created on: Nov 6, 2015
 *      Author: ZZ
 */

#ifndef SRC_EDGE_H_
#define SRC_EDGE_H_
#include "Hashtag.h"

struct Edge{
	long int time;
	vector<Hashtag*> hashtags;
	~Edge(){
		for(Hashtag* ht : hashtags){
			ht->removeEdge(this);
			delete ht;
		}
	}
	Edge(long int t, Hashtag* ht1, Hashtag* ht2) : time(t){
		hashtags.push_back(ht1);
		hashtags.push_back(ht2);
	}
	void updateTime(long int t){time = t;}
};




#endif /* SRC_EDGE_H_ */
