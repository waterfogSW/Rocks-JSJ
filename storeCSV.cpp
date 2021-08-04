#include <assert.h>
#include <bits/stdc++.h>

#include "rocksdb/db.h"
#include "rocksdb/db_bench_tool.h"

#define CSV_PATH "./log.csv"  // CSV file path

using namespace std;

rocksdb::DB* db;
rocksdb::Options options;

string removeSpecials(string str);
vector<pair<string, vector<string>>> read_csv(string filename);
vector<pair<string, string>> generateKV(string filename);

vector<pair<string, vector<string>>> read_csv(string filename) {
    // Reads a CSV file into a vector of <string, vector<int>> pairs where
    // each pair represents <column name, column values>

    // Create a vector of <string, string vector> pairs to store the result
    vector<pair<string, vector<string>>> result;

    // Create an input filestream
    ifstream csvFile(filename);

    // Make sure the file is open
    if (!csvFile.is_open()) throw runtime_error("Could not open file");

    // Helper vars
    string line, colname;
    string val;

    // Read the column names
    if (csvFile.good()) {
        // Extract the first line in the file
        getline(csvFile, line);

        // Create a stringstream from line
        stringstream ss(line);

        // Extract each column name
        while (getline(ss, colname, ',')) {
            // Initialize and add <colname, int vector> pairs to result
            result.push_back({colname, vector<string>{}});
        }
    }

    // Read data, line by line
    while (getline(csvFile, line)) {
        // Create a stringstream of the current line
        cout << line << '\n';

        // Create a stringstream from line
        stringstream ss(line);

        // Keep track of the current column index
        int colIdx = 0;
        string substr;

        while (getline(ss, substr, ',')) {
            substr = removeSpecials(substr);
            result.at(colIdx++).second.push_back(substr);
        }
    }

    // Close file
    csvFile.close();

    return result;
}

string removeSpecials(string str) {
    int i = 0, len = str.length();
    while (i < len) {
        char c = str[i];
        if ((c >= '0') && (c <= '9')) {
            ++i;
        } else {
            str.erase(i, 1);
            --len;
        }
    }
    return str;
}

/* filename : file path, timeIndex : index of timestamp in csv file, id : index of id in csv file*/
vector<pair<string, string>> generateKV(string filename, int timeIndex, int idIndex) {
    auto csv_vector = read_csv(CSV_PATH);
    int row_count = csv_vector.at(idIndex).second.size();

    vector<pair<string,string>> kv_pairs;

    for (int i = 0; i < row_count; i++) {
        string key;
        string value;
        key += csv_vector.at(idIndex).second[i];
        key += csv_vector.at(timeIndex).second[i];

        for (int j = 0; j < csv_vector.size(); j++) {
            value += csv_vector.at(j).second[i];
        }
        kv_pairs.push_back({key, value});
    }

    return kv_pairs;
}

int main() {
    
    auto result = generateKV(CSV_PATH, 3, 0);

    for(auto i : result) {
        cout << i.first << " " << i.second << '\n';
    }
    
    // options.create_if_missing = true;
    // rocksdb::Status status = rocksdb::DB::Open(options, "./testdb", &db);
    // assert(status.ok());

    // string key = "1";
    // string value = "hello 1";

    // string result;

    // rocksdb::Status s;
    // // if (s.ok()) s = db->Put(rocksdb::WriteOptions(), key, value);
    // if (s.ok()) s = db->Get(rocksdb::ReadOptions(), key, &result);
    // if (s.ok()) s = db->Delete(rocksdb::WriteOptions(), key);

    // cout << result;
    // delete db;
}