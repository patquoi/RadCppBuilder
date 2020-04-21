@echo off
rd /S /Q obj
mkdir obj
del /S *.obj
del /S *.pch
del /S *.map
del /S *.tds
del /S *.pdi
del /S *.tmp
del /S *.cbproj.local
del /S *.groupproj.local
del /S *.deployproj
del bin\lebrgw.32.i??
rd /S /Q src\__astcache
rd /S /Q src\__history
rd /S /Q src\__recovery
attrib -S -H Thumbs.db /S
del /S Thumbs.db

del ..\lebrgw-src-win64.zip
del ins\Output\ins*.exe

cls
"C:\Program Files\7-Zip\7z.exe" a ..\lebrgw-src-win64.zip bin\licen?e.txt bin\lisezmoi.txt 
"C:\Program Files\7-Zip\7z.exe" a -r ..\lebrgw-src-win64.zip ins\*.* src\*.* res\*.*
echo Compiler et tester l'installation...
"C:\Program Files (x86)\Inno Setup 5\Compil32.exe" "C:\Users\Patrice Fouquet\Documents\Embarcadero\Studio\Projets\lebrgw\ins\Lebrgw.iss"
del ..\lebrgw-src-win64.zip
"C:\Program Files\7-Zip\7z.exe" a -r ..\lebrgw.zip
cls
echo Renommer ../lebrgw.zip en lebrgw-NNN (Rio).zip selon la version courante...
pause

