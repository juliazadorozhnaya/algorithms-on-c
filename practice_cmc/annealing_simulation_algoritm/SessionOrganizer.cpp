#include "SessionOrganizer.h"
#include "Util.h"
#include "HillClimb.h"
#include <vector>

//organization of work distribution within the session

SessionOrganizer::SessionOrganizer()
{
    parallelTracks = 0;
    worksInSession = 0;
    sessionsInTrack = 0;
    processingTimeInMinutes = 0;
    tradeoffCoefficient = 1.0;
}

SessionOrganizer::SessionOrganizer(string filename)
{
    readInInputFile(filename);
    processor = new Processor(parallelTracks, sessionsInTrack, worksInSession);
}

void SessionOrganizer::organizeworks()
{
    const int ANSWER_TO_THE_UNIVERSE = 43;
    HillClimb hill_climb(distanceMatrix, parallelTracks, sessionsInTrack, worksInSession, tradeoffCoefficient);
    auto state = hill_climb.hill_climb(true, processingTimeInMinutes * 0.95, ANSWER_TO_THE_UNIVERSE);
    int workCounter = 0;
    for (int i = 0; i < processor->getSessionsInTrack(); i++)
    {
        for (int j = 0; j < processor->getParallelTracks(); j++)
        {
            for (int k = 0; k < processor->getworksInSession(); k++)
            {
                processor->setwork(j, i, k, state[workCounter]);
                workCounter++;
            }
        }
    }
    return;
}

void SessionOrganizer::readInInputFile(string filename)
{
    vector<string> lines;
    string line;
    ifstream myfile(filename.c_str());
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            //cout<<"Line read:"<<line<<endl;
            lines.push_back(line);
        }
        myfile.close();
    }
    else
    {
        cout << "Unable to open input file";
        exit(0);
    }

    if (6 > lines.size())
    {
        cout << "Not enough information given, check format of input file";
        exit(0);
    }

    processingTimeInMinutes = atof(lines[0].c_str());
    worksInSession = atoi(lines[1].c_str());
    parallelTracks = atoi(lines[2].c_str());
    sessionsInTrack = atoi(lines[3].c_str());
    tradeoffCoefficient = atof(lines[4].c_str());

    int n = lines.size() - 5;
    double **tempDistanceMatrix = new double *[n];
    for (int i = 0; i < n; ++i)
    {
        tempDistanceMatrix[i] = new double[n];
    }

    for (int i = 0; i < n; i++)
    {
        string tempLine = lines[i + 5];
        // std::vector<string> elements(n);
        string* elements = new string[n];
        splitString(tempLine, " ", elements, n);
        for (int j = 0; j < n; j++)
        {
            tempDistanceMatrix[i][j] = atof(elements[j].c_str());
        }

        delete[] elements;
    }
    distanceMatrix = tempDistanceMatrix;

    int numberOfworks = n;
    int slots = parallelTracks * worksInSession * sessionsInTrack;
    if (slots != numberOfworks)
    {
        cout << "More works than slots available! slots:" << slots << " num works:" << numberOfworks << endl;
        exit(0);
    }
}

double **SessionOrganizer::getDistanceMatrix()
{
    return distanceMatrix;
}

void SessionOrganizer::printSessionOrganiser(char *filename)
{
    processor->printprocessor(filename);
}

double SessionOrganizer::scoreOrganization()
{
    // Sum of pairwise similarities per session.
    double score1 = 0.0;
    for (int i = 0; i < processor->getParallelTracks(); i++)
    {
        Track tmpTrack = processor->getTrack(i);
        for (int j = 0; j < tmpTrack.getNumberOfSessions(); j++)
        {
            Session tmpSession = tmpTrack.getSession(j);
            for (int k = 0; k < tmpSession.getNumberOfworks(); k++)
            {
                int index1 = tmpSession.getwork(k);
                for (int l = k + 1; l < tmpSession.getNumberOfworks(); l++)
                {
                    int index2 = tmpSession.getwork(l);
                    score1 += 1 - distanceMatrix[index1][index2];
                }
            }
        }
    }

    // Sum of distances for competing works.
    double score2 = 0.0;
    for (int i = 0; i < processor->getParallelTracks(); i++)
    {
        Track tmpTrack1 = processor->getTrack(i);
        for (int j = 0; j < tmpTrack1.getNumberOfSessions(); j++)
        {
            Session tmpSession1 = tmpTrack1.getSession(j);
            for (int k = 0; k < tmpSession1.getNumberOfworks(); k++)
            {
                int index1 = tmpSession1.getwork(k);

                // Get competing works.
                for (int l = i + 1; l < processor->getParallelTracks(); l++)
                {
                    Track tmpTrack2 = processor->getTrack(l);
                    Session tmpSession2 = tmpTrack2.getSession(j);
                    for (int m = 0; m < tmpSession2.getNumberOfworks(); m++)
                    {
                        int index2 = tmpSession2.getwork(m);
                        score2 += distanceMatrix[index1][index2];
                    }
                }
            }
        }
    }
    double score = score1 + tradeoffCoefficient * score2;
    return score;
}
