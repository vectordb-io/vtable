#ifndef __UTIL_H__
#define __UTIL_H__

#include <ctime>
#include <vector>
#include <string>

namespace vectordb {

namespace util {

bool RemoveDir(const std::string &path);
bool ChildrenOfDir(const std::string &path, std::vector<std::string> &children_paths, std::vector<std::string> &children_names);
std::string LocalTimeString(time_t t);
unsigned int RSHash(const char *str);
void Split(const std::string &s, char separator, std::vector<std::string> &sv, const std::string ignore = "");

void ToLower(std::string &str);
bool DirOK(const std::string &path);
bool MakeDir(const std::string &path);
bool RecurMakeDir(const std::string &path);
bool RecurMakeDir2(const std::string &path);

} // namespace util

} // namespace vectordb

#endif
