#include "PredictionModule.h"
using std::vector;

ClassResult3 PredictionModule::predict(const std::vector<std::vector<std::vector<double>>> *t)
{
    torch::Tensor tensor = torch::tensor(t);
	std::vector<torch::jit::IValue> inputs;
    inputs.push_back(tensor);
    at::Tensor output = pModule->forward(inputs).toTensor();
    ClassResult3 result;
    result.value[0] = output.index({ 0, 0 }).item().toDouble();
    result.value[1] = output.index({ 0, 1 }).item().toDouble();
    result.value[2] = output.index({ 0, 2 }).item().toDouble();
    return result;
}
