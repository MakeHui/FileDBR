//
// Created by MakeHui on 16/12/5.
//

#include <iostream>
#include <sstream>

#include "FdbrQueryBuilder.h"

using namespace std;
using namespace FileDBR;

namespace FileDBR {
    
    FdbrQueryBuilder::FdbrQueryBuilder(string databasePath, string delimiter) {
        this->database.setDatabasePath(databasePath);
        this->database.setDelimiter(delimiter);
        
        this->maths = {">", ">=", "!", "<", "<=", "~", "!~", "="};
    }

    FdbrQueryBuilder::~FdbrQueryBuilder() {

    }

    vector<map<string, string>> FdbrQueryBuilder::select(string table, vector<string> columns, map<string, string> where) {
        vector<map<string, string>> allData = this->database.read(table);
        vector<map<string, string>> result;
        vector<map<string, string>> _where;
        
        map<string, string>::iterator itr;
        
        for (itr = where.begin(); itr != where.end(); ++itr) {
            vector<string> firstWhere = split(itr->first, " ");
            map<string, string> thisWhere;
            
            thisWhere["field"] = firstWhere[0];
            thisWhere["value"] = itr->second;
            thisWhere["math"] =  (firstWhere.size() == 2) ? firstWhere[1] : "=";
            if (!this->inVector(thisWhere["math"], this->maths)) {
                thisWhere["math"] = "=";
            }
            
            _where.push_back(thisWhere);
        }
        
        bool isContinue;
        for (int i = 0; i < allData.size(); ++i) {
            isContinue = false;
            for (int j = 0; j < _where.size(); ++j) {
                if (!this->whereCompare(allData[i][_where[j]["field"]], _where[j]["value"], _where[j]["math"])) {
                    isContinue = true;
                    break;
                }
            }
            
            if (isContinue) {
                continue;
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

    bool FdbrQueryBuilder::whereCompare(string str, string str1, string math) {
        if (">" == math && str <= str1) {
            return false;
        }
        else if (">=" == math && str < str1) {
            return false;
        }
        else if ("!" == math && str == str1) {
            return false;
        }
        else if ("<" == math && str >= str1) {
            return false;
        }
        else if ("<=" == math && str > str1) {
            return false;
        }
        else if ("~" == math && str.find(str1) == string::npos) {
            return false;
        }
        else if ("!~" == math && str.find(str1) != string::npos) {
            return false;
        }
        else if ("=" == math && str != str1) {
            return false;
        }
        
        return true;
    }
    
    vector<string> FdbrQueryBuilder::split(const string str, string delimiter, int limit) {
        vector<string> result;
        stringstream ss;
        ss.str(str);
        string item;
        int i = 0;
        
        while (getline(ss, item, *this->strToChar(delimiter))) {
            result.push_back(item);
            if (i == limit) break;
        }
        
        return result;
    }
    
    char * FdbrQueryBuilder::strToChar(string str) {
        char * writable = new char[str.size() + 1];
        std::copy(str.begin(), str.end(), writable);
        writable[str.size()] = '\0'; // don't forget the terminating 0
        
        return writable;
    }
    
    bool FdbrQueryBuilder::inVector(string needle, vector<string> &haystack) {
        return find(haystack.begin(), haystack.end(), needle) != haystack.end();
    }
    
}
