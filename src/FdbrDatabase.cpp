//
// Created by MakeHui on 16/12/5.
//

#include <sstream>

#include "FdbrDatabase.h"

//#define FDBR_SPLIT_PATTERN    ","

namespace FileDBR {

    FdbrDatabase::FdbrDatabase() {

    }

    FdbrDatabase::FdbrDatabase(string databasePath) {
        this->databasePath = databasePath;
    }

    FdbrDatabase::~FdbrDatabase() {

    }
    
    bool FdbrDatabase::existFile(string fileName) {
        fstream fs(fileName, ios::in);
        
        bool exist = false;
        if (fs) exist = true;
        
        fs.close();
        
        return exist;
    }
    
    bool FdbrDatabase::createFile(string fileName) {
        fstream fs(fileName, ios::out);
        
        bool success = false;
        if (fs) success = true;
        
        fs.close();
        
        return success;
    }

    vector<string> FdbrDatabase::split(const string str, string pattern, int limit) {
        vector<string> elems;
        string buf = pattern; // Have a buffer string
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

    void FdbrDatabase::setDatabasePath(string databasePath) {
        this->databasePath = databasePath;
    }

    string FdbrDatabase::getDatabasePath() {
        return this->databasePath;
    }

    bool FdbrDatabase::openFile(string fileName) {
        fstream *fs = new fstream(this->databasePath + fileName, ios::in|ios::out);

        if (*fs) {
            this->files[fileName] = fs;
            return true;
        }

        return false;
    }

}
