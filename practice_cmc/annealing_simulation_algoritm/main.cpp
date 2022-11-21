#include <cstdlib>
#include "SessionOrganizer.h"

using namespace std;

int main(int argc, char **argv)
{
    // Парсинг входных данных
    if (argc < 3)
    {
        cout << "Потерянные данные\n";
        cout << "Корректный формат: \n";
        cout << "./main <input_filename> <output_filename>";
        exit(0);
    }
    string inputfilename(argv[1]);

    // Запуск анализа работ процессоров
    SessionOrganizer *organizer = new SessionOrganizer(inputfilename);

    // Разгрузка работ по процессорам на основе параллельности
    organizer->organizeworks();

    organizer->printSessionOrganiser(argv[2]);

 
    delete organizer;

    return 0;
}
