//
// Created by MakeHui on 16/12/5.
//

#include <iostream>
#include <sstream>
#include <algorithm>

#include "FdbrQueryBuilder.h"

namespace FileDBR {
    
    FdbrQueryBuilder::FdbrQueryBuilder(std::string databasePath, std::string delimiter) {
        this->database.setDatabasePath(databasePath);
        this->database.setDelimiter(delimiter);
        
        this->maths = {">", ">=", "!=", "<", "<=", "~", "!~", "="};
    }

    FdbrQueryBuilder::~FdbrQueryBuilder() {

    }
    
    bool FdbrQueryBuilder::createTable(std::string table, std::vector<std::string> columns) {
        this->database.createFile(table);
        this->database.setFileStructure(columns);
        
        return this->database.write(table);
    }
    
    bool FdbrQueryBuilder::deleteTable(std::string table) {
        return this->database.delFile(table);
    }

    std::vector<std::map<std::string, std::string>> FdbrQueryBuilder::select(std::string table, std::vector<std::string> columns, std::map<std::string, std::string> where, std::map<std::string, std::string> order) {
        std::vector<std::map<std::string, std::string>> fileData = this->database.read(table);
        std::vector<std::map<std::string, std::string>> result;
        std::vector<std::map<std::string, std::string>> _where;
        std::vector<std::string> whereKeys;
        std::map<std::string, std::string>::iterator itr;
        
        if (!this->checkColumns(columns)) {
            return result;
        }
        
        if (!this->checkColumns(this->mapKeys(order))) {
            return result;
        }
        
        for (itr = where.begin(); itr != where.end(); ++itr) {
            std::vector<std::string> firstWhere = split(itr->first, " ");
            std::map<std::string, std::string> thisWhere;
            
            whereKeys.push_back(firstWhere[0]);
            
            thisWhere["field"] = firstWhere[0];
            thisWhere["value"] = itr->second;
            thisWhere["math"] =  (firstWhere.size() == 2) ? firstWhere[1] : "=";
            if (!this->inVector(thisWhere["math"], this->maths)) {
                thisWhere["math"] = "=";
            }
            
            _where.push_back(thisWhere);
        }
        
        if (!this->checkColumns(whereKeys)) {
            return result;
        }
        
        bool isContinue;
        for (int i = 0; i < fileData.size(); ++i) {
            isContinue = false;
            for (int j = 0; j < _where.size(); ++j) {
                if (!this->whereCompare(fileData[i][_where[j]["field"]], _where[j]["value"], _where[j]["math"])) {
                    isContinue = true;
                    break;
                }
            }
            
            if (isContinue) {
                continue;
            }
            
            result.push_back(fileData[i]);
        }
        
        if (order.size() != 0) {
            this->sortMethod(result, order);
        }

        if (columns.size() != 0) {
            for (int i = 0; i < result.size(); ++i) {
                std::map<std::string, std::string> column;
                for (int j = 0; j < columns.size(); ++j) {
                    column[columns[j]] = result[i][columns[j]];
                }
                result[i] = column;
            }
        }

        return result;
    }

    bool FdbrQueryBuilder::insert(std::string table, std::map<std::string, std::string> datas) {
        std::vector<std::map<std::string, std::string>> fileData = this->select(table);
        std::vector<std::string> structure = this->database.getFileStructure();
        std::map<std::string, std::string> rowData;
        std::map<std::string, std::string>::iterator itr;
        
        if (!this->checkColumns(this->mapKeys(datas))) {
            return false;
        }

        for (int i = 0; i < structure.size(); ++i) {
            rowData[structure[i]] = "";
        }

        for (itr = datas.begin(); itr != datas.end(); ++itr) {
            rowData[itr->first] = itr->second;
        }

        fileData.push_back(rowData);
        this->database.setFileData(fileData);
        this->database.write(table);

        return true;
    }

