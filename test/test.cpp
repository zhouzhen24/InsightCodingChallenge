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

TEST(TweetFeatureTwo, DISABLED_parser2){
	Tweet2 t;
	string line;
	unordered_map<string, Hashtag*> allHashtags;
	vector<Edge*> allEdges;

	char* inputPath = "tweet_input/tweets.txt";
	ifstream input_file(inputPath);
	ASSERT_TRUE(input_file);

	char* outputPath = "tweet_output/raw2.txt";
	ofstream output_file(outputPath);
	ASSERT_TRUE(output_file);



	for(int line_no = 1; getline(input_file, line); line_no++){
		if(!(line_no >= 1 && line_no <= 50))
			break;
//		printf("Line %5d\n", line_no);
//		printf("line :%s\n", line.c_str());
		parser2(line, t);

		if(!t.hashtags.empty() && t.hashtags.size() == 1){
			string message = t.hashtags.front();
			if(allHashtags.find(message) != allHashtags.end())
				allHashtags[message]->updateTime(t.timestamp_ms);
			else{
				Hashtag* ht = new Hashtag(t.timestamp_ms, message);
				allHashtags.insert(make_pair(message, ht));
			}
		}
		//if we have edges
		else if (!t.hashtags.empty()){
			vector<pair<string, string> > pairs;
			t.convertToPairs(pairs);
			for(pair<string, string> p : pairs){
				unordered_map<string, Hashtag*>::iterator it1 = allHashtags.find(p.first), it2 = allHashtags.find(p.second);
				Hashtag *ht1, *ht2;
				if(it1 == allHashtags.end()){
					ht1 = new Hashtag(t.timestamp_ms, p.first);
					allHashtags.insert(make_pair(p.first, ht1));
				}
				else
					ht1 = it1->second;
				if(it2 == allHashtags.end()){
					ht2 = new Hashtag(t.timestamp_ms, p.second);
					allHashtags.insert(make_pair(p.second, ht2));
				}
				else
					ht2 = it2->second;

				//update time
				ht1->time = t.timestamp_ms;
				ht2->time = t.timestamp_ms;
				Edge* e = ht1->getEdge(ht2);
				if(e != NULL){
					e->updateTime(t.timestamp_ms);
					continue;
				}
				e = new Edge(t.timestamp_ms, ht1, ht2);
				allEdges.push_back(e);

			}

		}
		printf("Line %d\n", line_no);
		printf("Hashtags: \n");
		for(unordered_map<string, Hashtag*>::iterator ht = allHashtags.begin(); ht != allHashtags.end(); ht++)
			printf("#%s ", ht->second->text.c_str());
		printf("\nEdges :\n");
		for(Edge* e : allEdges)
			printf("#%s <-> #%s\n", e->hashtags[0]->text.c_str(), e->hashtags[1]->text.c_str());
		printf("\n");
		double degree = (double)allHashtags.size() / (double)allEdges.size();
		printf("%d hashtags, %d edges\n%d Degree\n", allHashtags.size(), allEdges.size(), degree);
	}
	for(Edge* e : allEdges)
		delete e;
	for(unordered_map<string, Hashtag*>::iterator ht = allHashtags.begin(); ht != allHashtags.end(); ht++)
		delete ht->second;
	input_file.close();
	output_file.close();

}



int main(int argc, char** argv){
//	::testing::InitGoogleTest(&argc, argv);
//	return RUN_ALL_TESTS();
//	string inputName = "tweets.txt";
//	string outputName = "ft1.txt";
//	featureOne(inputName, outputName);
//	return 0;

		string inputName = "tweets.txt";
		string outputName = "raw2.txt";
		if(!featureTwo(inputName, outputName))
			printf("Feature 2 failed\n");
		return 0;
}


