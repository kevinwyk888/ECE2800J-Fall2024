#include "cipher.h"
#include <iostream>
#include <string>
#include <getopt.h>
using namespace std;

void printHelp() {
  cout << "Encrypt or decrypt a message using the Polybius Square cipher.\n"
       << "Usage: ./ex3 <command> [outputMode]\n"
       << "Commands:\n"
       << "\t-e, --encrypt\tEncrypt a message\n"
       << "\t-d, --decrypt\tDecrypt a message\n"
       << "Output modes:\n"
       << "\t-c, --compact\tProcess the message without spaces\n"
       << "\t-s, --sparse\tProcess the message with spaces" << endl;
}

void get_parameter(bool* e, bool* d, bool* h, bool* c, bool* s, int argc, char* argv[]) {
  int opt=0;int option_index = 0;
  opterr = 0; 
    static struct option long_options[] = {
        {"encrypt", no_argument, 0, 'e'},
        {"decrypt", no_argument, 0, 'd'},
        {"help", no_argument, 0, 'h'},
        {"compact", no_argument, 0, 'c'},
        {"sparse", no_argument, 0, 's'},
        {0, 0, 0, 0}
    };
    while ((opt = getopt_long(argc, argv, "edhcs", long_options, &option_index)) != -1) {
        switch (opt) {
            case 'h':
                *h = true;
                break;
            case 'e':
                *e = true;
                break;
            case 'd':
                *d = true;
                break;
            case 'c':
                if (!*e && !*d) {
                  cout << "Invalid option!" << endl;
                  exit(0);
                }
                *c = true;
                break;
            case 's':
              if (!*e && !*d) {
                  cout << "Invalid option!" << endl;
                  exit(0);
                }
                *s = true;
                break;
            case '?': 
                cout << "Invalid option!" << endl;
                exit(0);
            default:
                abort();
        }
    }
}
void work_encrypt(bool compact_sparse) {
  string input;
  getline(cin,input);
  for (size_t k=0;k<input.length();k++) {
    char c=input[k];
    if (c==' ') cout << "000";
    if ('A'<= c && c<='Z') cout << "1";
    if ('a'<=c && c<='z') cout << "2";
    if (c == 'j' || c == 'J') cout << "00";
    else 
      for (int i=0;i<5;i++)
        for (int j=0;j<5;j++)
          if (c == uppercaseSquare[i][j] || c == lowercaseSquare[i][j]) 
            cout << i+1 << j+1;
    if (compact_sparse) cout <<" ";
  }
}

void work_decrypt(bool compact_sparse){
  int group;
  if (compact_sparse) group=4;
  else group=3;
  string input;
  getline(cin,input);
  for (size_t i=0; i<input.length(); i+=group) {
    string part = input.substr(i, group);
    if (part[0] == '0') cout << ' ';
    if (part[0] == '1') cout << uppercaseSquare[part[1]-49][part[2]-49];
    if (part[0] == '2') cout << lowercaseSquare[part[1]-49][part[2]-49];
  }
}