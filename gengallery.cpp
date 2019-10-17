#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include "dirlist.h"

using namespace std;

vector<string> imgs = {"beach1.jpg", "test"};

vector<std::string> split(std::string str, std::string token){
    vector<std::string>result;
    while(str.size()){
        size_t index = str.find(token);
        if(index!=std::string::npos){
            result.push_back(str.substr(0,index));
            str = str.substr(index+token.size());
            if(str.size()==0)result.push_back(str);
        }else{
            result.push_back(str);
            str = "";
        }
    }
    return result;
}

std::string slurp(std::string fname) {
  std::ifstream in(fname);
  std::stringstream sstr;
  sstr << in.rdbuf();
  return sstr.str();
}

int main() {
  vector<fileinfo> imgs = dirlist("images/*");
  for (int i=0; i<imgs.size(); i++) {
    string fname = imgs[i].name;
    if (fname.size() < 3) continue;
    system(("identify images/" + fname + " > info").c_str());
    string info = slurp("info");
    vector<string> parts = split(info, " ");
    vector<string> dim = split(parts[2], "x");
    if (i >0 ) cout << ",\n";
    cout << "{ src: 'https://mytj.pics/images/";
    cout << fname << "', w: " << dim[0] << ", h: " << dim[1] << "}";
    cout << std::flush;
  }

}
