#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <sstream>


using namespace std;

double solveBeta(){
    double beta;
    double kelvin0 = 273.15, kelvin25 = 298.15;
    beta = (log(3))/((1/kelvin0)-(1/kelvin25));
    //cout <<"Beta: " <<beta << endl;
    return beta;
}

double rNull(double tnull){
    double rnull, powerFactor;
    double kelvin0 = 273.15;
    powerFactor = solveBeta() * ((1/kelvin0)-(1/tnull));
    rnull = (3000.0) / (exp(powerFactor));
    //cout <<"Ro: " <<rnull << endl;
    return rnull;
}

double rTemp(double tempIn, double tnull){
    double rT;
    double kelvinO = 273.1500;
    double powerFactor = solveBeta()*((1.000/tempIn)-(1.000/tnull))*1.000;
    rT = rNull(tnull)*1.0000*exp(powerFactor);
    //cout <<"PowerFactor: " <<powerFactor << endl;
    //cout <<"Ro: " <<rNull(tnull) << endl;
    cout << "R(" << tempIn << ")= "<<rT <<endl;
    return rT;
}

void helpCMD(){
    cout << "Insert Help dialogue" << endl;
}

int main(){
    string cmd;

    double tempIn;
    double tnull = 293.15;

    do{
        cout<<"\n[CMD] : ";
        getline(cin, cmd);

        stringstream cc(cmd);

        if (cmd == "help")
        {
            helpCMD();
        }
        else if (cc >> tempIn)
        { 
            cout << "T = " << stod(cmd) << " K\n";
            cout << "To = " << tnull << " K\n";
            cout << "Ro = " << rNull(tnull) << endl;
            cout << "β = " << solveBeta() << endl;
            cout << "==========================\n";
            rTemp(stod(cmd),tnull); 
        }
        else if (cmd == "exit")
        {
            cout << "Exiting..." << endl;
        }
        else cout<<"Invalid Command. " <<  
        "Type 'help' for a list of commands."<<endl;
    }
    while (cmd != "exit");

}