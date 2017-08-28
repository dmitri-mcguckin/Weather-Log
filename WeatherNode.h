#ifndef WEATHERNODE_H
#define WEATHERNODE_H

#include <iostream>
#include <iomanip>
#include <istream>
#include <fstream>
#include <string.h>

using namespace std;

class Node
{
    private:
        int time;
        double temp;
        double wind;
    public:
        // Constructors
        Node();
        Node(int, double, double);
        
        // Destructor
        ~Node();
        
        // Accessors
        int getTime();
        double getTemp();
        double getWind();
        
        // Mutators
        friend ostream &operator << (ostream &, Node &);
        const Node & operator = (const Node &);
};

#endif