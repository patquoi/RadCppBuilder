@echo off
rd /S /Q obj
rd /S /Q cur2cpp\obj
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
del bin\osmoz.32.i??
rd /S /Q src\__astcache
rd /S /Q src\__history
rd /S /Q src\__recovery
rd /S /Q cur2cpp\src\__astcache
rd /S /Q cur2cpp\src\__history
rd /S /Q cur2cpp\src\__recovery
attrib -S -H Thumbs.db /S
del /S Thumbs.db

del ..\osmoz-src-win64.zip
del ins\Output\ins*.exe

cls
"C:\Program Files\7-Zip\7z.exe" a ..\osmoz-src-win64.zip bin\licen?e.txt bin\lisezmoi.txt
"C:\Program Files\7-Zip\7z.exe" a -r ..\osmoz-src-win64.zip ins\*.* src\*.* cur2cpp\src\*.* res\*.*
echo Compiler et tester l'installation...
"C:\Program Files (x86)\Inno Setup 5\Compil32.exe" "C:\Users\Patrice Fouquet\Documents\Embarcadero\Studio\Projets\osmoz\ins\Osmoz.iss"
del ..\osmoz-src-win64.zip
del ..\osmoz.zip
"C:\Program Files\7-Zip\7z.exe" a -r ..\osmoz.zip
cls
echo Renommer ../osmoz.zip en osmoz-NNN (Rio).zip selon la version courante...
pause

