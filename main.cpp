#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string itoa(int n)
{
  string ret = "";

  while (n) {
    ret.push_back((n % 10) + '0');
    n /= 10;
  }

  return ret;
}

string transform(const string& s)
{
  int strLength = s.size();

  // Do not process words shorter than 3 chars, such as 'is' or 'a'
  if (strLength < 3) return s;

  // Process comma and period at the last position
  char finalChar = s[strLength - 1];
  if (finalChar == ',' || finalChar == '.') {
    --strLength;
  } else {
    finalChar = 0;
  }

  string ret = "";

  ret.push_back(s[0]);
  ret.append(itoa(strLength - 2));
  ret.push_back(s[strLength - 1]);

  if (finalChar != 0) {
    ret.push_back(finalChar);
  }

  return ret;
}

int main(int args, char* argv[]) 
{
  if (args < 2) {
    cout << "Please assign which file to be transformed." << endl;
    return 0;
  }

  string inFileName(argv[1]);

  ifstream ifs(inFileName.c_str(), ifstream::in);
  ofstream ofs(inFileName.append("_out").c_str());

  while (ifs.good()) {
    string line;

    getline(ifs, line);
    int lineSize = line.size();

    int start = 0;
    int end = line.find(' ');

    while (end != string::npos) {
      ofs << transform(line.substr(start, end - start)) << " ";

      start = end + 1;
      end = line.find(' ', start);
    }

    ofs << transform(line.substr(start, lineSize - start)) << endl;
  }

  ifs.close();
  ofs.close();

  return 0;
}
