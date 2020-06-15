// AlgorithmRegistrar.h
#pragma once

#include <map>
#include <functional>
#include <memory> 
#include "../interfaces/AbstractAlgorithm.h"

// A singleton to hold algorithm factories and .so handles 
class AlgorithmRegistrar
{
	struct DlCloser
	{
    		void operator()(void *dlhandle) const noexcept;
	};

	// Algorithm factories signature type
	typedef std::function<std::unique_ptr<AbstractAlgorithm>()> AlgorithmFactory;
	typedef std::unique_ptr<void, DlCloser> DlHandler; 

	// Dynamic-linker handles map (to keep algorithms code in memory)
	std::map<std::string, DlHandler> _handles;

	// Algorithm factories
	std::vector<AlgorithmFactory> _factories;
    std::vector<std::string> _names;

	// iteration over factories
	typedef decltype(_factories)::const_iterator const_iterator;

	// Default Constructor
	AlgorithmRegistrar() = default;
	~AlgorithmRegistrar();

	// Prevent copy - this is singelton
	AlgorithmRegistrar(const AlgorithmRegistrar&) = delete;
	AlgorithmRegistrar& operator=(const AlgorithmRegistrar&) = delete;

	// AlgorithmRegistration needs to internally registerFactory
	friend class AlgorithmRegistration;

	// AlgorithmRegistration's internal interface to support register-on-load policy
	inline void registerFactory(AlgorithmFactory factory) { _factories.push_back(factory); }

public:
        // Gets a reference to AlgorithmRegistrar's singleton instance
        static AlgorithmRegistrar& getInstance();

        // Rreturns an iterator to the first algorithm factory
        inline const_iterator begin() const { return _factories.begin(); }

        // Returns an iterator that points to the end
        inline const_iterator end() const { return _factories.end(); }

        // Loads an algorithm from given shared object file into the registrar
        // parameters:
        //   file_path - shared object file path to load
        //   error - On failure, it will be filled with a Human-readable error message.
        // Returns:
        //   true if given shared object's algorithm was registered successfully, false oterwise
        bool loadAlgorithmFromFile(const std::string& file_path, std::string& error);

        // uses the factory iterator to get algorithm name
        std::string getAlgorithmName(int index){
            return _names[index];
        }
        AlgorithmFactory getAlgorithmByIndex(int index){
            return _factories[index];
        }
};
