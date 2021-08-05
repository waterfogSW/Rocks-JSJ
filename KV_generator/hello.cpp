#include <bits/stdc++.h>

#include "generator.h"
#include "rocksdb/db.h"
using namespace std;

string kDBPath = "~/workspace/RocksDB_test";

int main(int argc, char const* argv[]) {
    rocksdb::DB* db;
    rocksdb::Options options;
    rocksdb::Status s = rocksdb::DB::Open(options, kDBPath, &db);
    assert(s.ok());

    cout << "코드 작성중입니다" << '\n';
    auto kv = generateKV_random(1000000);

    //MK: 시작/끝 시간을 측정하기 위해서 추가
    struct timespec begin, end;
    double tmpValue = 0.0;

    //MK: 연산 시작과 함께 시간을 측정함
    clock_gettime(CLOCK_MONOTONIC, &begin);

    for (auto i : kv) {
        if (s.ok()) s = db->Put(rocksdb::WriteOptions(), i.first, i.second);
    }

    //MK: 연산이 끝나면 시간을 측정함
    clock_gettime(CLOCK_MONOTONIC, &end);
    cout << tmpValue;
}
