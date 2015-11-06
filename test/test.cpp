/*
 * test.cpp
 *
 *  Created on: Nov 5, 2015
 *      Author: ZZ
 */

#include "gtest/gtest.h"
#include "parser.h"
#include <stdio.h>

TEST(TweetParser, parser){
	Tweet t;
	string line;
	char* inputPath = "tweet_input/tweets.txt";
	ifstream input_file(inputPath);
	ASSERT_TRUE(input_file);

	while(getline(input_file, line)){
		parser(line, t, "text", "created_at");
		printf("%s (timestamp: %s)\n", t.value1.c_str(), t.value2.c_str());
	}

	input_file.close();

}








int main(int argc, char** argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}


