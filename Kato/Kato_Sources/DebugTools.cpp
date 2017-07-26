#include "DebugTools.h"

/*
	stringstream class
	It enables formatting the string buffer it has, which can be accessed as a C++ string object
*/
#include <sstream>

/*
	http://support.microsoft.com/kb/166474
	To speed the build process, Visual C++ and the Windows Headers provide the following new defines:

	VC_EXTRALEAN
	WIN32_LEAN_AND_MEAN

	You can use them to reduce the size of the Win32 header files.
*/
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

bool DebugTools::Assert(int expression,
						const char* outputMessage,
						const char* functionName,
						const char* fileName,
						unsigned int lineNumber)
{
	if (!expression)
	{
		std::stringstream ssObject;

		//format string buffer of stringstream object
		ssObject << "ASSERTION FAILURE : ";
		ssObject << "\nFile : " << fileName;
		ssObject << "\nLine Number : " << lineNumber;
		ssObject << "\nFunction Name : " << functionName;
		ssObject << "\nDescription : " << outputMessage;

		//multi byte string to wide character string
		/*
		  https://msdn.microsoft.com/en-us/library/eyktyxsx.aspx

		  errno_t mbstowcs_s(size_t *pReturnValue, //	[out] The number of characters converted.
		  wchar_t *wcstr,			 // [out] Address of buffer for the resulting converted wide character string.
		  size_t sizeInWords,	 // [in] The size of the wcstr buffer in words.
		  const char *mbstr,		 //	[in] The address of a sequence of null terminated multibyte characters.
		  size_t count);				 // [in] The maximum number of wide characters to store in the wcstr buffer, not including the terminating null, or _TRUNCATE.

		  If mbstowcs_s successfully converts the source string, it puts the size in wide characters of the converted string,
		  including the null terminator, into *``pReturnValue (provided pReturnValue is not NULL).
		  This occurs even if the wcstr argument is NULL and provides a way to determine the required buffer size.
		  Note that if wcstr is NULL, count is ignored, and sizeInWords must be 0.
		*/

		/*
		  figure out the bufferSize
		  #1 mbstowcs
		  #2 strlen
		*/
		size_t bufferSize = 0;
		mbstowcs_s(&bufferSize, 0, 0, ssObject.str().c_str(), 0);
		//unsigned int bufferSize2 = 0; bufferSize2 = strlen(ssObject.str().c_str());

		wchar_t* wcstr = 0;
		wcstr = reinterpret_cast<wchar_t*>(malloc(sizeof(WCHAR) * bufferSize));
		mbstowcs_s(0, wcstr, bufferSize, ssObject.str().c_str(), (bufferSize - 1));

		int returnValue = MessageBox(NULL, wcstr, L"ASSERT!",
			MB_TASKMODAL | MB_SETFOREGROUND | MB_YESNO | MB_ICONERROR);
		free(wcstr);

		//clicking yes will end this function call and break into the debugger
		if (returnValue == IDYES)
			return true;

		//clicking no will exit the program
		ExitProcess((unsigned)(-1));
	}

	//never returns false, but just to make sure compiler doesn't complain
	return false;
}

void DebugTools::CreateConsole()
{
	AllocConsole();

	FILE* pDummy = 0;
	/*
		Pretty much MSVS is the only platform to work on this project;
		may not have to consider the case of using freopen instead of freopen_s

		#1 Closes any file related with stdout stream.
		#2 Disassociate stdout with the file.
		#3 Open the file under the name "CONOUT$";
		a special file name denoting current console output.
		#4 Associate the file with stdout stream.
	*/
	freopen_s(&pDummy, "CONOUT$", "w", stdout);
	freopen_s(&pDummy, "CONOUT$", "w", stderr);

	//A for ANSI, and W for UNICODE
	SetConsoleTitleA("Debug Console");
}

void DebugTools::DestroyConsole()
{
	FreeConsole();
}