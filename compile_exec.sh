mkdir -p build
cd build
if cmake .. ; then
    if cmake --build . ; then
        ./snddisplay
        rm snddisplay
    else
        echo "Compilation error"
    fi   
else
    echo "CMake file error"
fi    
