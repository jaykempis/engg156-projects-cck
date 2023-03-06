#include <iostream>
#include <cstring>

using namespace std;

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

int main() 
{
    char hexNumber[80];
    // Read the hexadecimal number as a character array
    cout << "Enter hexadecimal number: ";
    cin >> hexNumber;

    double decValue = hexToDec(hexNumber);

    cout << hexNumber << " in decimal format = " << decValue << "\n";

    double resistancevalue = ADCconvert(decValue);

    cout << "\nThe Resistance of " << hexNumber << " is " << resistancevalue << endl;


}