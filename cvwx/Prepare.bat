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
del bin\cvw.32.i??
rd /S /Q src\__astcache
rd /S /Q src\__history
attrib -S -H Thumbs.db /S
del /S Thumbs.db

del ..\cvw-src-win64.zip
del ins\Output\ins*.exe

cls
"C:\Program Files\7-Zip\7z.exe" a ..\cvw-src-win64.zip bin\licen?e.txt bin\lisezmoi.txt bin\infosrc.txt
"C:\Program Files\7-Zip\7z.exe" a -r ..\cvw-src-win64.zip ins\*.* src\*.* res\*.*
echo Compiler et tester l'installation...
"C:\Program Files (x86)\Inno Setup 5\Compil32.exe" "C:\Users\Patrice Fouquet\Documents\Embarcadero\Studio\Projets\cvwx\ins\inscvw95.iss"
del ..\cvw-src-win64.zip
"C:\Program Files\7-Zip\7z.exe" a -r ..\cvw.zip
cls
echo Renommer ../cvw.zip en cvw-NNN (Rio).zip selon la version courante...
pause

