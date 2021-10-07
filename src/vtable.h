#ifndef __VTABLE_H__
#define __VTABLE_H__

#include <cstdio>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <leveldb/db.h>

namespace vectordb {

class VTable {

#define CELL_LENGTH 20

  public:
    VTable(const std::string& path);
    ~VTable();
    VTable(const VTable&) = delete;
    VTable& operator=(const VTable&) = delete;

    std::string meta_path() const {
        return path_ + "/meta";
    }

    std::string column_path(const std::string& column_name) const {
        return path_ + "/column_" + column_name;
    }

    size_t ColumnNum() const {
        return column_names_.size();
    }

    bool Load();
    bool CreateTable(const std::vector<std::string> &column_names);
    bool Insert(const std::vector<std::string> &key_values);
    bool Get(const std::string &key, const std::string &column_name, std::string &value) const;
    bool Get(const std::string &key, std::vector<std::string> &key_values) const;
    bool GetColumn(const std::string &column_name, std::vector<std::string> &values) const;
    bool Dump() const;

  private:
    std::vector<std::string> column_names_;
    std::string path_;
    leveldb::DB* db_meta_;
    std::map<std::string, leveldb::DB*> db_data_;
};

} // namespace vectordb

#endif
