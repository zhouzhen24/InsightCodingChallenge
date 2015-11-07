/*
 * Hashtag.cpp
 *
 *  Created on: Nov 6, 2015
 *      Author: ZZ
 */

#include "Hashtag.h"


Hashtag::~Hashtag(){
	for(Edge* e : edges){
		e->~Edge();
	}
}


void Hashtag::addEdge(Edge* e){
	if(edges.find(e) == edges.end())
		edges.insert(e);
}

void Hashtag::removeEdge(Edge* e){
	if(edges.find(e) != edges.end())
		edges.erase(e);
}

Hashtag* Hashtag::getPair(Edge* e){
	for(Hashtag* hs : e->hashtags){
		if(hs != this)
			return hs;
	}
	printf("getPair Warning: Edge has error between %s and %s in %s\n",
			e->hashtags[0]->text.c_str(),
			e->hashtags[0]->text.c_str(),
			text.c_str());
	return NULL;
}

Edge* Hashtag::getEdge(Hashtag* otherHt){
	for(Edge* e : edges){
		if(getPair(e)->text == otherHt->text)
			return e;
	}
	return NULL;
}

Edge::~Edge(){
	for(Hashtag* ht : hashtags){
		ht->removeEdge(this);
		delete ht;
	}
}

Edge::Edge(long int t, Hashtag* ht1, Hashtag* ht2) : time(t){
	hashtags.push_back(ht1);
	hashtags.push_back(ht2);
	ht1->addEdge(this);
	ht2->addEdge(this);
}

