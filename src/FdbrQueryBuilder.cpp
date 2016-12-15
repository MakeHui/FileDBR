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

    vector<map<string, string>> FdbrQueryBuilder::select(string table, vector<string> columns, map<string, string> where, bool fuzzy) {
        vector<map<string, string>> result;
        vector<map<string, string>> allData = this->database.read(table);

        map<string, string>::iterator itr;
        for (int i = 0; i < allData.size(); ++i) {
            for (itr = where.begin(); itr != where.end(); ++itr) {
                cout << "key: " << itr->first << " value: " << itr->second << endl;
                if (fuzzy) {
                    if (allData[i][itr->first].find(itr->second) == string::npos) {
                        continue;
                    }
                }
                else {
                    if (allData[i][itr->first] != itr->second) {
                        continue;
                    }
                }
            }
            
            map<string, string> column;
            if (columns.size() != 0) {
                for (int j = 0; j < columns.size(); ++j) {
                    column[columns[j]] = allData[i][columns[j]];
                }
            }
            else {
                column = allData[i];
            }
            
            result.push_back(column);
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

}
