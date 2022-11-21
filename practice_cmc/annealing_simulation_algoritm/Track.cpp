#include <stdlib.h>

#include "Track.h"
 
//дорожка процессоров

Track::Track(int sessionsInTrack)
{
    this->sessionsInTrack = sessionsInTrack;
    sessions = (Session *)malloc(sizeof(Session) * sessionsInTrack);
}

void Track::setwork(int sessionIndex, int workIndex, int workId)
{
    if (sessionIndex < this->sessionsInTrack)
    {
        Session curSession = sessions[sessionIndex];
        curSession.setwork(workIndex, workId);
    }
    else
    {
        cout << "Index out of bound - Track::setwork" << endl;
        exit(0);
    }
}

int Track::getNumberOfSessions()
{
    return this->sessionsInTrack;
}

Session Track::getSession(int index)
{
    if (index < this->sessionsInTrack)
    {
        return sessions[index];
    }
    else
    {
        cout << "Index out of bound - Track::getSession" << endl;
        exit(0);
    }
}

void Track::setSession(int index, Session session)
{
    if (index < this->sessionsInTrack)
    {
        sessions[index] = session;
    }
    else
    {
        cout << "Index out of bound - Track::setSession" << endl;
        exit(0);
    }
}
