#include "dirlist.h"
#include <string>
#include <vector>
#include <stdio.h>
#include <unistd.h>

using namespace std;

string workingdir() {
  char currpath[1024];
  getcwd(currpath, sizeof(currpath));
  //currpath[sizeof(currpath)-1] = '\0';
  printf("wd %s\n",currpath);
  return string(currpath);
}

vector<fileinfo> dirlist(string folder) {
  vector<fileinfo> files;
  std::string search_path = folder;
  if (folder.find("*") == std::string::npos)
    search_path += "/*.*";
  WIN32_FIND_DATA fd;
  //printf("search_path is %s\n",search_path.c_str());
  HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
  if(hFind != INVALID_HANDLE_VALUE) {
    do {
      fileinfo file;
      if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        file.isdir = true;
      else
        file.isdir = false;
      file.name = string(fd.cFileName);
      file.altname = string(fd.cAlternateFileName);
      file.fullpath = folder + "/" + file.name;
      file.size = (fd.nFileSizeHigh * (MAXDWORD+1)) + fd.nFileSizeLow;
      files.push_back(file);
    } while (::FindNextFile(hFind, &fd));
    ::FindClose(hFind);
  }
  return files;
}
