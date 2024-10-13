#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>

bool judge_Triangle(int n) {
    //Use mathmatical way to test.
    int x=sqrt(2*n); 
    return x*(x+1)==2*n;
}
bool judge_Power(int n) {
    // use loops to solve
    for (int i=2;i<=sqrt(n);i++)
        for (int j=2;pow(i,j)<=n;j++)
            if (pow(i,j)==n) return true;
    return false;
}
bool judge_squares(int n) {
    //use loops to solve
    for (int i=1;i<=sqrt(n);i++) {
        int sum=0;
        for (int j=i;sum<n;j++) {
            sum+=j*j;
            if (sum == n) return true;
        }
    }
    return false;
}
bool judge_abundant(int n) {
    //use loops to solve and note some details
    int sum=1;
    for (int i=2;i<=sqrt(n);i++)
        if (n%i==0) {
            sum+=i;
            if (i*i!=n) sum+=n/i;
        }
    return sum>n;
}


int main() {
    int n, opt;
    bool flag;
    // it seems to be convenient to use do/while
    do {
        printf("Please enter the integer and the test choice: ");
        scanf("%d %d", &n, &opt);
    } while (n<0 || n>1e8 || opt<1 || opt>4);
    // use switch to do multiple judgement 
    switch (opt) {
        case 1:
            flag = judge_Triangle(n);
            break;
        case 2:
            flag = judge_Power(n);
            break;
        case 3:
            flag = judge_squares(n);
            break;
        case 4:
            flag = judge_abundant(n);
            break;
        default:
            break;
    }
    // output the final result
    printf("%s",flag?"Pass":"Fail");
    return 0;
}