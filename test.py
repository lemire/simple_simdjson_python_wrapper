import simdjson_demo
import os
import timeit
thiscript = os.path.dirname(os.path.realpath(__file__))


myfile = thiscript+"/jsonexamples/twitter.json"
volume = os.path.getsize(myfile)

simdjson_demo.load_file(myfile)
print(simdjson_demo.is_ok())
repeat = 8000

print("volume = "+str(volume)+"B")

for i in range(3):
  print("trial "+str(i+1)+":")
  gb = volume / 1000000000.

  times = timeit.timeit(simdjson_demo.is_ok, number=repeat) / repeat

  print("time to parse "+ str(times)+ " s")

  print(str(gb/times)+" GB/s")