    unsigned int FdbrQueryBuilder::update(std::string table, std::map<std::string, std::string> datas, std::map<std::string, std::string> where) {
        std::vector<std::map<std::string, std::string>> fileData = this->database.read(table);
        std::vector<std::map<std::string, std::string>> result;
        std::vector<std::map<std::string, std::string>> _where;
        std::vector<std::string> whereKeys;
        std::map<std::string, std::string>::iterator itr;
        
        if (!this->checkColumns(this->mapKeys(datas))) {
            return 0;
        }
        
        for (itr = where.begin(); itr != where.end(); ++itr) {
            std::vector<std::string> firstWhere = this->split(itr->first, " ");
            std::map<std::string, std::string> thisWhere;
            
            whereKeys.push_back(firstWhere[0]);

            thisWhere["field"] = firstWhere[0];
            thisWhere["value"] = itr->second;
            thisWhere["math"] =  (firstWhere.size() == 2) ? firstWhere[1] : "=";
            if (!this->inVector(thisWhere["math"], this->maths)) {
                thisWhere["math"] = "=";
            }

            _where.push_back(thisWhere);
        }
        
        if (!this->checkColumns(whereKeys)) {
            return 0;
        }

        int lines = 0;
        bool isContinue;
        for (int i = 0; i < fileData.size(); ++i) {
            isContinue = false;
            for (int j = 0; j < _where.size(); ++j) {
                if (!this->whereCompare(fileData[i][_where[j]["field"]], _where[j]["value"], _where[j]["math"])) {
                    isContinue = true;
                    break;
                }
            }

            if (isContinue) {
                continue;
            }

            for (itr = datas.begin(); itr != datas.end(); ++itr) {
                fileData[i][itr->first] = itr->second;
            }
            
            lines++;
        }

        this->database.setFileData(fileData);
        this->database.write(table);

        return lines;
    }

    unsigned int FdbrQueryBuilder::del(std::string table, std::map<std::string, std::string> where) {
        std::vector<std::map<std::string, std::string>> fileData = this->database.read(table);
        std::vector<std::map<std::string, std::string>> result;
        std::vector<std::map<std::string, std::string>> _where;
        std::vector<std::string> whereKeys;
        std::map<std::string, std::string>::iterator itr;
        
        for (itr = where.begin(); itr != where.end(); ++itr) {
            std::vector<std::string> firstWhere = split(itr->first, " ");
            std::map<std::string, std::string> thisWhere;
            
            whereKeys.push_back(firstWhere[0]);

            thisWhere["field"] = firstWhere[0];
            thisWhere["value"] = itr->second;
            thisWhere["math"] =  (firstWhere.size() == 2) ? firstWhere[1] : "=";
            if (!this->inVector(thisWhere["math"], this->maths)) {
                thisWhere["math"] = "=";
            }

            _where.push_back(thisWhere);
        }
        
        if (!this->checkColumns(whereKeys)) {
            return 0;
        }

        int lines = 0;
        bool isContinue;
        for (int i = 0; i < fileData.size(); ++i) {
            isContinue = false;
            for (int j = 0; j < _where.size(); ++j) {
                if (!this->whereCompare(fileData[i][_where[j]["field"]], _where[j]["value"], _where[j]["math"])) {
                    isContinue = true;
                    break;
                }
            }

            if (isContinue) {
                result.push_back(fileData[i]);
                continue;
            }
            
            lines++;
        }

        this->database.setFileData(result);
        this->database.write(table);

        return lines;
    }

    std::map<std::string, std::string> FdbrQueryBuilder::get(std::string table, std::vector<std::string> columns, std::map<std::string, std::string> where, std::map<std::string, std::string> order) {
        std::vector<std::map<std::string, std::string>> fileData = this->select(table, columns, where, order);
        std::map<std::string, std::string> result;
        
        if (fileData.size() != 0) {
            result = fileData[0];
        }
        
        return result;
    }

    bool FdbrQueryBuilder::has(std::string table, std::map<std::string, std::string> where) {
        std::vector<std::map<std::string, std::string>> fileData = this->select(table, {}, where);

        return fileData.size() != 0;
    }

    unsigned int FdbrQueryBuilder::count(std::string table, std::map<std::string, std::string> where) {
        std::vector<std::map<std::string, std::string>> fileData = this->select(table, {}, where);

        return static_cast<int>(fileData.size());
    }

    std::string FdbrQueryBuilder::max(std::string table, std::string column, std::map<std::string, std::string> where) {
        std::vector<std::map<std::string, std::string>> fileData = this->select(table, {column}, where, {{column, "DESC"}});

        if (fileData.size() != 0) {
            return fileData[0][column];
        }

        return "";
    }

