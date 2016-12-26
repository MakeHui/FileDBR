//
// Created by MakeHui on 16/12/5.
//

#ifndef FILEDBR_FDBRQUERYBUILDER_H
#define FILEDBR_FDBRQUERYBUILDER_H

#include <string>
#include <vector>
#include <map>

#include "FdbrDatabase.h"

namespace FileDBR {
    class FdbrQueryBuilder {
    public:
        FdbrQueryBuilder(std::string databasePath, std::string delimiter = FDBR_SPLIT_DELIMITER);

        ~FdbrQueryBuilder();

        bool createTable(std::string table, std::vector<std::string> columns);
        
        bool deleteTable(std::string table);
        
        std::vector<std::map<std::string, std::string>> select(std::string table, std::vector<std::string> columns = {}, std::map<std::string, std::string> where = {}, std::map<std::string, std::string> order = {});

        bool insert(std::string table, std::map<std::string, std::string> datas);

        unsigned int update(std::string table, std::map<std::string, std::string> datas, std::map<std::string, std::string> where = {});

        int del(std::string table, std::map<std::string, std::string> where = {});

        std::map<std::string, std::string> get(std::string table, std::vector<std::string> columns = {}, std::map<std::string, std::string> where = {}, std::map<std::string, std::string> order = {});

        bool has(std::string table, std::map<std::string, std::string> where = {});

        unsigned int count(std::string table, std::map<std::string, std::string> where = {});

        std::string max(std::string table, std::string column, std::map<std::string, std::string> where = {});

        std::string min(std::string table, std::string column, std::map<std::string, std::string> where = {});

        long double avg(std::string table, std::string column, std::map<std::string, std::string> where = {});

        long double sum(std::string table, std::string column, std::map<std::string, std::string> where = {});
        
    protected:
        bool sortMethod(std::vector<std::map<std::string,std::string>> &data, std::map<std::string, std::string> order);
        
        bool whereCompare(std::string str, std::string str2, std::string math);
        
        bool checkColumns(std::vector<std::string> columns);
        
        std::vector<std::string> mapKeys(std::map<std::string, std::string> data);
        
        std::vector<std::string> mapValues(std::map<std::string, std::string> data);

        std::vector<std::string> split(const std::string str, std::string delimiter, int limit = 512);
        
        char * strToChar(std::string str);
        
        bool inVector(std::string needle, std::vector<std::string> &haystack);
        
    private:
        FdbrDatabase database;
        bool debugMode;
        std::vector<std::string> logs;
        std::vector<std::string> maths;
    };
}


#endif //FILEDBR_FDBRQUERYBUILDER_H
