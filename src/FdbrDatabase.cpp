//
// Created by MakeHui on 16/12/5.
//

#include <iostream>
#include <sstream>

using namespace std;

#include "FdbrDatabase.h"

namespace FileDBR {

    FdbrDatabase::FdbrDatabase() {

    }

    FdbrDatabase::FdbrDatabase(string databasePath, string delimiter): databasePath(databasePath), delimiter(delimiter) {
        
    }

    FdbrDatabase::~FdbrDatabase() {
        this->closeFile();
    }
    
    void FdbrDatabase::setDatabasePath(string databasePath) {
        this->databasePath = databasePath;
    }
    
    string FdbrDatabase::getDatabasePath() {
        return this->databasePath;
    }
    
    void FdbrDatabase::setDelimiter(string str) {
        this->delimiter = str;
    }
    
    string FdbrDatabase::getDelimiter() {
        return this->delimiter;
    }
    
    bool FdbrDatabase::openFile(string fileName) {
        if (this->fs) this->closeFile();
        
        this->fs.open(this->databasePath + fileName);
        
        bool result = false;
        if (this->fs) result = true;
        
        return result;
    }
    
    void FdbrDatabase::closeFile() {
        this->fs.close();
    }
    
    bool FdbrDatabase::delFile(string fileName) {
        return 0 == remove(this->strToChar(this->databasePath + fileName));
    }
    
    bool FdbrDatabase::existFile(string fileName) {
        fstream fs(this->databasePath + fileName, ios::in);
        
        bool result = false;
        if (fs) result = true;
        
        fs.close();
        
        return result;
    }
    
    bool FdbrDatabase::createFile(string fileName) {
        fstream fs(this->databasePath + fileName, ios::out);
        
        bool result = false;
        if (fs) result = true;
        
        fs.close();
        
        return result;
    }
    
    vector<map<string, string>> FdbrDatabase::read(string fileName) {
        this->openFile(fileName);
        vector<map<string, string>> result;

        vector<string> headArray = this->head();

        if (headArray.size() == 0) {
            return result;
        }

        char row[1024];
        while(this->fs.getline(row, 1024)) {
            map<string, string> data;
            vector<string> rowArray = this->split(string(row), this->delimiter);

            for (int i = 0; i < rowArray.size(); ++i) {
                data[headArray[i]] = rowArray[i];
            }
            result.push_back(data);
        }
        
        return result;
    }
    
//    bool FdbrDatabase::write(string fileName) {
//        
//    }
//    
//    bool FdbrDatabase::change(string fileName) {
//        
//    }
//    
//    bool FdbrDatabase::del(string fileName) {
//        
//    }
    
    vector<string> FdbrDatabase::head(string fileName) {
        if (fileName != "") this->openFile(fileName);
        vector<string> result;
        
        char row[1024];
        this->fs.getline(row, 1024);
        result = this->split(string(row), this->delimiter);
        
        return result;
    }

    vector<string> FdbrDatabase::split(const string str, string delimiter, int limit) {
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

    char * FdbrDatabase::strToChar(string str) {
        char * writable = new char[str.size() + 1];
        std::copy(str.begin(), str.end(), writable);
        writable[str.size()] = '\0'; // don't forget the terminating 0

        return writable;
    }

}
