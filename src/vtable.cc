#include "util.h"
#include "vtable.h"

namespace vectordb {

VTable::VTable(const std::string& path)
    :path_(path) {
}

VTable::~VTable() {
    delete db_meta_;
    for (auto &kv : db_data_) {
        leveldb::DB *db = kv.second;
        delete db;
        //std::cout << "delete " << kv.first << " " << db << std::endl;
    }
}

bool
VTable::Load() {

    return true;
}

bool
VTable::CreateTable(const std::vector<std::string> &column_names) {
    if (column_names.size() < 1) {
        std::cout << "column_names error" << std::endl;
        return false;
    }

    std::set<std::string> column_set;
    for (auto &name : column_names) {
        column_set.insert(name);
    }

    if (column_names.size() != column_set.size()) {
        std::cout << "duplicate column" << std::endl;
        return false;
    }

    auto b = util::RecurMakeDir2(path_);
    assert(b);

    leveldb::Options options;
    options.create_if_missing = true;
    options.error_if_exists = true;

    auto s = leveldb::DB::Open(options, meta_path(), &db_meta_);
    assert(s.ok());

    for (auto &name : column_names) {
        leveldb::DB* db = nullptr;
        auto s = leveldb::DB::Open(options, column_path(name), &db);
        assert(s.ok());

        column_names_.push_back(name);
        db_data_.insert(std::pair<std::string, leveldb::DB*>(name, db));
    }

    return true;
}

bool
VTable::Insert(const std::vector<std::string> &key_values) {
    if (key_values.size() != ColumnNum()) {
        std::cout << "ColumnNum error" << std::endl;
        return false;
    }

    assert(key_values.size() >= 1);
    std::string key = key_values[0];

    for (int i = 0; i < ColumnNum(); ++i) {
        std::string column_name = column_names_[i];
        std::string value = key_values[i];

        auto it = db_data_.find(column_name);
        assert(it != db_data_.end());

        leveldb::DB* db = it->second;
        auto s = db->Put(leveldb::WriteOptions(), key, value);
        assert(s.ok());
    }

    return true;
}

bool
VTable::Get(const std::string &key, const std::string &column_name, std::string &value) const {
    value.clear();
    auto it = db_data_.find(column_name);
    assert(it != db_data_.end());
    leveldb::DB* db = it->second;

    auto s = db->Get(leveldb::ReadOptions(), key, &value);
    assert(s.ok());

    return true;
}

bool
VTable::Get(const std::string &key, std::vector<std::string> &key_values) const {
    key_values.clear();
    for (auto &name : column_names_) {
        auto it = db_data_.find(name);
        assert(it != db_data_.end());
        leveldb::DB* db = it->second;

        std::string value;
        auto s = db->Get(leveldb::ReadOptions(), key, &value);
        assert(s.ok());

        key_values.push_back(value);
    }

    return true;
}

bool
VTable::GetColumn(const std::string &column_name, std::vector<std::string> &values) const {
    values.clear();
    auto it = db_data_.find(column_name);
    assert(it != db_data_.end());
    leveldb::DB* db = it->second;

    leveldb::Iterator* db_it = db->NewIterator(leveldb::ReadOptions());
    for (db_it->SeekToFirst(); db_it->Valid(); db_it->Next()) {
        values.push_back(db_it->value().ToString());
    }
    assert(db_it->status().ok());
    delete db_it;

    return true;
}

bool
VTable::Dump() const {
    std::string line;
    for (auto &name : column_names_) {
        line.append(name);
        int space_count = CELL_LENGTH - name.length();
        for (int i = 0; i < space_count; ++i) {
            line.append(" ");
        }
    }
    std::cout << line << std::endl;

    assert(column_names_.size() >= 1);
    std::string key_name = column_names_[0];
    auto it = db_data_.find(key_name);
    assert(it != db_data_.end());
    leveldb::DB* db = it->second;
    assert(db);

    std::vector<std::string> keys;
    leveldb::Iterator* db_it = db->NewIterator(leveldb::ReadOptions());
    for (db_it->SeekToFirst(); db_it->Valid(); db_it->Next()) {
        keys.push_back(db_it->key().ToString());
    }
    assert(db_it->status().ok());
    delete db_it;

    for (auto &key : keys) {
        line.clear();
        std::vector<std::string> key_values;
        auto b = Get(key, key_values);
        assert(b);

        for (auto &value : key_values) {
            line.append(value);
            int space_count = CELL_LENGTH - value.length();
            for (int i = 0; i < space_count; ++i) {
                line.append(" ");
            }
        }
        std::cout << line << std::endl;
    }

    return true;
}

} // namespace vectordb
