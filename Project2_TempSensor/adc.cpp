//ENGG 126
//Project 2: Matrix Multiplication Speed Test
//by: Iris Carson, Antonio Castro, and Joshua Kempis
//--------------------------------------------------------------------
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <sstream>
#include <cstring>
#include <bits/stdc++.h>

using namespace std;

double Celsius2Kelvin(double temp_celsius)
{
  return temp_celsius + 273.15;
}

double solveBeta(double T_0)
{
  double N = ((1/273.15)-(1/T_0))-((1/298.15)-(1/T_0));
  double beta = log(3000/1000)/N;
  //cout <<"Beta: " <<beta << endl;
  return beta;
}

double rNull(double T_0){	
  double beta = solveBeta(T_0);
  double R_0 = 3000/ (exp(beta*((1/273.15)-(1/T_0))));
  //cout <<"Ro: " <<R_0 << endl;
  return R_0;
}

double rTemp(double tempIn, double T_0){
  double rT;
  double kelvinO = 273.1500;
  double powerFactor = solveBeta(T_0)*((1.000/tempIn)-(1.000/T_0))*1.000;
  rT = rNull(T_0)*1.0000*exp(powerFactor);
  //cout <<"PowerFactor: " <<powerFactor << endl;
  //cout <<"Ro: " <<rNull(T_0) << endl;
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
  double T_0 = Celsius2Kelvin(20); //293.15; // 20 degree C in Kelvin
  //cout<<"Temp_0 : "<< T_0 << endl; 
  
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
	  /* 
      cout << "Input Temperature in Kelvin: ";
      getline(cin, tempIn);

      cout << "T_in = " << stod(tempIn) << " K\n";
      cout << "To = " << T_0 << " K\n";
      cout << "Ro = " << rNull(T_0) << endl;
      cout << "β = " << solveBeta(T_0) << endl;
      cout << "==========================\n";
      rVal = rTemp(stod(tempIn),T_0);
	  */
	  
	  //MODIFIED TO OUTPUT ALL EQUIVALENT RESISTANCES AT ONCE
	  double TempsCel [10] = {-45, -25, -5, 15, 35, 55, 75, 90, 105, 120};
      double TempsKel [10];
      double Resistance [10];
	  
	  double beta = solveBeta(T_0);
	  double R_0 = rNull(T_0);
	  
	  for (int i = 0; i < 10; i++)
      {
        TempsKel[i] = Celsius2Kelvin(TempsCel[i]);
	    cout<<"Temperature : "<<TempsCel[i]<<"C \t; "<<TempsKel[i]<<"K | ";
	    Resistance[i] = R_0*(exp(beta*((1/TempsKel[i])-(1/T_0))));
	    cout<<"R"<<i<<" : "<<Resistance[i]<<endl;
      }
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
      tempOut = (solveBeta(T_0)*T_0)/(((log(resistancevalue/rNull(T_0)))*T_0)+solveBeta(T_0));
      cout << "T_out = " << tempOut << " K\n";
      cin.clear();
      cin.clear();
    }
    else if (cmd == "exit")
    {
      cout << "Exiting..." << endl;
    }
    else cout<<"Invalid Command. " <<  
    "Type 'help' for a list of commands."<<endl;
  
  } while (cmd != "exit");
}