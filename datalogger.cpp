#include "datalogger.h"

// ----------------------------------------------------------------
// |                        Constructors                          |
// ----------------------------------------------------------------

datalogger::datalogger()
{
    banHead = NULL;
    timeHead = NULL;
    tempHead = NULL;
    windHead = NULL;
    
    size = 0;
    banSize = 0;
}

// ----------------------------------------------------------------
// |                         Destructors                          |
// ----------------------------------------------------------------

datalogger::~datalogger()
{
    //TODO: Destruct
    Segment * previous = timeHead;
    Segment * current = previous->timeNext;
    BanList * bPrevious = banHead;
    BanList * bCurrent = bPrevious->next;
        
    while(current)
    {
        delete previous;
        previous = NULL;
        
        if(current->timeNext)
        {
            previous = current;
            current = previous->timeNext;
        }
        else
        {
            delete current;
            current = NULL;
            timeHead = NULL;
            break;
        }
    }
    
    while (bCurrent)
    {
        delete bPrevious;
        bPrevious = NULL;
        
        if(bCurrent->next)
        {
            bPrevious = bCurrent;
            bCurrent = bPrevious->next;
        }
        else
        {
            delete bCurrent;
            bCurrent = NULL;
            banHead = NULL;
            break;
        }
    }
}

// ----------------------------------------------------------------
// |                         Accessors                            |
// ----------------------------------------------------------------

void datalogger::printTime()
{
    Segment * current = timeHead;
    
    for(int i = 0; i < size; i++)
    {
        cout << current->data << endl;
        current = current->timeNext;
    }
    cout << endl;
}

void datalogger::printTime(ostream & buffer)
{
    Segment * current = timeHead;
    
    for(int i = 0; i < size; i++)
    {
        buffer << current->data << endl;
        current = current->timeNext;
    }
    buffer << endl;
}

void datalogger::printTopTemp(ostream & buffer, double minTemp, double maxTemp)
{
    maxTemp /=10;
    minTemp /= 10;
    
    double top = (maxTemp - ((maxTemp - minTemp) / 100));
    Segment * current = timeHead;
    
    buffer << endl;
    buffer << "----------------------------------------------------------------------" << endl;
    buffer << "TEMPERATURE" << endl;
    buffer << "Min temperature:\t\t\t" << minTemp  << " C" << endl;
    buffer << "Max temperature:\t\t\t" << maxTemp << " C" << endl << endl;
    buffer << "Top 1% temperatures (>= " << top << "):" << endl;
    
    while (current)
    {
        if((current->data.getTemp())/10 > top)
            buffer << current->data;
        
        current = current->timeNext;
    }
}

void datalogger::printBotTemp(ostream & buffer, double minTemp, double maxTemp)
{
    maxTemp /=10;
    minTemp /= 10;
    
    double bot = (minTemp + ((maxTemp - minTemp) / 100));
    Segment * current = timeHead;

    buffer << endl;
    buffer << "Bottom 1% temperatures (<= " << bot << "):" << endl;
    
    while (current)
    {
        if((current->data.getTemp())/10 < bot)
            buffer << current->data;
        
        current = current->timeNext;
    }
}

void datalogger::printTopWind(ostream & buffer, double minWind, double maxWind)
{
    maxWind /= 100;
    minWind /= 100;
    
    double top = (maxWind - ((maxWind - minWind) / 100));
    Segment * current = timeHead;
    
    buffer << endl;
    buffer << "----------------------------------------------------------------------" << endl;
    buffer << "WINDSPEED" << endl;
    buffer << "Min windspeed:\t\t\t" << minWind  << " m/s" << endl;
    buffer << "Max windspeed:\t\t\t" << maxWind << " m/s" << endl << endl;
    buffer << "Top 1% windspeeds (>= " << top << "):" << endl;
    
    while (current)
    {
        if((current->data.getWind())/100 > top)
            buffer << current->data;
        
        current = current->timeNext;
    }
}

