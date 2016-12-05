//
// Created by MakeHui on 16/12/5.
//

#ifndef FILEDBR_FDBRDATABASE_H
#define FILEDBR_FDBRDATABASE_H

#include <fstream>
#include <string>

using namespace std;

namespace FileDBR {
    class FdbrDatabase {
    public:
        FdbrDatabase();

        FdbrDatabase(string databasePath);

        FdbrDatabase(string databasePath, string tableName);

        ~FdbrDatabase();

        void setTableNameR(string tableName);

        void setDatabasePathR(string databasePath);

        bool create();

        string retrieveRowR();

        string retrieveResultR();

        bool updateR();

        bool deleteR();

        int countR();

    protected:

    private:
        string databasePath;
        string tableName;
        ofstream DBR;
    };
}


#endif //FILEDBR_FDBRDATABASE_H
