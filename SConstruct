# Make pretty output.
env = Environment( CXXCOMSTR = '(COMPILE) $SOURCES',
                  LINKCOMSTR = '(LINK)    $TARGET',
                     CPPPATH = ['/opt/local/include', '#header'], LIBPATH='/opt/local/lib')
Export('env')

# Compile the meat of it all
implementation_objects = SConscript('implementation/SConscript', build_dir='build', export='env')
workload_objects = SConscript('workload/SConscript', build_dir='build/workload', export='env')

# Unit tests are compiled and run every time the program is compiled.
tests = SConscript('test/SConscript', build_dir='build/test', export='env')
AddPostAction(tests, tests[0].path)
