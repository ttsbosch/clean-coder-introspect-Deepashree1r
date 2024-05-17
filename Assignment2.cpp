// Online C++ compiler to run C++ program online
#include <iostream>
#include <string>
using namespace std;

class Device
{
    public:
        int serialNumber;
        string modelname;
};

class Printer : public virtual Device{

    public:
     void print(string path){
        cout<<"Printing ....."<<path;
    }
};

class Scanner : public virtual Device{

    public:
     void scan(string path){
        cout<<"Scanning ....."<<path;
    }
};

class PrintScanner : public Printer, public Scanner {

public:

    Printer printer;
    Scanner scanner;

 
    void print(string path){
        printer.print(path);
    }
 
    void scan(string path){
        scanner.scan(path);
    }
    
};
class TaskManager{
    public:
     static void execuctePrintTask(Printer *printer,string documentPath){
        printer->print(documentPath);
    }
     static void execucteScanTask(Scanner *scanner,string documentPath){
            scanner->scan(documentPath);
    }
};


    int main(){
        Printer printerObj;
        Scanner scannerObj;
        PrintScanner printScannerObj;

        TaskManager::execuctePrintTask(&printerObj,"Test.doc");
        TaskManager::execucteScanTask(&scannerObj,"MyImage.png");
        TaskManager::execuctePrintTask(&printScannerObj,"NewDoc.doc");
        TaskManager::execucteScanTask(&printScannerObj,"YourImage.png");
    }