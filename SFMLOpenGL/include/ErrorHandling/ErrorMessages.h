namespace spl
{
	namespace ErrorMessages
	{

		//String literals

		//Shader Errors
		const char SHADER_FILE_NOT_FOUND[] = "Shader file not found.";		
		const char SHADER_UNSUPPORTED_FORMAT[] = "Shader file extension not supported. Please use .cs, .fs, .gs, or .vs";
		const char SHADER_FILE_EMPTY[] = "Shader file is empty.";
		const char SHADER_COMPILATION_ERROR[] = "Shader compilation error.";
		const char SHADER_ADD_ATTRIBUTE[] = "Shader: Could not add attribute/uniform.";


		//Buffer Errors
		const char SSBO_GENERATION_ERROR[] = "Buffer could not be created.";

		const char TEXTURE_ERROR[] = "Unknown texture error.";

	}
}