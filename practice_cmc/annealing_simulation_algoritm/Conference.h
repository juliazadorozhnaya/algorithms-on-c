#ifndef processor_H
#define processor_H

#include <iostream>
#include <fstream>
using namespace std;

#include "Track.h"

class Processor
{
  private:
    // The array of tracks.
    Track *tracks;

    // The number of parallel tracks.
    int parallelTracks;

    // The number of sessions in a track.
    int sessionsInTrack;

    // The number of works in a session.
    int worksInSession;

  public:
    Processor();

    /**
     * Constructor for processor.
     * 
     * @param parallelTracks is the number of parallel tracks.
     * @param sessionsInTrack is the number of sessions in a track.
     * @param worksInSession is the number of works in a session.
     */
    Processor(int parallelTracks, int sessionsInTrack, int worksInSession);

    /**
     * Initialize the tracks.
     * @param parallelTracks is the number of parallel tracks.
     * @param sessionsInTrack is the number of sessions in a track.
     * @param worksInSession is the number of works in a session.
     */
    void initTracks(int parallelTracks, int sessionsInTrack, int worksInSession);

    /**
     * returns the number of parallel tracks, session number, etc.
     */
    int getParallelTracks();
    int getSessionsInTrack();
    int getworksInSession();
    Track getTrack(int index);

    /**
     * starts work in processors
     * @param trackIndex track index
     * @param sessionIndex session index
     * @param workIndex work index
     * @param workId job number
     */
    void setwork(int trackIndex, int sessionIndex, int workIndex, int workId);

    void printprocessor(char *);
};

#endif /* processor_H */
