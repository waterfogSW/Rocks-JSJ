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
generateKV_random - generate records by random, high bit - sequence number, low bit - delivery time
record_count : number of records to generate
*/
vector<pair<string, string>> generateKV_random_high(int record_count);

/*
generateKV_random - generate records by random, low bit - sequence number, high bit - delivery time
record_count : number of records to generate
*/
vector<pair<string, string>> generateKV_random_low(int record_count);

#endif