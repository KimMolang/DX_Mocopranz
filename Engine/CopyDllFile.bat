xcopy	/y	..\Header\*.h				..\..\Reference\Header\Engine\

xcopy	/y	.\Code\*.h				..\..\Reference\Header\Engine\
xcopy	/y	.\Code\*.inl				..\..\Reference\Header\Engine\
xcopy	/y	.\bin\{out}\%1\%2\System.lib		..\..\Reference\Library\Engine\%1\
xcopy	/y	.\bin\{out}\%1\%2\System.dll		..\..\Client\bin\{out}\%1\Debug\
xcopy	/y	.\bin\{out}\%1\%2\System.dll		..\..\Client\bin\{out}\%1\Release\