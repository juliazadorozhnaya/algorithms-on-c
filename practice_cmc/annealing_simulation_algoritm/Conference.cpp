
#include "Conference.h"

//work on processors
Processor::Processor()  {
    this->parallelTracks = 0;
    this->sessionsInTrack = 0;
    this->worksInSession = 0;
}

//processor description
Processor::Processor(int parallelTracks, int sessionsInTrack, int worksInSession)    
{
    this->parallelTracks = parallelTracks;
    this->sessionsInTrack = sessionsInTrack;
    this->worksInSession = worksInSession;
    initTracks(parallelTracks, sessionsInTrack, worksInSession);
}

//counting tracks
void Processor::initTracks(int parallelTracks, int sessionsInTrack, int worksInSession)    
{
    tracks = (Track *)malloc(sizeof(Track) * parallelTracks);
    for (int i = 0; i < parallelTracks; i++)
    {
        Track tempTrack(sessionsInTrack);
        for (int j = 0; j < sessionsInTrack; j++)
        {
            Session tempSession(worksInSession);
            tempTrack.setSession(j, tempSession);
        }
        tracks[i] = tempTrack;
    }
}

//tasks for the processor
int Processor::getParallelTracks()  
{
    return parallelTracks;
}

int Processor::getSessionsInTrack()
{
    return sessionsInTrack;
}

int Processor::getworksInSession()
{
    return worksInSession;
}

Track Processor::getTrack(int index)
{
    if (index < parallelTracks)
    {
        return tracks[index];
    }
    else
    {
        cout << "Index out of bound - processor::getTrack" << endl;
        exit(0);
    }
}

//installation work
void Processor::setwork(int trackIndex, int sessionIndex, int workIndex, int workId)        
{
    if (this->parallelTracks > trackIndex)
    {
        Track curTrack = tracks[trackIndex];
        curTrack.setwork(sessionIndex, workIndex, workId);
    }
    else
    {
        cout << "Index out of bound - processor::setwork" << endl;
        exit(0);
    }
}

//printing processors
void Processor::printprocessor(char *filename)   
{
    ofstream ofile(filename);

    for (int i = 0; i < sessionsInTrack; i++)
    {
        for (int j = 0; j < parallelTracks; j++)
        {
            for (int k = 0; k < worksInSession; k++)
            {
                ofile << tracks[j].getSession(i).getwork(k) << " ";
            }
            if (j != parallelTracks - 1)
            {
                ofile << "| ";
            }
        }
        ofile << "\n";
    }
    ofile.close();
    cout << "The result is viewed in:";
    printf("%s :)\n", filename);
}
