#pragma once
#include <vector>
#include <string>
#include <map>
#include <exception>
namespace spl
{
	enum ShaderErrorIDs
	{
		FileNotFound = 0,
		UnsupportedFormat = 1,
		EmptySourceFile = 2,

	};
	class ExceptionCodes
	{
	public:
		ExceptionCodes();
		~ExceptionCodes();

		//Error IDS

		static std::string getErrorMessage(int errorId);
	private:
		static std::map<int, std::string> errorMessages;

		static void populateErrorMessages();
	};
}



