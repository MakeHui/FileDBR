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
        this->fileStructure.clear();
        this->fileData.clear();
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
    
    bool FdbrDatabase::openFile(string fileName, ios_base::openmode openModel) {
        if (this->databaseFile == fileName && this->currentOpenMode == openModel && this->fs) {
            return true;
        }

        if (this->fs) {
            this->closeFile();
        }

        this->fs.open(this->databasePath + fileName, openModel);
        this->currentOpenMode = openModel;

        bool result = false;
        if (this->fs) {
            result = true;
        }

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
        if (fs) {
            fs.close();
            result = true;
        }
        
        return result;
    }
    
    bool FdbrDatabase::createFile(string fileName) {
        fstream fs(this->databasePath + fileName, ios::out);
        
        bool result = false;
        if (fs) {
            fs.close();
            result = true;
        }
        
        return result;
    }
    
    vector<map<string, string>> FdbrDatabase::read(string fileName) {
        if (this->databaseFile == fileName && this->fileData.size() > 0) {
            return this->fileData;
        }

        vector<map<string, string>> result;

        if (!this->structure(fileName)) {
            return result;
        }

        if (!this->openFile(fileName)){
            return result;
        }

        string row;
        int index = 0;
        while(!this->fs.eof()) {
            index = index + 1;
            if (index == 1) {
                getline(this->fs, row);
                continue;
            }
            map<string, string> data;
            vector<string> rowArray;

            getline(this->fs, row);
            if (row.empty()) {
                continue;
            }
            rowArray = this->split(row, this->delimiter);
            for (int i = 0; i < rowArray.size(); ++i) {
                data[this->fileStructure[i]] = rowArray[i];
            }
            result.push_back(data);
        }

        this->fileData = result;
        
        return result;
    }
    
    bool FdbrDatabase::write(string fileName) {
        if (this->fileData.size() == 0) {
            return false;
        }

        if (!this->openFile(fileName, ios_base::out|ios_base::trunc)) {
            return false;
        }

        string row = "";
        for (int i = 0; i < this->fileStructure.size(); ++i) {
            row = row + this->fileStructure[i] + this->delimiter;
        }
        row = row + "\n";
        this->fs.write(row.c_str(), row.size());

        for (int i = 0; i < this->fileData.size(); ++i) {
            map<string, string>::iterator itr;
            row = "";
            for (itr = this->fileData[i].begin(); itr != this->fileData[i].end(); ++itr) {
                row = row + itr->second + this->delimiter;
            }
            
            if (i != this->fileData.size() - 1) {
                row = row + "\n";
            }
            this->fs.write(row.c_str(), row.size());
        }

        return true;
    }
    
    bool FdbrDatabase::structure(string fileName) {
        if (!this->openFile(fileName)) return false;
        
        string row;
        getline(this->fs, row);

        if (row.size() == 0) return false;

        this->fileStructure = this->split(row, this->delimiter);
        
        return this->fileStructure.size() != 0;
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
