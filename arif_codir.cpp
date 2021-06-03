#include <iostream>
#include <fstream>
#include <cstddef>
#include <map>
#include <iomanip>
constexpr short int SIZE_OF_CHARS = 8;
constexpr short int SIZEOF_NUM = 7;
using namespace std;

int main()
{
	ifstream fin("input.txt");
	ofstream fout("output.txt", ios::binary);
	map <unsigned char, unsigned int> frequency;
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

	fout.write((char*)&count, sizeof(count));
	fout.write((char*)&SIZE_OF_CHARS, sizeof(SIZE_OF_CHARS));
	unsigned int FreqSize = frequency.size();
	fout.write((char*)&FreqSize, sizeof(FreqSize));

	map <unsigned char, double*> freq;
	double a = 0, b = 0;
	for (auto s : frequency)
	{
		fout.write((char*)&s.first, sizeof(s.first));
		fout.write((char*)&s.second, sizeof(s.second));

		freq[s.first] = new double[3];
		freq[s.first][0] = double(s.second) / double(count);
		b = a + freq[s.first][0];
		freq[s.first][1] = a;
		freq[s.first][2] = b;
		a = b;
	}

	double l = 0, h = 1;
	int i = 0;
	while ((c = fin.get()) && !fin.eof())
	{
		double _l = l + freq[c][1] * (h - l),
			_h = l + freq[c][2] * (h - l);
		l = _l;
		h = _h;
		i++;

		if (i % SIZE_OF_CHARS == 0)
		{
			//fout.write(reinterpret_cast<char*>(&l), sizeof(l));
			//cout << setprecision(100) << l << endl;
			//cout << setprecision(100) << h << endl;
			uint64_t temp = 0;
			double num = 0;
			int i = 0;
			while (!(l <= num && num < h))
			{
				i++;
				if (1 / pow(2, i) + num < h)
				{
					num += 1 / pow(2, i);
					temp |= (uint64_t(1) << (i - 1));
				}
			}
			for (int i = 0; i < SIZEOF_NUM; i++)
			{
				unsigned char bit = (temp >> (i * 8)) & 255;
				fout.write((char*)&bit, sizeof(bit));
			}

			l = 0;
			h = 1;
			i = 0;
		}
	}

	if (i % SIZE_OF_CHARS)
	{
		//fout.write(reinterpret_cast<char*>(&l), sizeof(l));
		uint64_t temp = 0;
		double num = 0;
		int i = 0;
		while (!(l <= num && num < h))
		{
			i++;
			if (1 / pow(2, i) + num < h)
			{
				num += 1 / pow(2, i);
				temp |= (uint64_t(1) << (i - 1));
			}
		}
		for (int i = 0; i < SIZEOF_NUM; i++)
		{
			unsigned char bit = (temp >> (i * 8)) & 255;
			fout.write((char*)&bit, sizeof(bit));
		}

	}
	return 0;
}
