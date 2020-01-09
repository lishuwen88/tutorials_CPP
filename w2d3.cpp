#include <iostream>
#include <fstream>
#include <chrono>
#include <memory>
#include <stdio.h>
#include <cstring>
#ifdef __linux__
#include <unistd.h>
#endif
using namespace std;
using namespace std::chrono;
const size_t sz = 512 * 1024 * 1024;
const int numiter = 20;
const size_t bufsize = 1024 * 1024;
int main(int argc, char**argv)
{
  unique_ptr<char[]> data(new char[sz]);
  unique_ptr<char[]> buf(new char[bufsize]);
  for (size_t p = 0; p < sz; p += 16) {
    memcpy(&data[p], "BINARY.DATA.....", 16);
  }
  unlink("file.binary");
  int64_t total = 0;
  if (argc < 2 || strcmp(argv[1], "fopen") != 0) {
    cout << "fstream mode\n";
    ofstream myfile("file.binary", ios::out | ios::binary);
    if (!myfile) {
      cerr << "open failed\n"; return 1;
    }
    myfile.rdbuf()->pubsetbuf(buf.get(), bufsize); // IMPORTANT
    for (int i = 0; i < numiter; ++i) {
      auto tm1 = high_resolution_clock::now();
      myfile.write(data.get(), sz);
      if (!myfile)
        cerr << "write failed\n";
      auto tm = (duration_cast<milliseconds>(high_resolution_clock::now() - tm1).count());
      cout << tm << " ms\n";
      total += tm;
    }
    myfile.close();
  }
  else {
    cout << "fopen mode\n";
    FILE* pFile = fopen("file.binary", "wb");
    if (!pFile) {
      cerr << "open failed\n"; return 1;
    }
    setvbuf(pFile, buf.get(), _IOFBF, bufsize); // NOT important
    auto tm1 = high_resolution_clock::now();
    for (int i = 0; i < numiter; ++i) {
      auto tm1 = high_resolution_clock::now();
      if (fwrite(data.get(), sz, 1, pFile) != 1)
        cerr << "write failed\n";
      auto tm = (duration_cast<milliseconds>(high_resolution_clock::now() - tm1).count());
      cout << tm << " ms\n";
      total += tm;
    }
    fclose(pFile);
    auto tm2 = high_resolution_clock::now();
  }
  cout << "Total: " << total << " ms, " << (sz*numiter * 1000 / (1024.0 * 1024 * total)) << " MB/s\n";
}