void datalogger::printBotWind(ostream & buffer, double minWind, double maxWind)
{
    maxWind /=100;
    minWind /= 100;
    
    double bot = (minWind + ((maxWind - minWind) / 100));
    Segment * current = timeHead;
    
    buffer << "----------------------------------------------------------------------" << endl;
    buffer << "Bottom 1% windspeeds (<= " << bot << "):" << endl;
    
    while (current)
    {
        if((current->data.getWind())/100 < bot)
            buffer << current->data;
        
        current = current->timeNext;
    }
}

void datalogger::printOut()
{
    Segment * current = windHead;
    
    while (current)
    {
        cout << current->data;
        
        if(current->windNext)
            current = current->windNext;
        else
            break;
    }
}

void datalogger::printReport()
{    
    //TODO: Print full report
    
    clear();
    clear();
    
    Segment * current = timeHead;
    
    int minTime = current->data.getTime(), maxTime = current->data.getTime();
    double tempRange, minTemp = current->data.getTemp(), maxTemp = current->data.getTemp();
    double windRange, minWind = current->data.getWind(), maxWind = current->data.getWind();
    
    while (current)
    {
        if(current->data.getTime() < minTime)
            minTime = current->data.getTime();
            
        if(current->data.getTime() > maxTime)
            maxTime = current->data.getTime();
        
        if(current->data.getTemp() < minTemp)
            minTemp = current->data.getTemp();
        
        if(current->data.getTemp() > maxTemp)
            maxTemp = current->data.getTemp();
        
        if(current->data.getWind() < minWind)
            minWind = current->data.getWind();
        
        if(current->data.getWind() > maxWind)
            maxWind = current->data.getWind();
        
        current = current->timeNext;
    }
    
    ofstream outFile;
    outFile.open("weather_report.txt");
    
    outFile << "\t\t\t\t\t\t\t\t-- Data Report --" << endl << endl;
    outFile << "Time range:\t\t" << minTime << " - " << maxTime << endl;
    outFile << "Number of entries:\t\t" << size << endl;
        
    printTopTemp(outFile,minTemp,maxTemp);
    printBotTemp(outFile,minTemp,maxTemp);
    printTopWind(outFile,minWind,maxWind);
    printBotWind(outFile,minWind,maxWind);
    
    outFile.close();
    
    
    cout << "Report has been generated in weather_report.txt" << endl;
}

// ----------------------------------------------------------------
// |                         Mutators                            |
// ----------------------------------------------------------------

