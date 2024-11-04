#include<iostream>
#include<cassert>
#include<string>
using namespace std;
int f(int n) {
    if (n<0) throw "123";
    if (n>1) throw 12;
    if (n==0) throw 1.00;
    if (n==1) throw false;
    return 0;
}
int main(int argc, char *argv[]) {
try {
    f(1);
} catch (int v) {
    cout << "int" ;
} catch (double v) {
    cout << "double";
} catch (const char* v) {
    cout << "string";
} catch (...) {
    cout << "None of above";
}

return 0;
}