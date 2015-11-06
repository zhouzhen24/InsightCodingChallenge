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

#include <stdio.h>

TEST(TweetFeatureOne, DISABLED_parser){
	Tweet t;
	string line;
	char* inputPath = "tweet_input/test1.txt";
	ifstream input_file(inputPath);
	ASSERT_TRUE(input_file);

	char* outputPath = "tweet_output/parse_raw.txt";
	ofstream output_file(outputPath);
	ASSERT_TRUE(output_file);

//	ofstream no_unicode("tweet_output/no_unicode.txt");
//	ASSERT_TRUE(no_unicode);

	int line_no = 1;
	while(getline(input_file, line)){
		parser(line, t, "text", "created_at");
		//("line %d <%s (timestamp: %s)>\n", line_no, t.value1.c_str(), t.value2.c_str());
		output_file << t.value1.c_str() << " (timestamp: " << t.value2.c_str() << ")\n";
		line_no++;
	}

	input_file.close();
	output_file.close();
}


TEST(TweetFeatureOne, DISABLED_clean_tweet_text){
	Tweet t;
	string line;
	char* inputPath = "tweet_input/test2.txt";
	ifstream input_file(inputPath);
	ASSERT_TRUE(input_file);

	char* outputPath = "tweet_output/clean_message.txt";
	ofstream output_file(outputPath);
	ASSERT_TRUE(output_file);

	int line_no = 1;
	while(getline(input_file, line)){
		if(!(line_no >= 1 && line_no <= 100))
			break;
		parser(line, t, "text", "created_at");
		printf("Line %5d\n", line_no);
		printf("Cleaning...");
		string raw = t.value1;
		cleanUnicode(t.value1);
		string no_unicode = t.value1;
		cleanEscape(t.value1);
		printf("Done\n");
		printf("Raw       : %s\n", raw.c_str());
		printf("No Unicode: %s\n", no_unicode.c_str());
		printf("Clean     : %s\n", t.value1.c_str());
		line_no++;
	}

	input_file.close();
	output_file.close();
}


TEST(TweetFeatureOne, DISABLED_Full_Functional){
	Tweet t;
	string line;
	char* inputPath = "tweet_input/tweets.txt";
	ifstream input_file(inputPath);
	ASSERT_TRUE(input_file);

	char* outputPath = "tweet_output/ft1.txt";
	ofstream output_file(outputPath);
	ASSERT_TRUE(output_file);

	int line_no = 1;
	int unicode_no = 0;
	while(getline(input_file, line)){
		if(!(line_no >= 1 && line_no <= 1000))
			break;
		parser(line, t, "text", "created_at");
		string raw = t.value1;
		if(cleanUnicode(t.value1))
			unicode_no++;
		string no_unicode = t.value1;
		cleanEscape(t.value1);
		output_file << t.value1.c_str() << " (timestamp: " << t.value2.c_str() << ")\n";
		line_no++;
	}

	input_file.close();
	output_file << "\n" << unicode_no << " tweets contained unicode.";
	output_file.close();
}

TEST(TweetFeatureTwo, parser2){
	Tweet2 t;
	string line;
	char* inputPath = "tweet_input/tweets.txt";
	ifstream input_file(inputPath);
	ASSERT_TRUE(input_file);

	char* outputPath = "tweet_output/raw2.txt";
	ofstream output_file(outputPath);
	ASSERT_TRUE(output_file);

	int line_no = 1;
	while(getline(input_file, line)){
		if(!(line_no >= 1 && line_no <= 50))
			break;
//		printf("Line %5d\n", line_no);
//		printf("line :%s\n", line.c_str());
		parser2(line, t);
//		printf("Tweet Time: %ld\n", t.timestamp_ms);
//		for(size_t i = 0; i < t.hashtags.size(); i++)
//			printf("#%s ", t.hashtags[i].c_str());
//		printf("\n");
		line_no++;
	}

	input_file.close();
	output_file.close();

}



int main(int argc, char** argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
//	string inputName = "tweets.txt";
//	string outputName = "ft1.txt";
//	featureOne(inputName, outputName);
//	return 0;
}


