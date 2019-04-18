%
% run from base eigen-matio directory
% run this:
%
%   octave --no-gui --path tests --eval mexeig_test
%
disp('building mex test function')

if (exist ('OCTAVE_VERSION', 'builtin') > 0)
    setenv('XTRA_CXXFLAGS','-std=c++11')
    mkoctfile --mex tests/mextest.cpp -v -Ibuild/eigenX/src/eigenX
else
    mex tests/mextest.cpp -v -Ibuild/eigenX/src/eigenX
end

% error msg
%mextest()

% error msg
%mextest([33])
A = [22 43];
B = [22 43+1i];

a = mextest(A)
b = mextest(B)

if norm(A - a) > 1e-9 || norm(B - b) > 1e-9
    exit(1)
end

exit(0)