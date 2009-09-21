objects = SConscript('source/SConscript', build_dir='build')

tests = SConscript('source/test/SConscript', build_dir='build/test')
AddPostAction(tests, tests[0].path)
