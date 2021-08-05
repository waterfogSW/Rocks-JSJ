#include <bits/stdc++.h>

#include "generator.h"
#include "rocksdb/db.h"
using namespace std;

const string PATH = "/home/san/workspace/Rocks-JSJ/RsDB";

int main(int argc, char const* argv[]) {
    rocksdb::DB* db;
    rocksdb::Options options;
    options.create_if_missing = true;
    rocksdb::Status status = rocksdb::DB::Open(options, PATH, &db);
    assert(status.ok());

    rocksdb::Status s;

    int record_count = atoi(argv[1]);
    auto kv = generateKV_random(record_count);

    clock_t start = clock(); // 시작 시간 저장

    for (auto i : kv) {
        if (s.ok()) s = db->Put(rocksdb::WriteOptions(), i.first, i.second);
    }

    clock_t end = clock(); // 코드가 끝난 시간 저장

    printf("Time: %lf\n", (double)(end - start)/CLOCKS_PER_SEC);

    string cmd = "rm -rf " + PATH;
    system(cmd.c_str());
    return 0;
}
