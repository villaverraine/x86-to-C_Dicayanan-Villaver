nasm -f win64 imgCvtGrayIntToDouble.asm
gcc -c imgCvtGrayIntToDouble_C.c -o imgCvtGrayIntToDouble_C.obj -m64
gcc imgCvtGrayIntToDouble_C.obj imgCvtGrayIntToDouble.obj -o imgCvtGrayIntToDouble.exe -m64
imgCvtGrayIntToDouble.exe