# Make pretty output.
env = Environment( CXXCOMSTR = '(COMPILE) $SOURCES',
                  LINKCOMSTR = '(LINK)    $TARGET')
Export('env')

# Compile the meat of it all
objects = SConscript('source/SConscript', build_dir='build')

# Unit tests are compiled and run every time the program is compiled.
tests = SConscript('source/test/SConscript', build_dir='build/test', export='env')
AddPostAction(tests, tests[0].path)
