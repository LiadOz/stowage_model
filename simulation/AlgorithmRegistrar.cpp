#include <vector>



// AlgorithmRegistrar.cpp
#include "AlgorithmRegistrar.h"
#include <dlfcn.h>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

void AlgorithmRegistrar::DlCloser::operator()(void *dlhandle) const noexcept 
{
	dlclose(dlhandle);
}

AlgorithmRegistrar& AlgorithmRegistrar::getInstance()
{
	static AlgorithmRegistrar instance;
	return instance;
}

AlgorithmRegistrar::~AlgorithmRegistrar()
{
	// Remove all factories - before closing all handles!
	_factories.clear();
	_handles.clear();
}

bool AlgorithmRegistrar::loadAlgorithmFromFile(const std::string& file_path, std::string& error) {

    auto currentAlgs = _factories.size();
    std::string filename = fs::path(file_path).stem().string();
    // Try to load given module
    DlHandler algo_handle(dlopen(file_path.c_str(), RTLD_LAZY));

    // Check if dlopen succeeded
    if (algo_handle != nullptr) {
        if (currentAlgs == _factories.size()){ // checking if the alg registered
            error = "Algorithm " + filename + " didn't register itself";
            return false;
        }
        // if algorithm registered twice
        _handles[file_path] = std::move(algo_handle);
        _names.push_back(filename);
        return true;
    }

    if (currentAlgs != _factories.size() + 1){
        error = "Algorithm " + filename + " registered itself more than once";
        for (size_t i = 0; i < currentAlgs - _factories.size() - 1; ++i) {
            _factories.pop_back();
        }
        return false;
    }

    const char *dlopen_error = dlerror();
    error = dlopen_error ? dlopen_error : "Failed to open shared object!";
    return false;
}
