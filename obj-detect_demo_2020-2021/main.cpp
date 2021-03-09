#include <iostream>
#include <string>
#include <torch/script.h>
#include "VGG16_Predicting.h"
using namespace std;

int main_proccess(const std::string &module_file);

int main(int argc, char* argv[])
{
	if (2 != argc) exit(-1);
	try {
		return main_proccess(argv[1]);
	}
	catch (const torch::Error &e) {
		std::cerr << "\n******************************\n"
					   "        An Error Occurs       \n"
					   "******************************\n";
		std::cerr << "Type: Torch Error\n";
		std::cerr << "Brief:\n" << e.msg() << '\n';
		std::cerr << "Context:\n" << e.context() << '\n';
		std::cerr << "Backtrace:\n" << e.backtrace() << '\n';
	}
	catch (const std::exception &e) {
		std::cerr << "\n******************************\n"
					   "        An Error Occurs       \n"
					   "******************************\n";
		std::cerr << "Type: Others\n";
		std::cerr << "Info:\n" << e.what() << '\n';
	}
    return -1;
	//return main_proccess("C:\\Users\\JLWG\\Desktop\\module.pt");
}

int main_proccess(const std::string &module_file)
{
	/**
	 *	load the module
	 */
	VGG16_Predicting model(module_file);
	model.load();
	// send msg that loading is finished
    Json::Value root;
    Json::StreamWriterBuilder writerBuilder;
    std::ostringstream stream;
	root["type"] = "event";
	root["data"] = "loaded";
	// write
    std::unique_ptr<Json::StreamWriter> jsonWriter(writerBuilder.newStreamWriter());
    jsonWriter->write(root, &stream);	// write to stream 
	// send
	out(stream.str());

	/**
	 *	main loop
	 */
	while (true)
	{
		std::string msg("");
		// get tensor
		if (model.readStream(msg))
		{
			// predict
			model.predict();
			// send prediction
			model.sendPrediction();
		}
		else
		{
			// empty input
			if (msg.empty()) continue;

			JSONCPP_STRING errs;
            Json::Value root;
            Json::CharReaderBuilder readerBuilder;

            std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());
            if (!jsonReader->parse(msg.c_str(), msg.c_str() + msg.length(), &root, &errs)
				|| !errs.empty())
                std::cout << "parseJson err. " << errs << std::endl;
			// recieving a command
			if ("command" == root["type"].asString())
			{
				// exit
				if ("exit" == root["data"].asString()) break;
			}

			continue;
		}
	}
	return 0;
}
