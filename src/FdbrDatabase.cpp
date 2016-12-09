//
// Created by MakeHui on 16/12/5.
//

#include <sstream>

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
        if (remove(this->strToChar(this->databasePath + fileName))){
            return false;
        }
        
        return true;
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
        
        char row[1024];
        while(this->fs.getline(row, 1024)) {
            map<string, string> data;
            data["a"] = row;
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
        if (fileName == "") this->openFile(fileName);
        
        vector<string> result;
        
        char row;
        this->fs.getline(&row, 1024);
        
        result = this->split(string(&row), FDBR_SPLIT_DELIMITER);
        
        return result;
    }

    vector<string> FdbrDatabase::split(const string str, string delimiter, int limit) {
        vector<string> elems;
        string buf = delimiter; // Have a buffer string
        stringstream ss(str); // Insert the string into a stream

        vector<string> tokens; // Create vector to hold our words

        int i = 0;
        while (ss >> buf) {
            elems.push_back(buf);
            i++;
            if (i == limit) break;
        }
        return elems;
    }

    char * FdbrDatabase::strToChar(string str) {
        char * writable = new char[str.size() + 1];
        std::copy(str.begin(), str.end(), writable);
        writable[str.size()] = '\0'; // don't forget the terminating 0

        return writable;
    }

}
