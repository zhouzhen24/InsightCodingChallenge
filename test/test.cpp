/*
 * test.cpp
 *
 *  Created on: Nov 5, 2015
 *      Author: ZZ
 */

#include "gtest/gtest.h"
#include "parser.h"
#include "FeatureOne.h"
#include "parser2.h"
#include "Tweet2.h"
#include "Hashtag.h"
#include "FeatureTwo.h"

#include <stdio.h>
#include <unordered_map>

using namespace std;


int main(int argc, char** argv){
//	::testing::InitGoogleTest(&argc, argv);
//	return RUN_ALL_TESTS();
//	string inputName = "tweets.txt";
//	string outputName1 = "ft1.txt";
//	featureOne(inputName, outputName);
//	return 0;

		string inputName = "tweets.txt";
		string outputName1 = "ft1.txt";
		string outputName2 = "ft2.txt";
		if(!featureOne(inputName, outputName1))
			printf("Feature 1 failed\n");
		if(!featureTwo(inputName, outputName2))
			printf("Feature 2 failed\n");
		return 0;
}


