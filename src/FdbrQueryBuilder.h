//
// Created by MakeHui on 16/12/5.
//

#ifndef FILEDBR_FDBRQUERYBUILDER_H
#define FILEDBR_FDBRQUERYBUILDER_H

#include <string>
#include <vector>
#include <map>

using namespace std;

namespace FileDBR {
    class FdbrQueryBuilder {
    public:
        vector<map<string, string>> select(string table, vector<string> columns, map<string, string> where);

        bool insert(string table, map<string, string> datas);

        bool updatet(string table, map<string, string> datas, map<string, string> where);

        bool del(string table, map<string, string> where);

        vector<map<string, string>> get(string table, vector<string> columns, map<string, string> where);

        bool has(string table, map<string, string> where);

        bool count(string table, map<string, string> where);

        vector<map<string, string>> max(string table, vector<string> columns, map<string, string> where);

        vector<map<string, string>> min(string table, vector<string> columns, map<string, string> where);

        vector<map<string, string>> avg(string table, vector<string> columns, map<string, string> where);

        vector<map<string, string>> sum(string table, vector<string> columns, map<string, string> where);

    private:
        string databasePath;
        bool  debugMode;
        vector<string> logs;

    };
}


#endif //FILEDBR_FDBRQUERYBUILDER_H
