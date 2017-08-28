#include "WeatherNode.h"

// ----------------------------------------------------------------
// |                        Constructors                          |
// ----------------------------------------------------------------

Node::Node()
{
    time = 0;
    temp = 0;
    wind = 0;
}

Node::Node(int tTime, double tTemp, double tWind)
{
    time = tTime;
    temp = tTemp;
    wind = tWind;
}

// ----------------------------------------------------------------
// |                         Destructors                          |
// ----------------------------------------------------------------

Node::~Node()
{
    //TODO: Nothing
}

// ----------------------------------------------------------------
// |                         Accessors                            |
// ----------------------------------------------------------------
int Node::getTime()
{
    return time;
}

double Node::getTemp()
{
    return temp;
}

double Node::getWind()
{
    return wind;
}

// ----------------------------------------------------------------
// |                          Operators                           |
// ----------------------------------------------------------------

ostream & operator << (ostream & buffer, Node & node)
{
    buffer << "Timestamp: " << node.time  << endl;
    buffer << "Temperature: " << (node.temp / 10.0) << " C"<< endl;
    buffer << "Windspeed: " << (node.wind / 100) << " m/s" << endl;
    buffer << endl;
    
    return buffer;
}

const Node & Node::operator = (const Node & node)
{
    if(this == &node)
    {
        return *this;
    }
    else
    {
        this->time = node.time;
        this->temp = node.temp;
        this->wind = node.wind;
        
        return *this;
    }
}