#include <iostream>
#include "./src/SoapServerClient.h"

int main(int argc, char ** args)
{
    SoapServerClient  * ssc = 0;
    cout << "----------------" << endl;
    cout << "Soap-Client-Test" << endl;
    cout << "----------------" << endl;
    ssc = new SoapServerClient(1000, "http://localhost:8000");
    cout << "Input: " << "14-1002" << endl;
    ssc->sendMessage(4, 14, "Test String", "14-1002", 12345);
    cout << "----------------" << endl;
    cout << "Input: " << "15-1002" << endl;
    ssc->sendMessage(4, 14, "Test String", "15-1002", 12345);
    cout << "----------------" << endl;
    cout << "Input: " << "4-SOAP412" << endl;
    ssc->sendMessage(4, 14, "Test String", "4-SOAP412", 12345);
    cout << "----------------" << endl;
    cout << "Input: " << "-5-SOAP51002" << endl;
    ssc->sendMessage(4, 14, "Test String", "-5-SOAP51002", 12345);
    cout << "----------------" << endl;
    delete ssc;
    cout << "Ende-Test" << endl;
    cout << "----------------" << endl;
    return 0;
}