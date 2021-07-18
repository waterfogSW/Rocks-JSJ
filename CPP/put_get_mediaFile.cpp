#include <bits/stdc++.h>

#include "rocksdb/db.h"
#include "rocksdb/options.h"
#include "rocksdb/slice.h"

using namespace ROCKSDB_NAMESPACE;
using namespace std;

const char* filename_in = "./media/temp0.mp4";
const char* filename_out = "./media/dest0.mp4";

template<typename T, typename... Args>
unique_ptr<T> make_unique(Args&&... args) {
	    return unique_ptr<T>(new T(forward<Args>(args)...));
}

template <typename T>
string Pack(const T* data, int _size)
{
	    string d(_size, L'\0');
	    memcpy(&d[0], data, d.size());
	    return d;
}

template <typename T>
unique_ptr<T> Unpack(const string& data)
{
	    if (data.size() != sizeof(T))
		            return nullptr;

	        auto d = make_unique<T>();
		    memcpy(d.get(), data.data(), data.size());
		        return d;
}


int main() {
    DB* db;

    Options options;
    options.create_if_missing = true;
    Status status = DB::Open(options, "./data", &db);
    assert(status.ok());

    options.error_if_exists = true;

    // Status
    Status s;
    if (!s.ok()) cerr << s.ToString() << endl;


    // 스트림 객체 생성
    // 동영상 파일 READ
    ifstream fin;
    fin.open(filename_in, ios::in | ios::binary);

    if (!fin) {
        cout << "FILE OPEN EXCEPTION" << endl;
        return 0;
    }

    // 동영상 파일 WRITE
    ofstream fout;
    fout.open(filename_out, ios::out | ios::binary);

    if (!fout) {
        cout << "FILE OPEN EXCEPTION" << endl;
        return 0;
    }


    int count = 0;
    char value[1024];
    int default_key = 0;
    string key_name = "key_";


    while (!fin.eof()) {
        fin.read(value, 1024);		// 최대  1024 바이트 읽어 배열 s에 저장. 
        int n = fin.gcount();   // 실제 읽은 바이트 수 반환

        string key = key_name + to_string(default_key++);

	    if(n < 1024){

		    char *temp_value = new char[n];
		
		    for(int i=0; i<n; i++){
			    temp_value[i] = value[i];
		    }

		    if(s.ok()) s = db->Put(rocksdb::WriteOptions(), key, Pack(&temp_value, n));		
	    }
	    else{
	    	if(s.ok()) s = db->Put(rocksdb::WriteOptions(), key, Pack(&value, n));
    	}
    }

    fin.close();

    
    int key_iter = 0;
    
    for (int i = 0; i < default_key; i++) {
        string key = key_name + to_string(key_iter++);

        string get_value;
       	s = db->Get(rocksdb::ReadOptions(), key, &get_value);


        // COPY
        int n = get_value.size();
        fout.write(get_value.c_str(), n);
   }

    delete db;
    return 0;
}
