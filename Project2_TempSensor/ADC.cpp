#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <sstream>
#include <cstring>


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

double hexToDec(char hexNumber[]) 
{
    double decimalNumber = 0;
    int len = strlen(hexNumber);
    for (int base = 1, i=(len-1); i>=0; i--, base *= 16) 
    {
       // Get the hex digit in upper case 
       char digit = toupper(hexNumber[i]);
       if ( digit >= '0' && digit <='9' ) 
       {
          decimalNumber += (digit - 48)*base;
       }
       else if ( digit >='A' && digit <='F' ) 
       {
          decimalNumber += (digit - 55)*base;
       }
    }
    return decimalNumber;
}

double ADCconvert(double ADC)
{
    double voltage;
    cout << "Input ADC Value in Decimal: " << ADC << endl;
    voltage = ADC * (5.00/65535.00);
    cout << "Voltage: " << voltage << endl;

    //calculate current over resistor
    double current;
    current = (5.00-voltage)/1000.00;
    cout << "Current: " << current << endl;

    //calculate resistance
    double resistance;
    resistance = voltage/current;
    cout << "Resistnace: " << resistance << endl;

    return resistance;

}

void helpCMD()
{
  cout<<"\nLists of possible commands: \n"
      <<"* help            - displays the lists of commands \n"
      <<"* res            - Resistance/Temperature Operations"
      <<"* adc            - ADC Operations \n"
      <<"* exit            - closes the program"<<endl;
}

int main(){
    string cmd, tempIn;

    double rVal, tempOut;
    double tnull = 293.15;

    do{
        cout<<"\n[CMD] : ";
        getline(cin, cmd);

        stringstream cc(cmd);

        if (cmd == "help")
        {
            helpCMD();
        }
        else if (cmd == "res")
        {
            cout << "Input Temperature in Kelvin: ";
            getline(cin, tempIn);

            cout << "T_in = " << stod(tempIn) << " K\n";
            cout << "To = " << tnull << " K\n";
            cout << "Ro = " << rNull(tnull) << endl;
            cout << "β = " << solveBeta() << endl;
            cout << "==========================\n";
            rVal = rTemp(stod(tempIn),tnull);
        }
        else if (cmd == "adc")
        { 
            char hexNumber[80];
            cout << "Enter hexadecimal number: ";
            cin >> hexNumber;

            double decValue = hexToDec(hexNumber);

            cout << hexNumber << " in decimal format = " << decValue << "\n";
            double resistancevalue = ADCconvert(decValue);
            //replace rVal with ADC resistance calc
            tempOut = (solveBeta()*tnull)/(((log(resistancevalue/rNull(tnull)))*tnull)+solveBeta());
            cout << "T_out = " << tempOut << " K\n";
        
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