void datalogger::addData(int timestamp, double temperature, double windspeed)
{    
    Segment * temp = new Segment; // Populate new segment with inputs from file
    Segment * current = NULL;
    Segment * previous = NULL;
    
    BanList * banTemp = new BanList; // Populate a banTemp with a copy of the curren temp
    BanList * bCurrent = NULL;
    
    // Empty the pointers (redundant, but safe)
    temp->timeNext = NULL;
    temp->tempNext = NULL;
    temp->windNext = NULL;
    banTemp->next = NULL;    
    
    temp->data = Node(timestamp,temperature,windspeed); // Populate data part of Segment
    banTemp->bnum = temp->data.getTime(); // Populate the banTemp with the timestame from temp
    
    if(size == 0) // Start a new list, make it the begining of all three lists
    {        
        bCurrent = banHead; // Start banlist, use for later
        
        // Check preexisting list of banned entries
        if(bCurrent) // If a ban list has something in it, continue
        {                    
            for(int i = 0; i < banSize; i++) // Compare everything in the ban list to temp, if a match is found, throw out temp, else continue
            {
                if(temp->data.getTime() == bCurrent->bnum) // A pre-existing duplicate has been found
                {
                    // Throw out temp
                    delete temp;
                    temp = NULL;
                    return;
                }
                        
                if(bCurrent->next) // Keep checking the ban list
                    bCurrent = bCurrent->next;
                else // At the end of the list, and no bans found, continue
                    break;
            }
        }
        
        timeHead = temp;
        tempHead = temp;
        windHead = temp;
        
        size++;
        return;
    }
    else
    {
        // Insert the node into timestamp temperature and windspeed in respective order
        
        // Timestamp insertion
        
        current = timeHead; // Start at the first known timestamp head
        bCurrent = banHead; // Start banlist, use for later
        
        // Check preexisting list of banned entries
        if(bCurrent) // If a ban list has something in it, continue
        {                    
            for(int i = 0; i < banSize; i++) // Compare everything in the ban list to temp, if a match is found, throw out temp, else continue
            {
                if(temp->data.getTime() == bCurrent->bnum) // A pre-existing duplicate has been found
                {
                    //TODO: Throw out temp
                    return;
                }
                        
                if(bCurrent->next) // Keep checking the ban list
                    bCurrent = bCurrent->next;
                else // At the end of the list, and no bans found, continue
                    break;
            }
        }
        
        while(current)
        {          
            //bCurrent = banHead;
            
            if(temp->data.getTime() == current->data.getTime()) // If temp is the same as current (dulplicate found)
            {                
                if(banSize == 0) // If banHead is empty, start a new ban list
                {
                    banHead = banTemp;
                }
                else // Add timestamp to banlist
                {
                    while(bCurrent->next) // Move to the end of the list
                    {
                        bCurrent = bCurrent->next;
                    }
                    
                    bCurrent->next = banTemp;                    
                }
                
                banSize++;
                
                // Remove current node
                if(current == timeHead) // Removing at head
                {
                    timeHead = current->timeNext;
                    tempHead = current->timeNext;
                    windHead = current->timeNext;
                    delete current;
                    current = NULL;

                    delete temp;
                    temp = NULL;
                }
                else if (current->timeNext == NULL) // Removing at tail
                {
                    previous->timeNext = NULL;
                    delete current;
                    current = NULL;
                    
                    delete temp;
                    temp = NULL;
                }
                else // Removing in between
                {
                    previous->timeNext = current->timeNext;
                    delete current;
                    current = NULL;
                    
                    delete temp;
                    temp = NULL;
                }
                                           
                size--;
                return;
            }
            else if(current->timeNext && current->data.getTime() < temp->data.getTime()) // If not at the end of the list, and current timestamp is less than temp timestamp, then check the next node
            {
                previous = current;
                current = current->timeNext;
            }
            else // If at the end of the list (catch it premptively) insert at the end
            {
                break;
            }
        }
        
        if(current == timeHead && current->data.getTime() > temp->data.getTime()) // If still at the timeHead of the list, then insert before the timeHead, and reassign timeHead to temp
        {
            temp->timeNext = timeHead;
            timeHead = temp;
        }
        else if (current->timeNext == NULL && current->data.getTime() < temp->data.getTime()) // If current is at the end of the list AND temp is greater than current, then insert after current
        {
            current->timeNext = temp;
        }
        else // If data is somewhere in between, then insert after current
        {
            temp->timeNext = current;
            previous->timeNext = temp;
        }
        
        // Windspeed insertion
        
        /*current = windHead;
        previous = NULL;
        
        while (current)
        {
            if(current->windNext && current->data.getWind() < temp->data.getWind()) // If not at the end of the list, and current windspeed is less than temp windspeed, then check the next node
            {
                previous = current;
                current = current->windNext;
            }
            else // If at the end of the list (catch it premptively) insert at the end
            {
                break;
            } 
        }
        
        if(current == windHead && current->data.getWind() > temp->data.getWind()) // If still at the timeHead of the list, then insert before the timeHead, and reassign timeHead to temp
        {
            temp->windNext = windHead;
            windHead = temp;
        }
        else if (current->windNext == NULL && current->data.getWind() < temp->data.getWind()) // If current is at the end of the list AND temp is greater than current, then insert after current
        {
            current->windNext = temp;
        }
        else // If data is somewhere in between, then insert after current
        {
            temp->windNext = current;
            previous->windNext = temp;
        }*/
        
        size++;
        return;
    }
}