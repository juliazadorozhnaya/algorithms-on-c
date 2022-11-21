#include <cstdlib>
#include "SessionOrganizer.h"

using namespace std;

int main(int argc, char **argv)
{
    // ������� ������� ������
    if (argc < 3)
    {
        cout << "���������� ������\n";
        cout << "���������� ������: \n";
        cout << "./main <input_filename> <output_filename>";
        exit(0);
    }
    string inputfilename(argv[1]);

    // ������ ������� ����� �����������
    SessionOrganizer *organizer = new SessionOrganizer(inputfilename);

    // ��������� ����� �� ����������� �� ������ ��������������
    organizer->organizeworks();

    organizer->printSessionOrganiser(argv[2]);

 
    delete organizer;

    return 0;
}
