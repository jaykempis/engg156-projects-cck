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

double Kelvin2Celsius(double temp_kelvin)
{
  return temp_kelvin - 273.15;
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
  double powerFactor = solveBeta(T_0)*((1.000/tempIn)
                       -(1.000/T_0))*1.000;
  rT = rNull(T_0)*1.0000*exp(powerFactor);
  //cout <<"PowerFactor: " <<powerFactor << endl;
  //cout <<"Ro: " <<rNull(T_0) << endl;
  cout << "R(" << tempIn << ")= "<<rT <<endl;
  return rT;
}

double ADCconvert(double ADC)
{
  double voltage;
  cout <<ADC<<" in Decimal: " << ADC << endl;
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
      <<"* res            - Resistance/Temperature Operations\n"
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
	  double TempsCel [10] = {-45, -25, -5, 15, 35, 
	                           55, 75, 90, 105, 120};
      double TempsKel [10];
      double Resistance [10];
	  
	  double beta = solveBeta(T_0);
	  double R_0 = rNull(T_0);
	  
	  for (int i = 0; i < 10; i++)
      {
        TempsKel[i] = Celsius2Kelvin(TempsCel[i]);
	    cout<<"Temperature : "<<TempsCel[i]<<"C \t; "
		    <<TempsKel[i]<<"K | ";
	    Resistance[i] = R_0*(exp(beta*((1/TempsKel[i])-(1/T_0))));
	    cout<<"R"<<i<<" : "<<Resistance[i]<<endl;
      }
    }
	
    else if (cmd == "adc")
    { 
	  string hexNumber[10] = {"F9B8", "EB11", "CB00", "9A48", "6761",
	                        "400F", "26C0", "1ABE", "12B9", "0D58"};
  	  for (int i = 0; i < 10; i++)
      {
        double decValue = stoi(hexNumber[i], 0, 16);
	    double resistancevalue = ADCconvert(decValue);
	    //Replace rVal with ADC resistance calc
        tempOut = (solveBeta(T_0)*T_0)/
		    (((log(resistancevalue/rNull(T_0)))*T_0)+solveBeta(T_0));
        cout << "T_out = " << tempOut <<" K;\t"
		     <<Kelvin2Celsius(tempOut)<<"degree Celsius"<<endl;
      }
	}
    else if (cmd == "exit")
    {
      cout << "Exiting..." << endl;
    }
    else cout<<"Invalid Command. " <<  
    "Type 'help' for a list of commands."<<endl;
  
  } while (cmd != "exit");
}