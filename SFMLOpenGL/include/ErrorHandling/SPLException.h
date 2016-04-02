#include <stdexcept>
#include <string>
#include "ErrorMessages.h"
namespace spl
{

	class SPLException : public std::runtime_error
	{

	public:
		SPLException(std::string err) :
			std::runtime_error(err){
				errorMessage = err;
			};

		//Overload for extraData
		SPLException(std::string err, std::string extraDat) :
			std::runtime_error(err){
				errorMessage = err;
				ExtraData(extraDat);
			};
	public:
		const char* what() const throw()
		{
			
			return errorMessage.c_str();
		}
		std::string ExtraData() const { return extraData; }
		void ExtraData(std::string val)
		{ 
			extraData = val; 
			errorMessage = errorMessage + ": " + extraData;
		}
		~SPLException(){};
	private:
		std::string extraData;
		std::string errorMessage;

	};




}