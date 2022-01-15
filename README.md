# Interpolator


### About
Numerical 1D interpolation in C++ via linked lists. It supports the following two basic operations:
```
void insert(double x, double y);
double interpolate(double x);
```
Both operations run in linear time. It currently implements the following two interpolation types:
* Linear
* Smoothstep

| Original | Linear | Smoothstep
| ------------- | ------------- | -------------|
| ![alt text](https://raw.githubusercontent.com/0xLeo/interpolator/master/assets/original.jpg) | ![alt text](https://raw.githubusercontent.com/0xLeo/interpolator/master/assets/result_linear.jpg)| ![alt text](https://raw.githubusercontent.com/0xLeo/interpolator/master/assets/result_smoothstep.jpg) |


### Compilation and execution instructions

To compile it, you only need a version of the g++ compiler that supports the C++17 and newer standards. No dependencies are needed. The project is built by a `Makefile` and unit tests are compiled with the Catch2 library. To compile it and run the driver code execute:
```
cd interpolator
make
./main
```
`main` by default outputs the interpolation results in a file called `out.txt`. You can plot them by running the `scripts/plot.py` script.  

To build and run the unit tests execute:
```
make test
```
To clean everything but the Catch2 object file (since it's heavy and doesn't need to change often):
```
make quickclean
```
To clean everything:
```
make clean
```
