disp('building mex test function')

if (exist ('OCTAVE_VERSION', 'builtin') > 0)
    setenv('XTRA_CXXFLAGS','-std=c++11')
    mkoctfile --mex  mextest.cpp -v -IeigenX/src/eigenX
else
    mex mextest.cpp -v -IeigenX/src/eigenX
end
    
a = mextest([22 43])
b = mextest([22 43+i])
