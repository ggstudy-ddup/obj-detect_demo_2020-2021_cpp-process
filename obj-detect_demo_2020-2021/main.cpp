#include <iostream>
#include <string>
using namespace std;

#include "PredictionModule.h"
#include "DoubleArray.h"
#include "Communicator.h"

#ifndef DEBUG
#define DEBUG
#endif // !DEBUG
#ifdef DEBUG
#define DEBUG_INFO(msg) \
	std::cerr << msg << '\n'; \
	std::fflush(stderr);
#endif // DEBUG

constexpr int VGG16_TENSOR_DEPTH  = 3;
constexpr int VGG16_TENSOR_HEIGHT = 224;
constexpr int VGG16_TENSOR_WIDTH  = 224;

int main_proccess(const std::string &module_file);

int main(int argc, char* argv[])
{
	if (argc != 2) return 0;
	try	{
		return main_proccess(argv[1]);
	}
	catch (const std::exception & e) {
		DEBUG_INFO(string("Unexpected error occurs!\n") + e.what());
		return -1;
	}
}

int main_proccess(const std::string &module_file)
{
	Communicator communicator;
DEBUG_INFO("Class <Communicator>, Object [communicator] => Communicator(), Action: [communicator] is constructed.")

	PredictionModule predictor(module_file);
DEBUG_INFO("Class <PredictionModule>, Object [predictor] => PredictionModule(), Action: [predictor] is constructed.")

	predictor.loadModule();
DEBUG_INFO("Class <PredictionModule>, Object [predictor] => loadModule(), Action: Module has been read into the memory.")

	while (true) {
        string message = communicator.listen();
DEBUG_INFO("Class <Communicator>, Object [communicator] => listen(), Action: Message has been read from the input space.")

		int length = DoubleArray::readLengthOfStringArray(message);
DEBUG_INFO("Class <DoubleArray>, static => readLengthOfStringArray(), Action: Amount of elements in the message is counted.")

		DoubleArray stretched_tensor(length);
DEBUG_INFO("Class <DoubleArray>, Object [stretched_tensor] => DoubleArray(), Action: [stretched_tensor] is constructed.")

		stretched_tensor.readFromString(message);
DEBUG_INFO("Class <DoubleArray>, Object [stretched_tensor] => readFromString(), Action: [stretched_tensor] is set with input data.")

    ClassResult3 result = predictor.predict(stretched_tensor,
        VGG16_TENSOR_DEPTH, VGG16_TENSOR_HEIGHT, VGG16_TENSOR_WIDTH);
DEBUG_INFO("Class <PredictionModule>, Object [predictor] => predict(), Action: Prediction using input tensor, set the tensor size to: 3 * 224 * 224")

    communicator.send(to_string(result.value[0]) + ' '
                    + to_string(result.value[1]) + ' '
                    + to_string(result.value[2]) + '\n');
	}

}