    std::string FdbrQueryBuilder::min(std::string table, std::string column, std::map<std::string, std::string> where) {
        std::vector<std::map<std::string, std::string>> fileData = this->select(table, {column}, where, {{column, "ASC"}});

        if (fileData.size() != 0) {
            return fileData[0][column];
        }

        return "";
    }

    long double FdbrQueryBuilder::avg(std::string table, std::string column, std::map<std::string, std::string> where) {
        std::vector<std::map<std::string, std::string>> fileData = this->select(table, {column}, where);
        double sum = 0.0;

        for (int i = 0; i < fileData.size(); ++i) {
            sum += std::atof(fileData[i][column].c_str());
        }

        return sum / fileData.size();
    }

    long double FdbrQueryBuilder::sum(std::string table, std::string column, std::map<std::string, std::string> where) {
        std::vector<std::map<std::string, std::string>> fileData = this->select(table, {column}, where);
        double sum = 0.0;

        for (int i = 0; i < fileData.size(); ++i) {
            sum += std::atof(fileData[i][column].c_str());
        }

        return sum;
    }

    bool FdbrQueryBuilder::sortMethod(std::vector<std::map<std::string,std::string>> &data, std::map<std::string, std::string> order) {
         std::map<std::string, std::string>::iterator itr = order.begin();
         std::transform(itr->second.begin(), itr->second.end(), itr->second.begin(), ::toupper);
         
         std::sort(data.begin(), data.end(), [&](std::map<std::string, std::string> first, std::map<std::string, std::string> second) {
             long int firstInt = std::atoi(first[itr->first].c_str());
             long int secondInt = std::atoi(second[itr->first].c_str());
             
             if (errno == 0) {
                 if (itr->second == "ASC") {
                     return firstInt < secondInt;
                 }
                 else {
                     return firstInt > secondInt;
                 }
             }
             else {
                 if (itr->second == "ASC") {
                     return first["a"] < second[itr->first];
                 }
                 else {
                     return first[itr->first] > second[itr->first];
                 }
             }
         });
         
         return true;
    }

    bool FdbrQueryBuilder::whereCompare(std::string str, std::string str1, std::string math) {
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
        else if ("~" == math && str.find(str1) == std::string::npos) {
            return false;
        }
        else if ("!~" == math && str.find(str1) != std::string::npos) {
            return false;
        }
        else if ("=" == math && str != str1) {
            return false;
        }
        
        return true;
    }
    
    bool FdbrQueryBuilder::checkColumns(std::vector<std::string> columns) {
        std::vector<std::string> structure = this->database.getFileStructure();
        
        for (int i = 0; i < columns.size(); ++i) {
            if (!this->inVector(columns[i], structure)) {
                return false;
            }
        }
        
        return true;
    }
    
    std::vector<std::string> FdbrQueryBuilder::mapKeys(std::map<std::string, std::string> data) {
        std::vector<std::string> keys;
        
        for(std::map<std::string, std::string>::iterator itr = data.begin(); itr != data.end(); ++itr) {
            keys.push_back(itr->first);
        }
        
        return keys;
    }
    
    std::vector<std::string> FdbrQueryBuilder::mapValues(std::map<std::string, std::string> data) {
        std::vector<std::string> values;
        
        for(std::map<std::string, std::string>::iterator itr = data.begin(); itr != data.end(); ++itr) {
            values.push_back(itr->first);
        }
        
        return values;
    }

    std::vector<std::string> FdbrQueryBuilder::split(const std::string str, std::string delimiter, int limit) {
        std::vector<std::string> result;
        std::stringstream ss;
        ss.str(str);
        std::string item;
        int i = 0;
        
        while (getline(ss, item, *this->strToChar(delimiter))) {
            result.push_back(item);
            if (i == limit) break;
        }
        
        return result;
    }
    
    char * FdbrQueryBuilder::strToChar(std::string str) {
        char * writable = new char[str.size() + 1];
        std::copy(str.begin(), str.end(), writable);
        writable[str.size()] = '\0'; // don't forget the terminating 0
        
        return writable;
    }
    
    bool FdbrQueryBuilder::inVector(std::string needle, std::vector<std::string> &haystack) {
        return std::find(haystack.begin(), haystack.end(), needle) != haystack.end();
    }
    
}
