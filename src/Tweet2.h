/*
 * Tweet2.h
 *
 *  Created on: Nov 5, 2015
 *      Author: ZZ
 */

#ifndef SRC_TWEET2_H_
#define SRC_TWEET2_H_

#include <algorithm>
#include <string>
#include <vector>
#include <time.h>

using namespace std;

struct Tweet2{

	time_t timestamp;
	vector<string> hashtags;
	void convertToPairs(vector<pair<string, string> > &pairs){
		for(size_t i = 0; i < hashtags.size(); i++)
			for(size_t j = i + 1; j < hashtags.size(); j++){
				//convert hashtag to lower case
				string ht1 = hashtags[i], ht2 = hashtags[j];
				transform(ht1.begin(), ht1.end(), ht1.begin(), ::tolower);
				transform(ht2.begin(), ht2.end(), ht2.begin(), ::tolower);
				if(ht1 != ht2)
					pairs.push_back(make_pair(ht1, ht2));
			}
	}
};

#endif /* SRC_TWEET2_H_ */
