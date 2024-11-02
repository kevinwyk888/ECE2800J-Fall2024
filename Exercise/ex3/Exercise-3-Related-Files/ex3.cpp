#include <iostream>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include "cipher.h"
using namespace std;

int main(int argc,char* argv[]) {
    bool e = false ,d = false ,h = false ,c = false ,s = false;
    if ( argc > 3 ) {
        cout << "Too many options!" << std::endl;
        return 0;
    }
    get_parameter(&e,&d,&h,&c,&s,argc,argv);
    if ( argc == 1 ) {
        cout << "No option!" << endl;
        return 0;
    }
    if (h) {
        if (argc > 2)  
            cout << "Invalid option!" << endl;
        else
            printHelp();
        return 0;
    }
    if (argc == 2) {
        if (e) work_encrypt(false);
        if (d) work_decrypt(false);
        if (c || s) cout << "Invalid option!" << endl;
        return 0;
    }
    if (argc == 3) {
        if ((e && d) || (c && s)) {
            cout << "Invalid option!" << endl;
            return 0;
        }
        if (e && c) work_encrypt(false);
        if (e && s) work_encrypt(true);
        if (d && c) work_decrypt(false);
        if (d && s) work_decrypt(true);
    }
    return 0;
}