//
// Created by MakeHui on 16/12/5.
//

#ifndef FILEDBR_FDBRDATABASE_H
#define FILEDBR_FDBRDATABASE_H

#include <fstream>
#include <string>
#include <vector>
#include <map>

#define FDBR_SPLIT_DELIMITER    ","

namespace FileDBR {
    class FdbrDatabase {
    public:
        FdbrDatabase();
        FdbrDatabase(std::string databasePath, std::string delimiter = FDBR_SPLIT_DELIMITER);

        ~FdbrDatabase();

        void setDatabasePath(std::string databasePath);
        std::string getDatabasePath();
        
        void setDelimiter(std::string str);
        std::string getDelimiter();

        std::vector<std::map<std::string, std::string>> getFileData();
        void setFileData(std::vector<std::map<std::string, std::string>> fileData);

        std::vector<std::string> getFileStructure();

        bool openFile(std::string fileName, std::ios_base::openmode openModel = std::ios_base::in|std::ios_base::out);
        void closeFile();
        bool delFile(std::string fileName);
        bool existFile(std::string fileName);
        bool createFile(std::string fileName);
        
        std::vector<std::map<std::string, std::string>> read(std::string fileName);
        bool write(std::string fileName);

        bool structure(std::string fileName);
        
    protected:
        std::vector<std::string> split(const std::string str, std::string delimiter, int limit = 512);

        char * strToChar(std::string str);

    public:
        std::map<std::string, std::fstream *> files;

    private:
        std::string databasePath;
        std::string databaseFile;
        std::string delimiter;

        std::vector<std::map<std::string, std::string>> fileData;
        std::vector<std::string> fileStructure;

        std::fstream fs;
        std::ios_base::openmode currentOpenMode;
    };
}


#endif //FILEDBR_FDBRDATABASE_H
