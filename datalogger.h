#ifndef DATALOGGER_H
#define DATALOGGER_H

#include <iostream>
#include <iomanip>
#include <istream>
#include <fstream>
#include <string.h>
#include "tools.h"
#include "WeatherNode.h"

using namespace std;

class datalogger
{
    private: 
        struct Segment
        {
            Node data;
            Segment * timeNext;
            Segment * tempNext;
            Segment * windNext;
        };
        
        struct BanList
        {
            int bnum;
            BanList * next;
        };
        
        int size;
        int banSize;
        BanList * banHead;
        Segment * timeHead;
        Segment * tempHead;
        Segment * windHead;
    public:
        // Constructors
        datalogger();
        
        // Destructor
        ~datalogger();
        
        // Accessors
        void printTime();
        void printTime(ostream & buffer);
        void printTopTemp(ostream & buffer, double, double);
        void printBotTemp(ostream & buffer, double, double);
        void printTopWind(ostream & buffer, double, double);
        void printBotWind(ostream & buffer, double, double);
        void printOut();
        void printReport();
        // Mutators
        void addData(int, double, double);
        void removeData(int);
};

#endif