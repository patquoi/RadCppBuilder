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
