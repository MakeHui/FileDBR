//
//  main.cpp
//  FileDBR
//
//  Created by MakeHui on 06/12/2016.
//  Copyright © 2016 MakeHui. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "src/FdbrDatabase.h"
#include "src/FdbrQueryBuilder.h"

using namespace FileDBR;
using namespace std;

int main(int argc, const char * argv[]) {
    map<string, string>::iterator itr;
    
    FdbrQueryBuilder queryBuilder("/Users/MakeHui/Desktop/");
    string tableName = "text.txt";
    
    cout << "--------createTable start----------" << endl;
    bool createTable = queryBuilder.createTable(tableName, {"a", "b", "c"});
    cout << createTable << endl;
    
    cout << "--------insert start----------" << endl;
    bool insert = queryBuilder.insert(tableName, {{"a", "223"}, {"b", "bbb"}, {"c", "ccc"}});
    cout << insert << endl;
    
    cout << "--------update start----------" << endl;
    int updateCount = queryBuilder.update(tableName, {{"b", "update"}}, {{"b", "bbb"}});
    cout << updateCount << endl;
    
    cout << "--------select start----------" << endl;
    vector<map<string, string>> selectData = queryBuilder.select(tableName, {"a", "b"}, {{"b", "update"}}, {{"b", "desc"}});
    for (int i = 0; i < selectData.size(); ++i) {
        for (itr = selectData[i].begin(); itr != selectData[i].end(); ++itr) {
            cout << itr->second << " ";
        }
        cout << endl;
    }
    
    cout << "--------get start----------" << endl;
    map<string, string> getData = queryBuilder.get(tableName, {"a", "b"}, {{"b", "update"}}, {{"b", "desc"}});
    for (itr = getData.begin(); itr != getData.end(); ++itr) {
        cout << itr->second << " ";
    }
    cout << endl;
    
    cout << "--------get start----------" << endl;
    bool has = queryBuilder.has(tableName, {{"a", "123"}});
    cout << has << endl;
    
    cout << "--------count start----------" << endl;
    unsigned int count = queryBuilder.count(tableName, {{"a", "223"}});
    cout << count << endl;
    
    cout << "--------max start----------" << endl;
    string max = queryBuilder.max(tableName, "a", {{"a ~", "2"}});
    cout << max << endl;
    
    cout << "--------min start----------" << endl;
    string min = queryBuilder.min(tableName, "a", {{"a !~", "4"}});
    cout << min << endl;
    
    cout << "--------avg start----------" << endl;
    long double avg = queryBuilder.avg(tableName, "a", {{"a", "223"}});
    cout << avg << endl;
    
    cout << "--------sum start----------" << endl;
    long double sum = queryBuilder.sum(tableName, "a", {{"a !=", "123"}});
    cout << sum << endl;
    
    cout << "--------delete start----------" << endl;
    int delCount = queryBuilder.del(tableName, {{"b", "update"}});
    cout << delCount << endl;
    
    cout << "--------deleteTable start----------" << endl;
    bool deleteTable = queryBuilder.deleteTable(tableName);
    cout << deleteTable << endl;
    
    
    cout << "Hello, World!" << endl;
    return 0;
}
