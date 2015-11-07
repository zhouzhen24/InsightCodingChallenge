/*
 * HashTag.h
 *
 *  Created on: Nov 6, 2015
 *      Author: ZZ
 */

#ifndef SRC_HASHTAG_H_
#define SRC_HASHTAG_H_


#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

struct Hashtag;

struct Edge{
	long int time;
	vector<Hashtag*> hashtags;
	~Edge();
	Edge(long int t, Hashtag* ht1, Hashtag* ht2);
	void updateTime(long int t){time = t;}
};


struct Hashtag{
	string text;
	long int time;
	unordered_set<Edge*> edges;
	~Hashtag();
	Hashtag(long int t, string message):time(t), text(message){}
	void updateTime(long int t){time = t;}
	void addEdge(Edge* e);
	void removeEdge(Edge* e);
	Hashtag* getPair(Edge* e);
	Edge* getEdge(Hashtag* otherHt);
};



#endif /* SRC_HASHTAG_H_ */
