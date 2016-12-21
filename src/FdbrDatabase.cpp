//
// Created by MakeHui on 16/12/5.
//

#include <iostream>
#include <sstream>

#include "FdbrDatabase.h"

namespace FileDBR {

    FdbrDatabase::FdbrDatabase() {

    }

    FdbrDatabase::FdbrDatabase(std::string databasePath, std::string delimiter): databasePath(databasePath), delimiter(delimiter) {
        
    }

    FdbrDatabase::~FdbrDatabase() {
        this->closeFile();
        this->fileStructure.clear();
        this->fileData.clear();
    }
    
    void FdbrDatabase::setDatabasePath(std::string databasePath) {
        this->databasePath = databasePath;
    }

    std::string FdbrDatabase::getDatabasePath() {
        return this->databasePath;
    }
    
    void FdbrDatabase::setDelimiter(std::string str) {
        this->delimiter = str;
    }

    std::string FdbrDatabase::getDelimiter() {
        return this->delimiter;
    }

    std::vector<std::map<std::string, std::string>> FdbrDatabase::getFileData() {
        return this->fileData;
    }

    void FdbrDatabase::setFileData(std::vector<std::map<std::string, std::string>> fileData) {
        this->fileData = fileData;
    }

    std::vector<std::string> FdbrDatabase::getFileStructure() {
        return this->fileStructure;
    }

    bool FdbrDatabase::openFile(std::string fileName, std::ios_base::openmode openModel) {
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
    
    bool FdbrDatabase::delFile(std::string fileName) {
        return 0 == remove(this->strToChar(this->databasePath + fileName));
    }
    
    bool FdbrDatabase::existFile(std::string fileName) {
        std::fstream fs(this->databasePath + fileName, std::ios::in);
        
        bool result = false;
        if (fs) {
            fs.close();
            result = true;
        }
        
        return result;
    }
    
    bool FdbrDatabase::createFile(std::string fileName) {
        std::fstream fs(this->databasePath + fileName, std::ios::out);
        
        bool result = false;
        if (fs) {
            fs.close();
            result = true;
        }
        
        return result;
    }

    std::vector<std::map<std::string, std::string>> FdbrDatabase::read(std::string fileName) {
        if (this->databaseFile == fileName && this->fileData.size() > 0) {
            return this->fileData;
        }

        std::vector<std::map<std::string, std::string>> result;

        if (!this->structure(fileName)) {
            return result;
        }

        if (!this->openFile(fileName)){
            return result;
        }

        std::string row;
        int index = 0;
        while(!this->fs.eof()) {
            index = index + 1;
            if (index == 1) {
                getline(this->fs, row);
                continue;
            }
            std::map<std::string, std::string> data;
            std::vector<std::string> rowVector;

            getline(this->fs, row);
            if (row.empty()) {
                continue;
            }
            rowVector = this->split(row, this->delimiter);
            for (int i = 0; i < rowVector.size(); ++i) {
                data[this->fileStructure[i]] = rowVector[i];
            }
            result.push_back(data);
        }

        this->fileData = result;
        
        return result;
    }
    
    bool FdbrDatabase::write(std::string fileName) {
        if (this->fileData.size() == 0) {
            return false;
        }

        if (!this->openFile(fileName, std::ios_base::out|std::ios_base::trunc)) {
            return false;
        }

        std::string row = "";
        for (int i = 0; i < this->fileStructure.size(); ++i) {
            row = row + this->fileStructure[i] + this->delimiter;
        }
        row = row + "\n";
        this->fs.write(row.c_str(), row.size());

        for (int i = 0; i < this->fileData.size(); ++i) {
            std::map<std::string, std::string>::iterator itr;
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
    
    bool FdbrDatabase::structure(std::string fileName) {
        if (!this->openFile(fileName)) return false;

        std::string row;
        getline(this->fs, row);

        if (row.size() == 0) return false;

        this->fileStructure = this->split(row, this->delimiter);
        
        return this->fileStructure.size() != 0;
    }

    std::vector<std::string> FdbrDatabase::split(const std::string str, std::string delimiter, int limit) {
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

    char * FdbrDatabase::strToChar(std::string str) {
        char * writable = new char[str.size() + 1];
        std::copy(str.begin(), str.end(), writable);
        writable[str.size()] = '\0'; // don't forget the terminating 0

        return writable;
    }

}
