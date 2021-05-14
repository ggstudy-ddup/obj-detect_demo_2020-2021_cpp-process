#include "Communicator.h"

Communicator::Communicator(FILE* out_stream, FILE* in_stream)
{
	outputStream = out_stream;
	inputStream = in_stream;
}

void Communicator::send(const std::string& msg)
{
	std::cout << msg;
	std::fflush(this->outputStream);
}

std::string Communicator::listen(char endchar)
{
	std::string buffer;
	std::getline(std::cin, buffer, endchar);
	return buffer;
}

std::string Communicator::listen(const std::string& endchar)
{
	std::string buffer;
	std::getline(std::cin, buffer, *endchar.c_str());
	return buffer;
}
