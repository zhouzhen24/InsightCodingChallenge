/*
 * FeatureOne.h
 *
 *  Created on: Nov 5, 2015
 *      Author: ZZ
 */

#ifndef SRC_FEATUREONE_H_
#define SRC_FEATUREONE_H_

#include "parser.h"

bool featureOne(string inputName, string outputName){

	inputName = "tweet_input/" + inputName;
	outputName = "tweet_output/" + outputName;
	ifstream input_file(inputName.c_str());
	assert(input_file);
	ofstream output_file(outputName.c_str());
	assert(output_file);

	int unicode_no = 0;
	string line;
	for(int line_no = 1; getline(input_file, line); line_no++){
		Tweet t;
		if(!parser(line, t, "text", "created_at")){
			fprintf(stderr, "line %d: Feature 1 parser fail!\n", line_no);
			fprintf(stderr, "JSON: %s\n", line.c_str());
			continue;
		}
		string raw = t.value1;
		if(cleanUnicode(t.value1))
			unicode_no++;
		string no_unicode = t.value1;
		cleanEscape(t.value1);
		output_file << t.value1.c_str() << " (timestamp: " << t.value2.c_str() << ")\n";
	}

	input_file.close();
	output_file << "\n" << unicode_no << " tweets contained unicode.\n";
	output_file.close();
	printf("End of Feature 1\n");
	return true;
}




#endif /* SRC_FEATUREONE_H_ */
