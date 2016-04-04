#include <iostream>
#include <fstream>
using namespace std;

//定义要删除的行号格式，下面定义的是型如: #0001 的行号
const int LINE_NUM_LENGTH = 5;
const char LINE_NUM_START = '#';

int main(int argc, char *argv[])
{
    fstream f;
    char *s = NULL;
    int n;
    for (int i = 1; i < argc; i++)
    {
        cout << "Processing file " << argv[i] << "......";
        f.open(argv[i], ios::in | ios::binary);
        if (!f.is_open())
        {
            cout << "CANNOT OPEN"<< endl;
            continue;
        }
        f.seekg(0, ios::end);
        n = f.tellg(); // 文件大小
        s = new char[n+1];
        f.seekg(0, ios::beg);
        f.read(s, n);
        s[n] = '\0';
        f.close();
        // 采用一种简单的判断，遇到LINE_NUM_START后接一个数字，
        // 则认为它是一个行号.
        for (int j = 0; j < n; j++)
        {
            if (s[j] == LINE_NUM_START &&
            (s[j+1] >= '0' && s[j+1] <= '9'))
            {
                for (int k = j; k < j + LINE_NUM_LENGTH; k++)
                    s[k] = ' ';
            }
        }

        f.open(argv[i], ios::out | ios::binary);
        if (!f.is_open())
        {
            cout << "CANNOT OPEN" << endl;
            delete[] s;
            continue;
        }
        f.write(s, n);
        f.close();
        cout << "OK" << endl;
        delete[] s;
    }
    return 0;
}
