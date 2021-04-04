## Implementation of Kernighan-Lin Algorithm (C++)

This code is the implementation of Kernighan-Lin algorithm with C++, which addresses two-way mini-cut partition problem.
* [An efficient heuristic procedure for partitioning graphs
](https://ieeexplore.ieee.org/document/6771089)

The pseudocode of KL algorithm from [Wiki](https://en.wikipedia.org/wiki/Kernighan%E2%80%93Lin_algorithm):

```
function Kernighan-Lin(G(V, E)) is
    determine a balanced initial partition of the nodes into sets A and B
    
    do
        compute D values for all a in A and b in B
        let gv, av, and bv be empty lists
        for n := 1 to |V| / 2 do
            find a from A and b from B, such that g = D[a] + D[b] − 2×c(a, b) is maximal
            remove a and b from further consideration in this pass
            add g to gv, a to av, and b to bv
            update D values for the elements of A = A \ a and B = B \ b
        end for
        find k which maximizes g_max, the sum of gv[1], ..., gv[k]
        if g_max > 0 then
            Exchange av[1], av[2], ..., av[k] with bv[1], bv[2], ..., bv[k]
    until (g_max ≤ 0)

    return G(V, E)
```

This project is inspired by [li3939108](https://github.com/li3939108/KL-Partitioning).

## Installation

1. Install [CMake](https://cmake.org/) and compile

```shell
git clone https://github.com/neo85824/kernighan-lin-algorithm-implementation.git
cd kernighan-lin-algorithm-implementation
mkdir build
cd build
cmake ..
cmake --build .
```

## Input Format
The first line consists of **V** and **E**, which stands for the number of vertices and edges. 

The following **E** lines represent the connection of edges. Note that the number of vertex starts from 1.

```shell
10 15
1 2
1 4
2 5
...
```


## Usage 

The execution file is in `src` of the built folder (e.g. `build/src`).

1. Execute and type the input by yourself
```
./kl_main
```
2. Execute with specific input file
```
./kl_main < ../../input/input_1000_1500.txt
```
3. Execute with specific input file and output the result vertex of set in specific output file

```
./kl_main < ../../input/input_1000_1500.txt
```
