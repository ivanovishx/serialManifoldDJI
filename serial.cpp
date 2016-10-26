#include<iostream>
#include<fstream>
using namespace std;

int main()
{
    ofstream arduino_output("/dev/ttyTHS1");
    ifstream arduino_input("/dev/ttyTHS1");

    int value;
    string txt;
    cout<<"Waiting serial port: ttyTHS1..."<<endl;
    while(cin >> value){
        arduino_output << value << endl;
        arduino_input >> txt;//I never recieve the "OK" (Which I should get)
        cout << txt;
    }

    arduino_input.close();
    arduino_output.close();
    return(0);
} 