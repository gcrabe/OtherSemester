set PATH=%PATH%;C:\AMD\acml4.4.0\ifort64\libset LIB=%LIB%;C:\AMD\acml4.4.0\ifort64\lib
cl –MD –O2 –DNDEBUG Matr_Mult_BLAS.cpp libacml_dll.lib
test.exe