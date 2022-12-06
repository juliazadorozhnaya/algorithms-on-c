#ifndef SESSION_H
#define SESSION_H

#include <iostream>
#include <cstdlib>
using namespace std;

/**
 * The session stores the number of jobs in one processor
 *
 */

class Session
{

  private:
    int *works;         
    int worksInSession; 

  public:
    Session();

    /**
     * constructor
     */
    Session(int worksInSession);

    /**
     * starting the work queue
     */
    void initworks(int worksInSession);

    /**
     * request for the number of works
     */
    int getNumberOfworks();

    /**
     * request a job number by its index
     */
    int getwork(int index);

    /**
     * matches the job number with its index
     * 
     * @param index index in the queue
     * @param workId number in operation
     */
    void setwork(int index, int workId);

    /**
     * printing works in a specific session
     *
     */
    void printSession();
};

#endif /* SESSION_H */
