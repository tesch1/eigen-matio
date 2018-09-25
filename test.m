disp('building mex test function')
mex mextest.cpp -v -IeigenX/src/eigenX

a = mextest([22 43])
b = mextest([22 43+i])
