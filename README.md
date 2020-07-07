


In a shell, trying the following:

```
python setup.py build
python setup.py install
```


For macos, preface the build step with `ARCHFLAGS=""`.

The run a test: `python test.py`.

Here an example of a result using the Visual Studio compiler.

```
$ python test.py
True
volume = 646997B
trial 1:
time to parse 0.00040099430000000005 s
1.6134817876463579 GB/s
trial 2:
time to parse 0.00040198872500000007 s
1.6094904154339151 GB/s
trial 3:
time to parse 0.0003991265624999999 s
1.6210321757274677 GB/s
```
