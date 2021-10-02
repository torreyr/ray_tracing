
# This is a standard configuration file for mekpie

# the name of your project
name = 'ray_tracing' 
# the .c file containing `main`
main = 'main.cpp'
# the c compiler configuration to use (gcc_clang, avr_gcc, or emscripten)
cc = gcc_clang(cmd='g++', dbg='gdb')
# any libraries to load
libs = []
# additional compiler flags
flags = ['-std=c++11', '-Wall']

if options.release:
    flags += ['-O']
else:
    flags += ['-g']
