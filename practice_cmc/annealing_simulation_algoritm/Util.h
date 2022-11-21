#ifndef UTIL_H
#define UTIL_H

/**
 * Utility Function ��������� ���������� ���������. ���������� �������� � ������� result[].
 * 
 * @param message ����������� ������
 * @param delimter delimiter ��������� ������
 * @param result ���������� �������� � ���� �������
 * @param expcted ����� ����������
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
        cout << "������� ����� ������������ ������.";
        exit(0);
    }
}

#endif /* UTIL_H */
