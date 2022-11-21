#include <errno.h>
#include <vector>

#include "Session.h"
 
//description of all sessions on processors

Session::Session()
{
    worksInSession = 0;
}

Session::Session(int worksInSession)
{
    this->worksInSession = worksInSession;
    initworks(worksInSession);
}

void Session::initworks(int worksInSession)
{
    this->works = (int *)malloc(sizeof(int) * worksInSession);
    for (int i = 0; i < worksInSession; i++)
    {
        works[i] = -1;
    }
}

int Session::getNumberOfworks()
{
    return worksInSession;
}

int Session::getwork(int index)
{
    if (index < worksInSession)
    {
        return works[index];
    }
    else
    {
        cout << "Index of the available abroad- Session::getwork" << endl;
        exit(0);
    }
}

void Session::setwork(int index, int workId)
{
    if (index < worksInSession)
    {
        works[index] = workId;
    }
    else
    {
        cout << "Index of the available abroad  - Session::setwork" << endl;
        exit(0);
    }
}
 
//printing a session

void Session::printSession()
{
    for (int i = 0; i < worksInSession; i++)
    {
        cout << works[i] << " ";
    }
    cout << endl;
}
