#ifndef UTIL_H
#define UTIL_H

/**
 * Utility Function раздел€ет стринговые сообщени€. результаты хран€тс€ в массиве result[].
 * 
 * @param message раздел€ема€ строка
 * @param delimter delimiter раздел€ет строки
 * @param result результаты хран€тс€ в этом массиве
 * @param expcted длина результата
 */
void splitString(string message, string delimiter, string result[], int n)
{
    int i = 0, pos = 0, length = 0, temp;
    temp = message.find(delimiter.c_str(), pos);
    while (temp != -1)
    {
        length = temp - pos;
        result[i] = message.substr(pos, length);
        pos = temp + delimiter.size();
        temp = message.find(delimiter.c_str(), pos);
        i++;
    }
    result[i] = message.substr(pos);
    i++;
    if (i != n)
    {
        cout << "ћатрица имеет неконкретный формат.";
        exit(0);
    }
}

#endif /* UTIL_H */
