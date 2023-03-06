#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <math.h>


using namespace std;

double solveBeta(){
    double beta;
    double kelvin0 = 273.15, kelvin25 = 298.15;
    beta = (log(3))/((1/kelvin0)-(1/kelvin25));
    cout <<"Beta: " <<beta << endl;

    return beta;
}

double rNull(double tnull){
    double rnull, powerFactor;
    double kelvin0 = 273.15;
    powerFactor = solveBeta() * ((1/kelvin0)-(1/tnull));
    rnull = (3000) / (exp(powerFactor));
    cout <<"Ro: " <<rnull << endl;
    return rnull;
}

double rTemp(double tempIn, double tnull){
    double rT;
    double kelvinO = 273.15;
    double powerFactor = solveBeta() * ((1/tempIn)-(1/tnull));
    rT = rNull(tnull)*exp(powerFactor);
    cout <<"PowerFactor: " <<powerFactor << endl;
    cout << rT << endl;
    return rT;
}

int main(){
    
    double tnull = 293.15;
    cout << rTemp(228.15,tnull) << endl;

}