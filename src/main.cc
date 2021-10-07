#include <iostream>
#include "vtable.h"

int
main(int argc, char **argv) {
    vectordb::VTable vt("./test_vtable");

    std::vector<std::string> column_names;
    column_names.push_back("name");
    column_names.push_back("birth");
    column_names.push_back("age");
    column_names.push_back("occupation");
    column_names.push_back("country");

    auto b = vt.CreateTable(column_names);
    assert(b);

    {
        std::vector<std::string> values;
        values.push_back("Alexander");
        values.push_back("BC 356.7.20");
        values.push_back("33");
        values.push_back("emperor");
        values.push_back("Macedonia");
        b = vt.Insert(values);
        assert(b);
    }

    {
        std::vector<std::string> values;
        values.push_back("Hannibal");
        values.push_back("BC 247");
        values.push_back("64");
        values.push_back("administrator");
        values.push_back("Carthage");
        b = vt.Insert(values);
        assert(b);
    }

    {
        std::vector<std::string> values;
        values.push_back("Caesar");
        values.push_back("BC 100.7.3");
        values.push_back("56");
        values.push_back("dictator");
        values.push_back("Rome");
        b = vt.Insert(values);
        assert(b);
    }

    {
        std::vector<std::string> values;
        values.push_back("Napoleon");
        values.push_back("AD 1769.8.5");
        values.push_back("52");
        values.push_back("emperor");
        values.push_back("France");
        b = vt.Insert(values);
        assert(b);
    }

    {
        std::cout << std::endl;
        auto b = vt.Dump();
        assert(b);
        std::cout << std::endl;
    }

    {
        std::cout << "test Get:" << std::endl;
        std::string value;
        auto b = vt.Get("Napoleon", "birth", value);
        assert(b);
        std::cout << "Napoleon birth: " << value;
        std::cout << std::endl;
        std::cout << std::endl;
    }

    {
        std::cout << "test Get:" << std::endl;
        std::vector<std::string> key_values;
        auto b = vt.Get("Napoleon", key_values);
        assert(b);
        std::cout << "Napoleon: ";
        for (auto &v : key_values) {
            std::cout << v << ", ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }

    {
        std::cout << "test GetColumn:" << std::endl;
        std::vector<std::string> values;
        auto b = vt.GetColumn("age", values);
        assert(b);
        std::cout << "age: ";
        for (auto &v : values) {
            std::cout << v << ", ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }

    return 0;
}
