#include <iostream>
#include <fstream>
#include <cstddef>
#include <map>
#include <iomanip>
#include <string>
#include <sstream>
constexpr short int SIZE_OF_CHARS = 15;
using namespace std;

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    map <unsigned char, int> frequency;
    unsigned char c = 0;
    unsigned long long count = 0;
    
    //reading a file and counting the character frequencies in an array
    while ((c = fin.get()) && !fin.eof())
    {
        frequency[c]++;
        count++;
    }

    //translating the pointer to the beginning of the file
    fin.clear();
    fin.seekg(0);
    fout << count << " " << short int(SIZE_OF_CHARS) << " " << int(frequency.size());

    map <unsigned char, double long*> freq;
    double long a = 0, b = 0;
    for (auto s : frequency)
    {
        fout << s.first << s.second << " ";
        freq[s.first] = new double long[3];
        freq[s.first][0] = double long(s.second) / double long(count);
        b = a + freq[s.first][0];
        freq[s.first][1] = a;
        freq[s.first][2] = b;

        cout << s.first << " ";
        cout.width(10);
        cout << freq[s.first][0] << " ";
        cout.width(10);
        cout << freq[s.first][1] << " ";
        cout.width(10);
        cout << freq[s.first][2] << endl;

        a = b;
    }

    double long l = 0, h = 1;
    int i = 0;
    while ((c = fin.get()) && !fin.eof())
    {
        double long _l = l + freq[c][1] * (h - l),
            _h = l + freq[c][2] * (h - l);
        l = _l;
        h = _h;
        i++;
        cout << endl;
        cout << "Encode: " << i << endl;
        cout << "l: " << setprecision(100) << l << endl;
        cout << "h: " << setprecision(100) << h << endl;
        cout << endl;

        if (i % SIZE_OF_CHARS == 0)
        {
        //    stringstream s1, s2;
        //    s1 << setprecision(100) << l;
        //    s2 << setprecision(100) << h;
        //    cout << s1.str() << endl;
        //    cout << s2.str() << endl;
        //    if (s1.str()!=s2.str())
        //    {
        //        for (int i = 0; i < 100; i++)
        //        {
        //            if (s1.str()[i] != s2.str()[i])
        //            {
        //                s1.str()[i] += 1;
        //                char buf[100];
        //                auto len = s1.str().copy(buf, 1, i);
        //                buf[len] = '\0';
        //                cout << buf << endl;
        //                break;
        //            }
        //        }
        //    }
        //    else
        //    {
        //        cout << s1.str() << endl;
        //    }
            
            fout << l;
            l = 0;
            h = 1;
            i = 0;
        }
    }

    if (i % SIZE_OF_CHARS)
    {
        fout << l;
    }

    return 0;
}
