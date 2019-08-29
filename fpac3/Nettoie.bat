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
del bin\fpac3.32.i??
rd /S /Q src\__astcache
rd /S /Q src\__history
rd /S /Q impcfgfpac3\src\__astcache
rd /S /Q impcfgfpac3\src\__history
attrib -S -H Thumbs.db /S
del /S Thumbs.db
