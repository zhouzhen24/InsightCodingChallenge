/*
 * Tweet2.h
 *
 *  Created on: Nov 5, 2015
 *      Author: ZZ
 */

#ifndef SRC_TWEET2_H_
#define SRC_TWEET2_H_

#include<string>
#include<vector>

using namespace std;

struct Tweet2{

	long int timestamp_ms;
	vector<string> hashtags;
	void convertToPairs(vector<pair<string, string> > &pairs){
		for(size_t i = 0; i < hashtags.size(); i++)
			for(size_t j = i + 1; j < hashtags.size(); i++)
				pairs.push_back(make_pair(hashtags[i], hashtags[j]));
	}
};




#endif /* SRC_TWEET2_H_ */
