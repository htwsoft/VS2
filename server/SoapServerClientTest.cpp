#include <iostream>
#include "./src/SoapServerClient.h"

int main(int argc, char ** args)
{

    cout << "----------------" << endl;
    cout << "Soap-Client-Test" << endl;
    cout << "----------------" << endl;
        SoapServerClient  * ssc = 0;
    ssc = new SoapServerClient(1, "http://10.9.40.111:8080/TafelWS/serverws?wsdl");
    cout << "Input: " << "14-1020" << endl;
    ssc->sendMessage(1, 14, "Test String", "14-1020", 12345);
    delete ssc;
    cout << "Ende-Test" << endl;
    cout << "----------------" << endl;
    return 0;
}