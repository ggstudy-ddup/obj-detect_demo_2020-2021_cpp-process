#pragma once
#include <string>
#include <torch/script.h>
#include "DoubleArray.h"
typedef struct struct_3ClassResult {
	double value[3];
} ClassResult3;
class PredictionModule
{
private:
	std::string file;
	torch::jit::script::Module *pModule;

public:
	PredictionModule(const std::string & file_full_path)
		: file(file_full_path), pModule(nullptr) {}
	~PredictionModule() { if (pModule) delete pModule; }

	void setModuleFile(const std::string & file_full_path) {
		file = file_full_path;
	}

	void loadModule() {
		if (pModule) delete pModule;
		pModule = new torch::jit::script::Module;
		*pModule = torch::jit::load(file);
		pModule->eval();
	}

	ClassResult3 predict(const std::vector<std::vector<std::vector<double>>> *tensor);

	ClassResult3 predict(const DoubleArray & arr, size_t depth, size_t height, size_t width) {
		std::vector<std::vector<std::vector<double>>> *tensor = arr.toTensor(depth, height, width);
		ClassResult3 result = PredictionModule::predict(tensor);
		delete tensor;
		return result;
	}

};

