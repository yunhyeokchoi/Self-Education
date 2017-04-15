::https://ss64.com/nt/setx.html
::setx set environment variables permanently, 
::SETX can be used to set Environment Variables for the machine (HKLM),
::or currently logged on user (HKCU):
::SETX [/s Computer [Credentials]] Variable Value [/m]
::Variable; The name of the environment variable that you want to set.
::Value; The value to which you want to set the environment variable.
::/m; Set the variable in the system environment HKLM.
::    (The default is the local environment HKCU)

::https://en.wikipedia.org/wiki/Batch_file
::The @ symbol at the start of any line prevents the prompt,
::from displaying that command as it is executed.
::https://ss64.com/nt/goto.html
::goto directs a batch program to jump to a labelled line.

::@if "%VSINSTALLDIR%"=="" goto error_no_VSINSTALLDIR

::setx INCLUDE "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\include;" -m
::setx LIB "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\lib;" -m
::setx PATH "C:\cygwin64\bin" -m

:::error_no_VSINSTALLDIR
::@echo ERROR: Cannot determine the location of the VS installation.
::@goto end

:::end
::setlocal enabledelayedexpansion

:: Suppress the command from being echoed to the prompt.
@echo off

SETLOCAL enabledelayedexpansion

:: set a variable with name 'STDERR',
:: which will be a name of the text file created,
:: storing a STDERR from the command executed
set STDERR=stderr.log
set FILEPATH=filepath.log
set CONTENT=

set CURRENT=%cd%
echo %CURRENT%

::return value of the function CheckValidProgram when looking for the validity of setx.exe
set SETXNOTFOUND=
::Check if the program 'setx' can be used directly from the command line,
::as it's not internal and there's a possibility of it to be not found.
call:CheckValidProgram setx.exe %STDERR% SETXNOTFOUND

IF "%SETXNOTFOUND%"=="1" (
  echo Current machine cannot locate the directory where setx.exe is.
  echo Finding where setx.exe is located.
  
  set SETXDIR=
  FOR %%G IN (c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z) DO (

    IF "!SETXNOTFOUND!"=="1" (
      echo Start looking up %%G drive.
      
      REM Move to the specific drive
      cd %%G: 1> nul 2> nul  
      
      REM Check if the drive specified actually exists.
      REM If exists, then do the search for the program.
      IF "!errorlevel!"=="0" (
      
        echo Search setx.exe in the %%G drive.
        REM Move to the root directory of the given drive
        cd \
        
        REM Print out the list of directories where the given file dwells in,
        REM to the filepath.log located in the original directory.
        dir setx.exe /b /s > %CURRENT%/%FILEPATH%
        cd %CURRENT%
        
        call:FindLineHasSubstring %FILEPATH% System32 SETXDIR
        IF NOT "!SETXDIR!"=="0" (
          REM Extract substring "setx.exe" from the string; just pure directory
          set SETXDIR=!SETXDIR:\setx.exe=!
          
          echo Found directory where setx.exe is located; !SETXDIR!
          set SETXNOTFOUND=0
        )
      )
    ) 
  )
  
  ::setx.exe's location has been found
  IF "!SETXNOTFOUND!"=="0" (
    ::change directory to where setx.exe is.
    cd !SETXDIR!
    set LASTLETTER=%PATH:~-1%
    echo !LASTLETTER!
    IF "!LASTLETTER!"==";" (
      echo %PATH%!SETXDIR!
      setx PATH %PATH%!SETXDIR! /m
    ) ELSE (
      echo %PATH%;!SETXDIR!
      setx PATH %PATH%;!SETXDIR! /m
    )
  )
)

::%1 string to check
:::CheckLastLetterIsSC
::FOR /F %%G IN (%1) DO (
::
::)

:: echo %errorlevel%
:: echo %RETURN%

:: IF EXIST STDERR DEL STDERR
:: IF EXIST FILEPATH DEL FILEPATH

goto:eof

::It takes one parameter,
::%1 output file to check
::%2 substring to extract
::%3 original string
:FindLineHasSubstring
FOR /F "tokens=*" %%G IN (%1) DO (

  set TEMP=%%G
  
  REM If found the substring "System32" from the TEMP, replace it with no character; extract
  set TEMP=!TEMP:%2=!
  
  REM If the modified string is not same as the original,
  REM meaning the original string contains System32 as part of the string,
  REM the original string is where the program resides.
  IF NOT "%%G"=="!TEMP!" (
    set %3=%%G
    call:next
  )
)
:next
goto:eof

::******************************************************************************
::Function Name: CheckValidProgram
::
::Brief:
::This function checks if the correct path has been set, 
::in order to execute a given program.
::Other way around would be checking a %errorlevel%,
::to see if its set to 9009; from not verified source.
::http://stackoverflow.com/questions/23091906/official-ms-reference-for-cmd-exe-errorlevel-9009
::******************************************************************************
::It takes two parameter, 
::%1 name of the program
::%2 output file to create
::%3 return value; 0 if program is reachable, and 1 if not.
:CheckValidProgram
::STDOUT to nul & STDERR to stderr.log
  %1 1> nul 2> %2
call:ConcatenateSTDERR %2
::If it prints the specific error message, there's something wrong in the path.
  IF "%CONTENT%"=="'%1' is not recognized as an internal or external command, operable program or batch file." (
    set %3=1
  ) ELSE (
    set %3=0
  )
goto:eof

::It takes one parameter,
::%1 output file to check
:ConcatenateSTDERR
::Delayed variable expansion is often useful when working with FOR Loops, 
::normally an entire FOR loop is evaluated as a single command,
::even if it spans multiple lines of a batch script;
::meaning the change would take effect after the for loop, not during the for loop.
  FOR /F "tokens=*" %%G IN (%1) DO (
    IF "!CONTENT!"=="" (
      set CONTENT=%%G
    ) ELSE (
      set CONTENT=!CONTENT! %%G
    )
  )
goto:eof