
# [FileDBR](http://huyaohui.com/2016/12/26/A-simple-CPP-framework-based-on-file/)

A simple C++ framework based on file.

## Get Started

### Use

Drag `src/*` to your projects

```c++
#include "FdbrQueryBuilder.h"

using namespace FileDBR;

int main(int argc, const char * argv[]) {
    FdbrQueryBuilder queryBuilder("/Users/MakeHui/Desktop/");
}
```

### Definition

Create table and delete table

#### createTable

Create table

> bool createTable(string table, vector\<string> columns)
- table: The table name
- columns: create column name
- 
- return: bool

```c++
bool data = queryBuilder.createTable("tablename.fdbr", {"field1", "field2", "field3"});
```

#### deleteTable

Delete table

> bool createTable(string table)
- table: The table name
- 
- return: bool

```c++
bool data = queryBuilder.deleteTable("tablename.fdbr");
```

### Where

In the basic use. You can use symbols to filter parameters.

#### equality

field1 = 123

```c++
vector<map<string, string>> data = queryBuilder.select("tablename.fdbr", {"field1", "field2"}, {{"field1", "123"}});
// or
vector<map<string, string>> data = queryBuilder.select("tablename.fdbr", {"field1", "field2"}, {{"field1 =", "123"}});
```

#### not equal

field1 != 123

```c++
vector<map<string, string>> data = queryBuilder.select("tablename.fdbr", {"field1", "field2"}, {{"field1 !=", "123"}});
```

#### greater

field1 > 123

```c++
vector<map<string, string>> data = queryBuilder.select("tablename.fdbr", {"field1", "field2"}, {{"field1 >", "123"}});
```

#### lesser

field1 < 123

```c++
vector<map<string, string>> data = queryBuilder.select("tablename.fdbr", {"field1", "field2"}, {{"field1 <", "123"}});
```

#### greater or equal

field1 >= 123

```c++
vector<map<string, string>> data = queryBuilder.select("tablename.fdbr", {"field1", "field2"}, {{"field1 >=", "123"}});
```

#### lesser or equal

field1 <= 123

```c++
vector<map<string, string>> data = queryBuilder.select("tablename.fdbr", {"field1", "field2"}, {{"field1 <=", "123"}});
```

#### like

field1 like 123

```c++
vector<map<string, string>> data = queryBuilder.select("tablename.fdbr", {"field1", "field2"}, {{"field1 ~", "123"}});
```

#### not like

field1 not like 123

```c++
vector<map<string, string>> data = queryBuilder.select("tablename.fdbr", {"field1", "field2"}, {{"field1 !~", "123"}});
```

### Query

Some to the query method in common use.

#### select

Select data from table

> vector\<map\<string, string>> select(string table, vector\<string> columns = {}, map\<string, string> where = {}, map\<string, string> order = {})
- table: The table name
- columns: The target columns of data will be fetched
- where: Query conditions
- order: Sorting conditions
- 
- return: vector\<map\<string, string>>

```c++
vector<map<string, string>> data = queryBuilder.select("tablename.fdbr", {"field1", "field2"}, {{"field1", "123"}}, {{"field1", "DESC"}})
```

#### insert

Insert new records in table

> bool insert(string table, map\<string, string> datas)
- table: The table name
- datas: The data will be inserted into table
- 
- return: bool

```c++
bool data = queryBuilder.insert("tablename.fdbr", {{"field1", "123"}, {"field3", "456"}});
```

#### update

Modify data in table

> unsigned int update(string table, map\<string, string> datas, map\<string, string> where = {})
- table: The table name
- datas: The data that will be modified
- where: Query conditions
- 
- return: The number of rows affected

```c++
unsigned int data = queryBuilder.update("tablename.fdbr", {{"field1", "111"}}, {{"field1", "100"}});
```

#### del

Delete data from table

> unsigned int del(string table, map\<string, string> where = {})
- table: The table name
- where: Query conditions
- 
- return: The number of rows affected

```c++
unsigned int data = queryBuilder.del("tablename.fdbr", {{"field1", "100"}});
```

#### get

Get only one record from table

> map\<string, string> get(string table, vector\<string> columns = {}, map\<string, string> where = {}, map\<string, string> order = {})
- table: The table name
- columns: The target columns of data will be fetched
- where: Query conditions
- order: Sorting conditions
- 
- return map\<string, string>

```c++
map<string, string> data = queryBuilder.get("tablename.fdbr", {"field2"}, {{"field1", "123"}}, {{"field1", "ASC"}})
```

#### has

Determine whether the target data existed

> bool has(string table, map\<string, string> where = {})
- table: The table name
- where: Query conditions
- 
- return: bool

```c++
bool data = queryBuilder.has("tablename.fdbr", {{"field1", "100"}});
```

#### count

Counts the number of rows

> unsigned int count(string table, map\<string, string> where = {});
- table: The table name
- where: Query conditions
- 
- return: unsigned int

```c++
unsigned int data = queryBuilder.count("tablename.fdbr", {{"field1", "100"}});
```

#### max

Get the maximum value for the column and support string

> string max(string table, string column, map\<string, string> where = {})
- table: The table name
- column: The target column will be calculated
- where: Query conditions
- 
- return: string

```c++
string data = queryBuilder.max("tablename.fdbr", "field2", {{"field1", "100"}});
```

#### min

Get the minimum value for the column and support string

> string min(string table, string column, map\<string, string> where = {});
- table: The table name
- column: The target column will be calculated
- where: Query conditions
- 
- return: string

```c++
string data = queryBuilder.min("tablename.fdbr", "field2", {{"field1", "100"}});
```

#### avg

Get the average value for the column

> long double avg(string table, string column, map\<string, string> where = {});
- table: The table name
- column: The target column will be calculated
- where: Query conditions
- 
- return: long double

```c++
long double data = queryBuilder.avg("tablename.fdbr", "field2", {{"field1", "100"}});
```

#### sum

Get the total value for the column

> long double sum(string table, string column, map\<string, string> where = {});
- table: The table name
- column: The target column will be calculated
- where: Query conditions
- 
- return: long double

```c++
long double data = queryBuilder.sum("tablename.fdbr", "field2", {{"field1", "100"}});
```

## License

FileDBR is under the LGPLv2.1 license.
