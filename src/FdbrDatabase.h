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

namespace FileDBR {
    class FdbrDatabase {
    public:
        FdbrDatabase();
        FdbrDatabase(string databasePath);

        ~FdbrDatabase();

        void setDatabasePath(string databasePath);
        string getDatabasePath();

        bool openFile(string fileName);
        void closeFile(string fileName);
        void deleteFile(string fileName);
        void read(string fileName);
        void write(string fileName);
        void change(string fileName);
        void del(string fileName);

    protected:
        /**
         * string split to array
         *
         * @param str
         * @param pattern
         * @param limit
         *
         * @return vector<string>
         */
        vector<string> split(const string str, string pattern, int limit = 512);

        /**
         * string to char
         * @param str
         * @return
         */
        char * strToChar(string str);

    public:
        map<string, fstream *> files;

    private:
        string databasePath;
    };
}


#endif //FILEDBR_FDBRDATABASE_H
