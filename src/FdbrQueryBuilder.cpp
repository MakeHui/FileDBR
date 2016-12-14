//
// Created by MakeHui on 16/12/5.
//

#include <iostream>

#include "FdbrQueryBuilder.h"

using namespace std;
using namespace FileDBR;

namespace FileDBR {

    FdbrQueryBuilder::FdbrQueryBuilder(string databasePath, string delimiter) {
        this->database.setDatabasePath(databasePath);
        this->database.setDelimiter(delimiter);
    }

    FdbrQueryBuilder::~FdbrQueryBuilder() {

    }

    vector<map<string, string>> FdbrQueryBuilder::select(string table, vector<string> columns, map<string, string> where) {
        vector<map<string, string>> result;
        vector<map<string, string>> allData = this->database.read(table);

        for (int i = 0; i < allData.size(); ++i) {
            map<string, string>::iterator itr;
            for (itr = allData[i].begin(); itr != allData[i].end(); ++itr) {
                cout << "key: " << itr->first << " value: " << itr->second << endl;
            }
        }

        return result;
    }

//    bool FdbrQueryBuilder::insert(string table, map<string, string> datas);
//
//    bool FdbrQueryBuilder::updatet(string table, map<string, string> datas, map<string, string> where);
//
//    bool FdbrQueryBuilder::del(string table, map<string, string> where);
//
//    vector<map<string, string>> FdbrQueryBuilder::get(string table, vector<string> columns, map<string, string> where);
//
//    bool FdbrQueryBuilder::has(string table, map<string, string> where);
//
//    bool FdbrQueryBuilder::count(string table, map<string, string> where);
//
//    vector<map<string, string>> FdbrQueryBuilder::max(string table, vector<string> columns, map<string, string> where);
//
//    vector<map<string, string>> FdbrQueryBuilder::min(string table, vector<string> columns, map<string, string> where);
//
//    vector<map<string, string>> FdbrQueryBuilder::avg(string table, vector<string> columns, map<string, string> where);
//
//    vector<map<string, string>> FdbrQueryBuilder::sum(string table, vector<string> columns, map<string, string> where);

    int FdbrQueryBuilder::vectorSearch(string needle, vector<string> haystack) {
        for (int i = 0; i < haystack.size(); ++i) {
            if (haystack[i] == needle) {
                return i;
            }
        }

        return -1;
    }

}
