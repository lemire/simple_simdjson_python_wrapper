

import platform


PLATFORM_WINDOWS = (platform.system() == 'Windows')
PLATFORM_MACOSX = (platform.system() == 'Darwin')

from setuptools import setup, Extension
if PLATFORM_WINDOWS:
    cpp_args = []
elif PLATFORM_MACOSX:
    cpp_args=["-stdlib=libc++", "-mmacosx-version-min=10.9",'-std=c++11']
else:
    cpp_args = ['-std=c++11']

module1 = Extension('simdjson', sources = ['src/simple_wrapper.cpp','src/simdjson.cpp'], include_dirs=['include'],  language='c++',extra_compile_args = cpp_args)

setup (name = 'simdjson',
        version = '1.0.0',
        description = 'Fast JSON Parsing',
        ext_modules = [module1])