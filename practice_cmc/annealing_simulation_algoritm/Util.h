#ifndef UTIL_H
#define UTIL_H

/**
 * Utility Function separates string messages. the results are stored in an array result[].
 * 
 * @param message shared string
 * @param delimter delimiter splits lines
 * @param result the results are stored in this array
 * @param expcted result length
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
        cout << "the matrix has an incorrect format.";
        exit(0);
    }
}

#endif /* UTIL_H */
