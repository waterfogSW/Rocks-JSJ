# YCSB 실험 MongoDB, RocksDB
## throughput제한하여 실험 2000, 4000, 6000 ....
import os
from pymongo import MongoClient, mongo_client

mongo_client = MongoClient('mongodb://localhost:27017')

def removeAllFile(filePath):
    if os.path.exists(filePath):
        for file in os.scandir(filePath):
            os.remove(file.path)
        return 'Remove all files in directory'
    else :
        return 'Wrong Path'

def removeDatabase():
    mongo_client.drop_database('workload')

def rocks_test_a(record):
    ## RocksDB rocksdb.dir= 에 rocksDB 데이터 저장되는 경로, ../result는 결과가 저장되는 경로
    os.system("./bin/ycsb load rocksdb -s -P workloads/workloada -p rocksdb.dir=../data -target " + str(record) + " -p recordcount=100000")
    os.system("./bin/ycsb run rocksdb -s -P workloads/workloada -p rocksdb.dir=../data -target " + str(record) + " -p operationcount=100000" + " | grep 'Latency' > ../result" + str(record) + ".txt")

def mongo_test_a(record):
    ## MongoDB url : 'workload' 는 몽고디비 데이터 베이스, ../result는 결과가 저장되는 경로
    os.system("./bin/ycsb load mongodb -s -P workloads/workloada -p mongodb.url='mongodb://127.0.0.1:27017/workload' -target " + str(record) + " -p recordcount=100000")
    os.system("./bin/ycsb run mongodb -s -P workloads/workloada -p mongodb.url='mongodb://127.0.0.1:27017/workload' -target " + str(record) + " -p operationcount=100000" + " | grep 'Latency' > ../result" + str(record) + ".txt")

def main():
    for i in range(1, 8):
        ## RocksDB 실험 : 아래에는 데이터 저장되는 폴더 수정할것
        # removeAllFile("../data")
        # rocks_test_a(2000 * i)

        removeDatabase()
        mongo_test_a(2000 * i)

if __name__ == "__main__":
    main()
