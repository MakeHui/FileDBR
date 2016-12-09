//
// Created by MakeHui on 16/12/5.
//

#ifndef FILEDBR_FDBRDATABASE_H
#define FILEDBR_FDBRDATABASE_H

#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

#define FDBR_SPLIT_DELIMITER    "┋"

namespace FileDBR {
    class FdbrDatabase {
    public:
        FdbrDatabase();
        FdbrDatabase(string databasePath, string delimiter = FDBR_SPLIT_DELIMITER);

        ~FdbrDatabase();

        void setDatabasePath(string databasePath);
        string getDatabasePath();
        
        void setDelimiter(string str);
        string getDelimiter();

        bool openFile(string fileName);
        void closeFile();
        bool delFile(string fileName);
        bool existFile(string fileName);
        bool createFile(string fileName);
        
        vector<map<string, string>> read(string fileName);
        bool write(string fileName);
        bool change(string fileName);
        bool del(string fileName);

        vector<string> head(string fileName = "");
        
    protected:
        /**
         * string split to array
         */
        vector<string> split(const string str, string delimiter, int limit = 512);

        /**
         * string to char
         */
        char * strToChar(string str);

    public:
        map<string, fstream *> files;

    private:
        string databasePath;
        string delimiter;
        
        fstream fs;
    };
}


#endif //FILEDBR_FDBRDATABASE_H
