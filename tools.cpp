#include "tools.h"

/*void menu() // DEPRECATED
{
    cout << "What would you like to do?" << endl;
    cout << "[A]dd song" << endl;
    cout << "[L]ist songs" << endl;
    cout << "[E]dit song" << endl;
    cout << "[R]emove song" << endl;
    cout << "[S]earch songs" << endl;
    cout << "[C]hange library" << endl;
    cout << "[Q]uit" << endl;
    cout << "?: ";
}*/

void clear()		
{
	#if defined(windows) || defined(__windows__) || defined(__windows)
        system("cls");
	#elif defined(unix) || defined(__unix__) || defined(__unix)	
        system("clear");
	#else
        cout << "Your operating system is not supported!" << endl;
        pause();
	#endif
}

void printFile(char *fileName)
{
    int x = 48;
    cout << setw(x) << setfill('-') << "-" << endl;
    cout << setw(x/2) << setfill(' ') << left << "Current Selected File: " << setw(x/2) << right << fileName << endl;
    cout << setw(x) << setfill('-') << "-" << endl;
    cout << setfill(' ') << left << endl;
}

void fixTime(int &min, int &sec)
{
        int addM;
        int addS;

        if(sec >= 60)
        {
                addM = sec / 60;
                addS = sec % 60;

                min += addM;
                sec = addS;
        }

        cout << right << setw(3);
        cout << min << ":";

        if(sec < 10)
                cout << "0";

        cout << left << setw(4);
        cout << sec;
}

bool error(istream &buffer)
{
    if(!buffer)
    {
        cout << endl << endl << "There was a problem with your input somewhere!" << endl;
        return true;
    }
    else
    {
        return false;
    }
}

void handle(istream &buffer)
{
    cout << endl << endl << "Please Wait while we handle it!" << endl << endl;
    buffer.clear();
    buffer.ignore();
}

void pause()
{
    cout << endl << "<Press Enter To Continue>" << endl;
    cin.get();
    cin.ignore(9999,'\n');
}
