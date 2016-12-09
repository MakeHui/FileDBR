//
//  main.cpp
//  FileDBR
//
//  Created by MakeHui on 06/12/2016.
//  Copyright © 2016 MakeHui. All rights reserved.
//

#include <iostream>

#include "src/FdbrDatabase.h"
#include "src/FdbrQueryBuilder.h"

using namespace FileDBR;

int main(int argc, const char * argv[]) {

    FdbrDatabase database("/Users/MakeHui/Desktop/");
    
//    bool exist = database.existFile("test2.txt");
//    bool create = database.createFile("test2.txt");
//    bool open = database.openFile("test2.txt");
//    database.closeFile();
//    bool del = database.delFile("test2.txt");
    
    
    vector<map<string, string>> data = database.read("test2.txt");
    
    for (int i = 0; i < data.size(); i++) {
        cout << data[i]["a"] << endl;
    }
    
//    cout << "exist: " << exist << endl;
//    cout << "create: " << create << endl;
//    cout << "open: " << open << endl;
//    cout << "create: " << del << endl;
    
    cout << "Hello, World!" << endl;
    return 0;
}
