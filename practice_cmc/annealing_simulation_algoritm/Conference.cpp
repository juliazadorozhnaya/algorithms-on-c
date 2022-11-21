
#include "Conference.h"

Processor::Processor()   //работа на процессах
{
    this->parallelTracks = 0;
    this->sessionsInTrack = 0;
    this->worksInSession = 0;
}

Processor::Processor(int parallelTracks, int sessionsInTrack, int worksInSession)    //описание процессора
{
    this->parallelTracks = parallelTracks;
    this->sessionsInTrack = sessionsInTrack;
    this->worksInSession = worksInSession;
    initTracks(parallelTracks, sessionsInTrack, worksInSession);
}

void Processor::initTracks(int parallelTracks, int sessionsInTrack, int worksInSession)     //подсчет треков
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

int Processor::getParallelTracks()  //задачи для процессора
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

void Processor::setwork(int trackIndex, int sessionIndex, int workIndex, int workId)         //установка работы
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

void Processor::printprocessor(char *filename)   //печать процессов
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
    // cout << "Результат смотреть в:";
    // printf("%s :)\n", filename);
}
