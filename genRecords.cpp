#include <bits/stdc++.h>
using namespace std;

#define RECORD_COUNT 1000000

template <typename... Args>
string string_format(const std::string& format, Args... args);
vector<pair<string, string>> generateKVPair(int record_count);

string getCurrentTime() {
    time_t curTime = time(NULL);
    struct tm* pLocal = localtime(&curTime);

    return string_format("%04d%02d%02d%02d%02d%02d",
                         pLocal->tm_year + 1900, pLocal->tm_mon + 1, pLocal->tm_mday,
                         pLocal->tm_hour, pLocal->tm_min, pLocal->tm_sec);
}

template <typename... Args>
string string_format(const std::string& format, Args... args) {
    size_t size = snprintf(nullptr, 0, format.c_str(), args...) + 1;
    if (size <= 0) {
        throw std::runtime_error("Error during formatting.");
    }
    std::unique_ptr<char[]> buf(new char[size]);
    snprintf(buf.get(), size, format.c_str(), args...);
    return std::string(buf.get(), buf.get() + size - 1);
}

vector<pair<string, string>> generateKVPair(int record_count) {
    try {
        if (record_count <= 0) throw record_count;
    } catch (int exception) {
        cout << "record count must be over then 0" << '\n';
    }

    vector<pair<string, string>> result;

    int index = 0;

    for (int i = 0; i < record_count; i++) {
        string sequenceNum = to_string(index++);
        string deliveryTime = getCurrentTime();

        result.push_back({sequenceNum, deliveryTime});
    }

    return result;
}

int main() {
    int i = 1;
    string temp = to_string(i);

    vector<pair<string, string>> records = generateKVPair(RECORD_COUNT);

    for (size_t i = 0; i < RECORD_COUNT; i++) {
        cout << records[i].first << ' ' << records[i].second << '\n';
    }
}