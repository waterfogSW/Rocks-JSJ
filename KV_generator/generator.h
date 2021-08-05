#ifndef _GENERATOR_H
#define _GENERATOR_H

#include <bits/stdc++.h>

using namespace std;

/* 
generateKV_csv.cpp - generate records from parsing CSV file
file name       : path of csv file
timeIndex       : index of time stamp in csv file
idIndex         : index of pirmitive key in csv file 
*/
vector<pair<string, string>> generateKV_csv(string filename, int timeIndex, int idIndex);

/*
generateKV_random - generate records from parsing CSV file
record_count : number of records to generate
*/
vector<pair<string, string>> generateKV_random(int record_count);


#endif