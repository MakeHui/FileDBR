//
// Created by MakeHui on 16/12/5.
//

#include "FdbrDatabase.h"

#include <iostream>

using namespace std;

namespace FileDBR {


    FdbrDatabase::FdbrDatabase() {

    }

    FdbrDatabase::FdbrDatabase(string databasePath) {
        this->databasePath = databasePath;
    }

    FdbrDatabase::FdbrDatabase(string databasePath, string tableName) {
        this->databasePath = databasePath;
        this->tableName = tableName;
    }

    FdbrDatabase::~FdbrDatabase() {

    }

    void FdbrDatabase::setTableNameR(string tableName) {
        this->tableName = tableName;
    }

    void FdbrDatabase::setDatabasePathR(string databasePath) {
        this->databasePath = databasePath;
    }

    bool FdbrDatabase::create() {

    }

    string FdbrDatabase::retrieveRowR() {

    }

    string FdbrDatabase::retrieveResultR() {

    }

    bool FdbrDatabase::updateR() {

    }

    bool FdbrDatabase::deleteR() {

    }

    int FdbrDatabase::countR() {

    }
}
