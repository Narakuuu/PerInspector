#include "utils/read_file.h"

namespace monitor {
bool ReadFile::ReadLine(std::vector<std::string>* args) {
  std::string line;
  // getline context to line 
  std::getline(ifs_, line);
  if (ifs_.eof() || line.empty()) {
    return false;
  }

  // string to stringstream
  std::istringstream line_ss(line);
  while (!line_ss.eof()) {
    std::string word;
    // store in word split with space
    line_ss >> word;
    // word store in vector
    args->push_back(word);
  }
  return true;
}


}  // namespace monitor