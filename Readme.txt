Conway's Game of Life benchmark
-------------------------------

This project is meant to test a few implementations of Conway's Game of Life
in C, JavaScritp and ASM.js against each other.

The tests are unscientific and very likely incorrect in their implementation
but they serve the intention of experimenting with various approaches and
getting a rough performance estimation.


Implementations
---------------

conway1.c    A naive implementation that computes the number of neighbours for
             each cell in turn, wrapping around at the edges.

conway2.c    Avoids the use of the modulo operator (%) by adding a buffer
             border around the grid in this fashion:

                v       v
                9 7 8 9 7 <
                3 1 2 3 1
                6 4 5 6 4
                9 7 8 9 7
                3 1 2 3 1 <

             This way, no wrap around has to be calculated in index lookups,
             greatly reducing the number of operations in the inner loop. The
             borders are updated (by copying the values) after every cycle.

conway3.c    Instead of counting the neighbours per cell, here the number of
             neighbours is calculated in 8 separate loops. It can be thought
             of as a large matrix addition:

               [a b c 0 0]   [0 a b c 0]   [0 0 a b c]   [0 0 0 0 0]
               [d e f 0 0]   [0 d e f 0]   [0 0 b c d]   [a b c 0 0]
               [g h i 0 0] + [0 g h i 0] + [0 0 e f g] + [d e f 0 0] + ...
               [0 0 0 0 0]   [0 0 0 0 0]   [0 0 0 0 0]   [g h i 0 0]
               [0 0 0 0 0]   [0 0 0 0 0]   [0 0 0 0 0]   [0 0 0 0 0]

             This lends itself to vector instruction optimisation, which the
             compiler does take advantage of.

             Finally the counts are checked and replaced by the correct new
             values (1 or 0).

conway3.js   A straightforward port to JavaScript. From the benchmark it's
             clear that Node.js fails to apply useful optimisations here

conway3b.js  By using Uint8Array instead of a plain old JavaScript array,
             performance is significantly improved but still two orders of
             magnitude lower than the PC version.

conway3.c    Compiling the C code to ASM.js, a subset of JavaScript that
(emcc)       Node.js is optimised for, yields speeds that are much closer to
             the native version.


Benchmarks results
------------------

In seconds. Obtained by using  sleep <command> on a FreeBSD Linode instance as
well as a Skylake i5 machine running Windows 10 with the Windows Subsystem for
Linux.

                    FreeBSD / Linode              Windows (LXSS) 
                conway1  conway2  conway3   conway1  conway2  conway3
                -------------------------   -------------------------
GCC   -O3        17.11     2.01     1.18      SEGV     1.24     0.69
Clang -O3        17.56     9.91     1.01      SEGV     7.29     0.48     
Node.js                           532.69                      289.16
 ~ Uint8Array                     140.88                       87.32
Emcc -O0                                                       15.15
Emcc -O1                                                        7.83
Emcc -O2                                                        6.47


License
-------

I, the copyright holder of this work, hereby release it into the public
domain. This applies worldwide.

If this is not legally possible: I grant any entity the right to use this work
for any purpose, without any conditions, unless such conditions are required
by law.
