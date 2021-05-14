#pragma once
#include <string>
#include <memory.h>
#include <vector>
#include <stdexcept>
#include <sstream>
constexpr const char* STR_ERR_OUTOFRANGE = "DoubleArray Index out_of_range Error!";
class DoubleArray
{
private:
	double *start;
	unsigned int length;

public:

	/* Constructor */
	DoubleArray(unsigned int len);
	/* Copier */
	DoubleArray(const DoubleArray &);
	/* Destructor */
	~DoubleArray() { delete[] start; }

	/* Access the element at index i
	 * @param i index in the array
	 * @return element of index i in the array
	 */
	inline double get(unsigned int i) {
		if (i >= length) throw std::out_of_range(STR_ERR_OUTOFRANGE);
		return start[i];
	}

	/* Set the elemnt at index i 
	 * @param i index
	 * @param val value
	 */
	inline void set(unsigned int i, double val) {
		if (i >= length) throw std::out_of_range(STR_ERR_OUTOFRANGE);
		start[i] = val;
	}

	/* Precondition: The string end with '\n'
	 * @param str string that will be read
	 * @return the amount of double is read from the string
	 */
	int readFromString(const std::string & str);

	/* Precondition: The string end with "\n\0"
	 * @param str string that will be read
	 * @return the amount of double is read from the string
	 */
	inline int readFromString(const char* str) {
        return DoubleArray::readFromString(std::string(str));
	}

	/* Precondition: des need to be nullptr; the length of array shoud meet with
	 *		depth * heigt * width
	 * Parameters depth, height, width represent the following size of tensor:
	 *		double tensor[depth][height][width];
	 * @param des pointer points to the following three-dimensional tensor
	 * @return the pointer pointing to the destination tensor
	 */
	double*** toTensor(double ***des, size_t depth, size_t height, size_t width) const;

	/* Precondition: the length of array shoud meet with depth * heigt * width
	 * Parameters depth, height, width represent the following size of tensor:
	 *		double tensor[depth][height][width];
	 * @param des pointer points to the following three-dimensional tensor
	 * @return the pointer pointing to an allocated three-dimensional vector
	 *
	 * NOTE: You need to free the pointer manually, it is allocated in the heap
	 */
	std::vector<std::vector<std::vector<double>>> *
		toTensor(size_t depth, size_t height, size_t width) const;

	/* Precondition: des need to be nullptr; the length of src shoud meet with
	 *		depth * heigt * width
	 * Parameters depth, height, width represent the following size of tensor:
	 *		double tensor[depth][height][width];
	 * @param src the one-dimensional source array
	 * @param des pointer points to the following three-dimensional tensor
	 * @return the pointer pointing to the destination tensor
	 */
	static double*** toTensor(const double * const src, double ***des,
		size_t depth, size_t height, size_t width);

	/* Precondition: the string includes double numbers that separate with space
	 *		and end with '\n'
	 */
	static int readLengthOfStringArray(const std::string &);
	
// Helper methods
private:

	inline double str2Double(const std::string& str) {
		std::istringstream iss(str);
		double num;
		iss >> num;
		return num;
	}

};

