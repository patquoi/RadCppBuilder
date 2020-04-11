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
del bin\osmotik.32.i??
rd /S /Q src\__astcache
rd /S /Q src\__history
attrib -S -H Thumbs.db /S
del /S Thumbs.db

del ..\osmtk-src-win64.zip
del ins\Output\ins*.exe

cls
"C:\Program Files\7-Zip\7z.exe" a ..\osmtk-src-win64.zip bin\licen?e.txt bin\lisezmoi.txt
"C:\Program Files\7-Zip\7z.exe" a -r ..\osmtk-src-win64.zip ins\*.* src\*.* res\*.*
echo Compiler et tester l'installation...
"C:\Program Files (x86)\Inno Setup 5\Compil32.exe" "C:\Users\Patrice Fouquet\Documents\Embarcadero\Studio\Projets\osmotik\ins\Osmotik.iss"
del ..\osmtk-src-win64.zip
del ..\osmotik.zip
"C:\Program Files\7-Zip\7z.exe" a -r ..\osmotik.zip
cls
echo Renommer ../osmotik.zip en osmotik-NNN (Rio).zip selon la version courante...
pause

