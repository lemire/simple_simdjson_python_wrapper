

import platform


PLATFORM_WINDOWS = (platform.system() == 'Windows')
PLATFORM_MACOSX = (platform.system() == 'Darwin')
link_args=[]
from setuptools import setup, Extension
if PLATFORM_WINDOWS:
    cpp_args = ["/Ob2", "/d2inlinestats","/W3" , "/w34710","/w34714"]
    link_args=[]
elif PLATFORM_MACOSX:
    cpp_args=["-stdlib=libc++", "-mmacosx-version-min=10.9",'-std=c++11']
else:
    cpp_args = ['-std=c++11']

module1 = Extension('simdjson_demo', sources = ['src/simple_wrapper.cpp','src/simdjson.cpp'], include_dirs=['include'],  language='c++',extra_compile_args = cpp_args,extra_link_args=link_args)

setup (name = 'simdjson_demo',
        version = '1.0.0',
        description = 'Fast JSON Parsing',
        ext_modules = [module1])