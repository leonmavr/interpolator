#!/usr/bin/env python3
from matplotlib import pyplot as plt
import os
this_script_path = os.path.abspath(__file__)
this_script_folder = os.path.dirname(this_script_path)

"""
This quick script reads the output dumped by main.cpp and plots it.
The file it reads (../out.txt) is structured as follows:
In the first part, there are the anchor points provided to the interpolator.
In the second part, there are the interpolation results.
Note that the interpolator is not necessarily linear.
The two parts are separated by a newline, so the file looks as follows:
x, y
x, y
...

x, y
x, y
...
"""
with open(os.path.join(this_script_folder, '..', 'out.txt')) as f:
    lines = f.readlines()

xy_anch = []
xy_interp = []
separate = False
for l in lines:
    if l.strip() == "":
        separate = True
        continue
    if not separate:
        xy_anch.append((float(l.split(',')[0]), float(l.split(',')[1])))
    else:
        xy_interp.append((float(l.split(',')[0]), float(l.split(',')[1])))

plt.plot([xy[0] for xy in xy_anch], [xy[1] for xy in xy_anch], 'ro')
plt.plot([xy[0] for xy in xy_interp], [xy[1] for xy in xy_interp], 'r-')
plt.xlabel('x')
plt.ylabel('y')
plt.grid(True)
plot_file = os.path.join(this_script_folder, 'result.jpg')
plt.savefig(plot_file)
print("Plot saved at:\n{}".format(os.path.abspath(plot_file)))
