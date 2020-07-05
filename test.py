import simdjson_demo
import os
import timeit
thiscript = os.path.dirname(os.path.realpath(__file__))


myfile = thiscript+"/jsonexamples/twitter.json"
volume = os.path.getsize(myfile)

simdjson_demo.load_file(myfile)
print(simdjson_demo.is_ok())
repeat = 100

print("volume = "+str(volume)+"B")

gb = volume / 1000000000.

times = timeit.timeit(simdjson_demo.is_ok, number=repeat) / repeat

print("time to parse "+ str(times)+ " s")

print(gb/times)