#include <bits/stdc++.h>

#include "generator.h"
#include "rocksdb/db.h"
using namespace std;

const string PATH = "/home/san/workspace/Rocks-JSJ/RsDB";

/* 
flag : 1 - highbit sequence number
flag : 0 - low bit sequence number
 */
void test(int flag, int record_count) {
    rocksdb::DB* db;
    rocksdb::Options options;
    options.create_if_missing = true;
    rocksdb::Status status = rocksdb::DB::Open(options, PATH, &db);
    assert(status.ok());

    rocksdb::Status s;

    auto kv = flag ? generateKV_random_high(record_count) : generateKV_random_low(record_count);

    clock_t start = clock(); // 시작 시간 저장

    for (auto i : kv) {
        if (s.ok()) s = db->Put(rocksdb::WriteOptions(), i.first, i.second);
    }

    clock_t end = clock(); // 코드가 끝난 시간 저장

    flag ? cout << "high " : cout << "low ";
    printf("Time: %lf\n", (double)(end - start)/CLOCKS_PER_SEC);

    string cmd = "rm -rf " + PATH;
    system(cmd.c_str());
    delete db;
}

int main(int argc, char const* argv[]) {
    test(1, atoi(argv[1]));
    test(0, atoi(argv[1]));
    return 0;
}
