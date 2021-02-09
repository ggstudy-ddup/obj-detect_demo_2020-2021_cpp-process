#include <torch/script.h>
#include <iostream>
#include <memory>
using namespace std;
int torch_main(int argc, char** argv)
{
	// load the module
	torch::jit::script::Module vgg16;
	try
	{
        vgg16 = torch::jit::load("C:\\Users\\JLWG\\Desktop\\module.pt");
	}
	catch (const c10::Error& e)
	{
		cerr << e.msg() << endl;
		return -1;
	}
	cout << "Module is successfully loaded!\n";

	std::vector<torch::jit::IValue> inputs;
    inputs.push_back(torch::ones({1, 3, 224, 224}));
 
	auto out = vgg16.forward(inputs);
	//c10::intrusive_ptr<c10::ivalue::Tuple> output;
	//at::Tensor output;
	at::Tensor output;
	try
	{
		auto temp = out.toTuple().get()->elements().back().toTensor();
		output = temp;
	}
	catch (const c10::Error& e)
	{
		cout << e.msg() << endl;
		return -1;
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
		return -1;
	}
    std::cout << endl << output.slice(/*dim=*/1, /*start=*/0, /*end=*/1) << '\n';

	try
	{
        std::cout << "0: " << output.index({ 0, 0 }).item() << '\n';
        std::cout << "1: " << output.index({ 0, 1 }).item() << '\n';
        std::cout << "2: " << output.index({ 0, 2 }).item() << '\n';
	}
	catch (const c10::Error& e)
	{
		cout << e.msg();
	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}

	return 0;
}