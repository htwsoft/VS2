@echo off
echo.
set /p NAME=gib bitte idl datei name an:
echo IDL DATEI: %NAME%

idlj -fall %NAME%

pause