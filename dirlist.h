#pragma once

#include <windows.h>
#include <string>
#include <vector>

using namespace std;

struct fileinfo {
  bool isdir;
  std::string name;
  std::string altname;
  std::string fullpath;
  unsigned long size;
};

std::string workingdir();

std::vector<fileinfo> dirlist(std::string folder);
