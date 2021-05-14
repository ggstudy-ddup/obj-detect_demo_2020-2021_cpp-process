#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#define FileStream(x) (FILE(*x)(unsigned int))
class Communicator
{
private:
	FILE *inputStream;
	FILE *outputStream;

public:
	Communicator(FILE *out_stream = stdout, FILE *in_stream = stdin);
	~Communicator() {}

	void send(const std::string & msg);

	/* This function would keep listen to the input stream until the end char
	 * is detected
	 * @param endchar if this char appears, the listen would stop and return
	 * @return the string listen from the input stream
	 */
	std::string listen(char endchar = '\n');
	/* This function would keep listen to the input stream until the end char
	 * is detected
	 * @param endchar if this char appears, the listen would stop and return
	 * @return the string listen from the input stream
	 */
	std::string listen(const std::string & endchar);

};

