#include <cstdlib>
#include "SessionOrganizer.h"

using namespace std;

int main(int argc, char **argv)
{
    // input data parsing
    if (argc < 3)
    {
        cout << "Lost Data\n";
        cout << "Correct format: \n";
        cout << "./main <input_filename> <output_filename>";
        exit(0);
    }
    string inputfilename(argv[1]);

    // Starting the analysis of the work of processors
    SessionOrganizer *organizer = new SessionOrganizer(inputfilename);

    // Unloading of work on processors based on parallelism
    organizer->organizeworks();

    organizer->printSessionOrganiser(argv[2]);

 
    delete organizer;

    return 0;
}
