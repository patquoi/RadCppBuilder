@echo off
rd /S /Q obj
mkdir obj
del /S *.obj
del /S *.pch
del /S *.map
del /S *.tds
del /S *.pdi
del /S *.cbproj.local
del /S *.groupproj.local
rd /S /Q src\__astcache
rd /S /Q src\__history
rd /S /Q impcfgfpac3\src\__astcache
rd /S /Q impcfgfpac3\src\__history
attrib -S -H Thumbs.db /S
del /S Thumbs.db

del ..\fpac3-src-win64.zip
del install\Output\ins*.exe

cls
"C:\Program Files\7-Zip\7z.exe" a ..\fpac3-src-win64.zip bin\licen?e.txt bin\lisez-moi.txt 
"C:\Program Files\7-Zip\7z.exe" a -r ..\fpac3-src-win64.zip ins\*.* impcfgfpac3\src\*.* src\*.* png\*.*
echo Compiler et tester l'installation...
"C:\Program Files (x86)\Inno Setup 5\Compil32.exe" "C:\Users\Patrice Fouquet\Documents\Embarcadero\Studio\Projets\fpac3\ins\insfpac3.iss"
del ..\fpac3-src-win64.zip
"C:\Program Files\7-Zip\7z.exe" a -r ..\fpac3.zip
cls
echo Renommer ../fpac3.zip en fpac3-NNN (Rio).zip selon la version courante...
pause

