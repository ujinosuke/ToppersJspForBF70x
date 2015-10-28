
set APPNAME=sample1
set APPDIR=..\..
set CFGPATH=c:\bin
set VDSPPATH=C:\Analog Devices\CrossCore Embedded Studio 2.0.0

set JSPPATH=..\..\..
set JSPARCHPATH=%JSPPATH%\include\arch\bf70x

"%VDSPPATH%\pp.exe" %APPDIR%\%APPNAME%.cfg -D__ECC__ -D__ADSPLPBLACKFIN__ _ -DBLACKFIN707_BLIP2 -I"%JSPARCHPATH%;%JSPPATH%\cfg;%JSPPATH%\include" > %APPNAME%_pp.cfg
rem "%VDSPPATH%\pp.exe" %APPDIR%\%APPNAME%.cfg -D__ECC__ -D__ADSPLPBLACKFIN__ -I"%JSPARCHPATH%;%JSPPATH%\cfg;%JSPPATH%\include" > %APPNAME%_pp.cfg
"%CFGPATH%\cfg.exe" %APPNAME%_pp.cfg
del %APPNAME%_pp.cfg
