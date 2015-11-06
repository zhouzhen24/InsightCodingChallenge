/*
 * HashTag.h
 *
 *  Created on: Nov 6, 2015
 *      Author: ZZ
 */

#ifndef SRC_HASHTAG_H_
#define SRC_HASHTAG_H_
#include "Edge.h"
#include <vector>
#include <unordered_set>
using namespace std;

struct Hashtag{
	string text;
	long int time;
	unordered_set<Edge*> edges;
	~Hashtag(){
		for(Edge* e : edges){
			e->~Edge();
		}
	}
	Hashtag(long int t, string message):time(t), text(message){text = "#" + text;}
	void addEdge(Edge* e);
	void removeEdge(Edge* e);
};

void Hashtag::addEdge(Edge* e){
	if(edges.find(e) == edges.end())
		edges.insert(e);
}

void Hashtag::removeEdge(Edge* e){
	if(edges.find(e) != edges.end())
		edges.erase(e);
}



#endif /* SRC_HASHTAG_H_ */
