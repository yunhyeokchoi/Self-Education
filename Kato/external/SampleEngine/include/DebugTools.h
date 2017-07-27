/******************************************************************************/
/*!
	\file   DebugTools.h
	\author Yunhyeok Choi
	\par    email: yunhyeokchoi\@gmail.com
	\date   18/7/2017
	\brief
		Defined macro functions exist no matter if the compilation happens in
		Debug or Release mode.
*/
/******************************************************************************/

#ifndef DEBUGTOOLS_H
#define DEBUGTOOLS_H

//TODO: Thinking of whether should I wrap it around the defined macro scope;
//inside "#if defined(DEBUG) | defined(_DEBUG)" and "#endif"
namespace DebugTools
{
	bool Assert(int expression,
							const char* outputMessage,
							const char* functionName,
							const char* fileName,
							unsigned int lineNumber);
	void CreateConsole();
	void DestroyConsole();
}

//When Visual Studio runs in Debug mode, it adds either two or one of the following lines.
//#define DEBUG
//#define _DEBUG

//Code for Debug Mode only.
#if defined(DEBUG) | defined(_DEBUG)

	/*! Use this macro instead of the function to ASSERT in debug only*/
	//If you want a macro to use more than one line you must put the \ at the end of every line except the last one.
	/*
		The __FUNCTION__ is a special identifier that visual studio will replace with the current function name.  
		The same is true for __FILE__ and __LINE__.
	*/
	/*
		in DEBUG mode
		if expression equals true, do nothing.
		if expression equals false, click yes to break into debugger.
		if expression equals false, click no to exit the program.
	*/
	#define DEBUG_ASSERT(exp, str)																			\
	if(DebugTools::Assert((exp),(str),__FUNCTION__,__FILE__, __LINE__))	\
	{                                                                   \
			DebugBreak();																										\
	}																																		\

	#define DEBUG_CREATE_CONSOLE() DebugTools::CreateConsole()
	#define DEBUG_DESTROY_CONSOLE() DebugTools::DestroyConsole()
//Code for Release mode.
#else
	//Do nothing in Release mode.
	#define DEBUG_ASSERT(exp, str)
	#define DEBUG_CREATE_CONSOLE()
	#define DEBUG_DESTROY_CONSOLE()
	/*
		Code blocks surrounded by # signs will only be executed, in the mode specified by the preprocessor if statements.

		This approach can benefit us in making our games retain themselves with good speed,
		as we can avoid additional checkings which don't need to be run necessarily on Release Mode.

		However, it would be redundant works for us to copy and paste code blocks surrounded by # signs wherever we want them to be.
		Better decision is to use preprocessor functions called macros.

		The ability to insert or remove code before compiling is what often makes preprocessor shine,
		despite its inability to let clients debug the code easily.
	*/

#endif
#endif