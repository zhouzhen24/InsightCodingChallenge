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

	char* outputPath = "tweet_output/ft1.txt";
	ofstream output_file(outputPath);
	ASSERT_TRUE(output_file);

	while(getline(input_file, line)){
		parser(line, t, "text", "created_at");
		printf("writing <%s (timestamp: %s)>...", t.value1.c_str(), t.value2.c_str());
		output_file << t.value1.c_str() << " (timestamp: " << t.value2.c_str() << ")\n";
		printf("Done\n");
	}

	input_file.close();
	output_file.close();
}








int main(int argc, char** argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}


