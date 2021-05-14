#include "DoubleArray.h"
using namespace std;

DoubleArray::DoubleArray(unsigned int len)
{
	length = len;
	start = new double[len];
	memset(start, 0, sizeof(double) * len);
}

DoubleArray::DoubleArray(const DoubleArray & obj)
{
	length = obj.length;
	start = new double[obj.length];
	memcpy_s(start, length, obj.start, obj.length);
}

int DoubleArray::readFromString(const std::string & str_ref)
{
	std::string str(str_ref);
	int i = 0;
	while (!str.empty())
	{
		size_t end = str.find(' ');
		this->start[i] = str2Double(str.substr(0, end));
		str = str.substr(end + 1);
		i++;
	}
	return 1;
}

double*** DoubleArray::toTensor(double*** des, size_t depth, size_t height, size_t width) const
{
	return DoubleArray::toTensor(start, des, depth, height, width);
}

std::vector<std::vector<std::vector<double>>>* DoubleArray::toTensor(size_t depth, size_t height, size_t width) const
{
	std::vector<std::vector<std::vector<double>>> *ptr = new std::vector<std::vector<std::vector<double>>>(depth);
	for (int i = 0; i < depth; i++) {
		ptr->at(i).reserve(height);
		for (int j = 0; j < height; j++) {
			ptr->at(i).at(j).reserve(width);
			for (int k = 0; k < width; k++) {
				ptr->at(i).at(j).at(k) = start[i * height * width + j * width + k];
			}
		}
	}
	return ptr;
}

double*** DoubleArray::toTensor(const double * const src, double ***des, size_t depth, size_t height, size_t width)
{
	for (int i = 0; i < depth; i++) {
		for (int j = 0; j < height; j++) {
			for (int k = 0; k < width; k++) {
				des[i][j][k] = src[i * height * width + j * width + k];
			}
		}
	}
	return des;
}

int DoubleArray::readLengthOfStringArray(const std::string & str)
{
	int len = 1;
	for (int i = 0; i < str.size(); i++) {
		if (' ' == str.at(i)) len++;
	}
	return len;
}

