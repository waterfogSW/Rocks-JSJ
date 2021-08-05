#include <bits/stdc++.h>

#include "generator.h"
#include "rocksdb/db.h"
using namespace std;

const string PATH = "/home/san/workspace/Rocks-JSJ/RsDB";

timespec diff(timespec start, timespec end) {
    timespec temp;

    if ((end.tv_nsec - start.tv_nsec) < 0) {
        temp.tv_sec = end.tv_sec - start.tv_sec - 1;
        temp.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
    } else {
        temp.tv_sec = end.tv_sec - start.tv_sec;
        temp.tv_nsec = end.tv_nsec - start.tv_nsec;
    }
    return temp;
}

int main(int argc, char const* argv[]) {
    rocksdb::DB* db;
    rocksdb::Options options;
    options.create_if_missing = true;
    rocksdb::Status status = rocksdb::DB::Open(options, PATH, &db);
    assert(status.ok());

    rocksdb::Status s;

    int record_count = atoi(argv[1]);
    auto kv = generateKV_random(record_count);

    struct timespec begin, end;
    double tmpValue = 0.0;

    //시간 측정 시작
    clock_gettime(CLOCK_MONOTONIC, &begin);

    for (auto i : kv) {
        if (s.ok()) s = db->Put(rocksdb::WriteOptions(), i.first, i.second);
    }

    //시간 측정 끝
    clock_gettime(CLOCK_MONOTONIC, &end);

    timespec temp = diff(begin, end);
    long time = temp.tv_sec + temp.tv_nsec;

    printf("Time (ms): %lf\n", (double)time / 1000000000);

    string cmd = "rm -rf " + PATH;
    system(cmd.c_str());
    return 0;
}
