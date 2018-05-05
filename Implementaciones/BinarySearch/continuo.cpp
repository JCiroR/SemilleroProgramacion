#include <cstdio>
#include <iostream>
#include <cmath>

using namespace std;

const double err = 0.01;

double eval(double x){
    return x;
}

int main() {
    double lo = 0, hi = 1000, target;
    int it = 20;
    scanf("%lf", &target);
    
    while(it--) {
        double mid = lo + (hi - lo)/2;
        if(target <= eval(mid))
            hi = mid;
        else lo = mid;
    }

    printf("%.12lf\n", lo);
}