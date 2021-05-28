#include <iostream>
#include <fstream>
#include <cstddef>
#include <map>
#include <iomanip>
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

        if (i % SIZE_OF_CHARS == 0)
        {
            fout << setprecision(100) << l;
            l = 0;
            h = 1;
        }
    }

    if (i % SIZE_OF_CHARS)
    {
        fout << setprecision(100) << l;
    }

    return 0;
}
