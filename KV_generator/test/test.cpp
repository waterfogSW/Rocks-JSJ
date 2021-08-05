#include <bits/stdc++.h>

#include "rocksdb/db.h"

using namespace std;

const string PATH = "/home/san/workspace/Rocks-JSJ/RsDB";

int main() {
    rocksdb::DB* db;
    rocksdb::Options options;
    options.create_if_missing = true;
    rocksdb::Status status = rocksdb::DB::Open(options, PATH, &db);
    assert(status.ok());


}