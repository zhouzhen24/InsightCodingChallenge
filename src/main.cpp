/*
 * test.cpp
 *
 *  Created on: Nov 5, 2015
 *      Author: ZZ
 */

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
    
    string inputName(argv[1]);// = "tweets.txt";
    string outputName1 = "ft1.txt";
    string outputName2 = "ft2.txt";
    if(!featureOne(inputName, outputName1))
        printf("Feature 1 failed\n");
    if(!featureTwo(inputName, outputName2))
        printf("Feature 2 failed\n");
    return 0;
}


