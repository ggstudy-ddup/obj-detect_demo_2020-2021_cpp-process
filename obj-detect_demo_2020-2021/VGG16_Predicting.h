#pragma once
#include <torch/script.h>
#include <string>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <json/json.h>
constexpr unsigned int TENSOR_SIZE = 3 * 224 * 224;
constexpr unsigned int N_CLASSES = 3;

inline void out(const std::string& msg) {
	std::cout << msg;
	std::fflush(stdout);
}

inline void in(std::string &buffer) {
	std::getline(std::cin, buffer);
}

class VGG16_Predicting
{
private:
	torch::jit::script::Module *pModule;
	std::string fname;
	std::vector<double> *pTensor;
	std::vector<double> *pPrediction;

	void read_tensor_from_json(const Json::Value &root);
	void create_tensor_msg(const std::vector<double> &prediction,std::string &doc);

public:
	VGG16_Predicting();
	VGG16_Predicting(const std::string &full_path);
	~VGG16_Predicting();

	inline std::string getModuleFileName() { return fname; }
	inline std::vector<double> getPrediction() { return *pPrediction; }

	void load(void);
	void load(const std::string &full_path);

	std::vector<double> predict(const torch::jit::IValue &tensor);
	std::vector<double> predict(void);

	/**
	 * Read the tensor from the stream (stdin)
	 * @ret TRUE when a tensor is read from the stream
	 * @ret FALSE when no tensor is read from the stream
	 */
	bool readStream(std::string &msg);

	void sendPrediction(const std::vector<double> &);
	void sendPrediction(void);

};
