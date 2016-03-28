#include "stdafx.h"
#include "..\..\include\ErrorHandling\ExceptionCodes.h"
#include <utility>
namespace spl
{
	std::map<int, std::string> spl::ExceptionCodes::errorMessages;

	ExceptionCodes::ExceptionCodes()
	{
	}


	ExceptionCodes::~ExceptionCodes()
	{
	}

	std::string ExceptionCodes::getErrorMessage(int errorId)
	{
		//Check to see if the error message vector is filled yet.
		if (errorMessages.size() == 0)
		{
			//Fill error message vector
			populateErrorMessages();
		}
		auto it = errorMessages.find(errorId);
		if (it == errorMessages.end())
		{
			//Error not found
			return std::string("Unknown Error");
		}
		return it->second;
	}

	void ExceptionCodes::populateErrorMessages()
	{
		errorMessages.insert(std::make_pair(ShaderErrorIDs::FileNotFound,"Shader file not found."));
		errorMessages.insert(std::make_pair(ShaderErrorIDs::UnsupportedFormat, "Shader file extension not supported. Please use .cs, .fs, .gs, or .vs"));
		errorMessages.insert(std::make_pair(ShaderErrorIDs::EmptySourceFile, "Shader file is empty."));


	}
}