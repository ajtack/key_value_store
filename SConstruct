# Make pretty output.
env = Environment( CXXCOMSTR = '(COMPILE) $SOURCES',
                  LINKCOMSTR = '(LINK)    $TARGET')
Export('env')

# Compile the meat of it all
objects = SConscript('implementation/SConscript', build_dir='build')

# Unit tests are compiled and run every time the program is compiled.
tests = SConscript('test/SConscript', build_dir='build/test', export='env')
AddPostAction(tests, tests[0].path)
