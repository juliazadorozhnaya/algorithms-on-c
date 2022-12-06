#ifndef TRACK_H
#define TRACK_H

#include "Session.h"

/**
 * The track contains a queue of sessions
 *
 */

class Track
{
private:
  Session *sessions;
  int sessionsInTrack;

public:
  Track() = delete;

  Track(int sessionsInTrack);  
  
  void setwork(int sessionIndex, int workIndex, int workId);

  int getNumberOfSessions();

  Session getSession(int index);

  void setSession(int index, Session session);
};

#endif /* TRACK_H */
