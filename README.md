


Prerequisite: You should know about Python, pip and setuptools; and be interested in simdjson. If not, then this is not for you.

In a shell, trying the following:

```
python setup.py build
python setup.py install
```


For macos, preface the build step with `ARCHFLAGS=""`.

The run a test: `python test.py`.


# Visual Studio

Here an example of a result using the Visual Studio compiler.

```
$ python test.py
True
volume = 646997B
trial 1:
time to parse 0.0003297345375 s
1.962175406026431 GB/s
trial 2:
time to parse 0.00031751438750000005 s
2.0376934887714335 GB/s
trial 3:
time to parse 0.00032592783749999996 s
1.9850927891361843 GB/s
```

# macOS

```
ARCHFLAGS=""  python3 setup.py build
python3 setup.py install
```

```
$ python3 test.py
True
volume = 631515B
trial 1:
time to parse 0.00022058525649999998 s
2.8629066603098203 GB/s
trial 2:
time to parse 0.000218998752 s
2.8836465698215488 GB/s
trial 3:
time to parse 0.00021954357225000004 s
2.876490500395417 GB/s
```
