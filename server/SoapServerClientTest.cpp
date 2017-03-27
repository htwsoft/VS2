#include <iostream>
#include "./src/SoapServerClient.h"

int main(int argc, char ** args)
{
    SoapServerClient  * ssc = 0;
    cout << "----------------" << endl;
    cout << "Soap-Client-Test" << endl;
    cout << "----------------" << endl;
    ssc = new SoapServerClient(1000, "http://10.9.40.111:8080/TafelWS/serverws?wsdl");
    cout << "Input: " << "14-1002" << endl;
    ssc->sendMessage(4, 14, "Test String", "14-1002", 12345);
    delete ssc;
    cout << "Ende-Test" << endl;
    cout << "----------------" << endl;
    return 0;
}