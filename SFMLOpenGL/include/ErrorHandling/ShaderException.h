#pragma once
#include <exception>
#include <vector>
#include <string>
#include "ErrorHandling/ExceptionCodes.h"
namespace spl
{

	class ShaderException : public std::runtime_error
	{
		
	public:
		ShaderException(ShaderErrorIDs errorID) :
			std::runtime_error(ExceptionCodes::getErrorMessage(errorID)){};
		~ShaderException(){};
		

	};




}


