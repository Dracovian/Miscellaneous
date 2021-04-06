# Bignum PCG

##

**Requirements:**

* libgmp *(for bignum/arbitrary precision support)*

* A C++20 compatible compiler *(almost all modern C++ compilers will support this)*

##

**How is this anything like PCG:**

I will admit that my minified variants of Professor O'Neill's PCG code are not faithful in any sense to the original concepts behind PCG.

For instance this variant is missing the following:

* Thread-safe operation *(no spinlocks or mutexes to be seen in this code)*

* Fixed-precision integer values for the RNG state and increment

* Fixed constant multipliers

* XSH-RR

* XSH-RS

* RXS-M-XS

* XSL-RR-RR

* DXS-M

##

**Translation for those variants above:**

**RR** = Random-Rotation

**RS** = Random-Shift

**XSH** = XORShift `x ^= x >> constant value`

**XSL** = XORShift high half into the low `lo_x ^= hi_x >> constant value`

**RXS** = Random XORShift `x ^= x >> random value`

**DXS** = Double XORShift `x ^= (x ^= x >> constant value) >> constant value`

**XS** = an alias for XSH

**M** = Multiply by fixed constant *(the multiplier in this sense)*

##

**The following are non-official variants that might be tested:**

**QXS** = Quad XORShift *(XORShift four times for diminishing returns on security in respect to runtime performance)*

**OXS** = Octa XORShift *(XORShift eight times for even more diminishing returns than QXS)*

**RM** = Multiply by a random value *(a randomized multiplier might cause issues)*

##

**Which variant of PCG is this built with:**

XSL-RR

But this is not true XSL-RR since we're not adhering to a 128-bit state or a 64-bit output. We're also not using the same 128-bit multiplier that Professor O'Neill uses for XSL-RR in the [PCG-C code](https://github.com/imneme/pcg-c).

I'm experimenting with PCG to see if I can still have a better PRNG than Mersenne Twister while maintaining the following benefits:

* Low-memory footprint

* Low-CPU requirement

Some say that rolling your own RNG is similar to rolling your own crypto *(in that you don't do either for the sake of security)*

But I prefer to take risks if it means I learn something from them. This is me taking a risk since the code in this repository might very well find its way into future projects.

Of course I'll have to make a ton of improvements to this code before I bother making use of it again, but this is just the beginning for me.

##

# Credits

The [Free Software Foundation](https://fsf.org) and the authors of the [GNU MP Library](https://gmplib.org/).

You know I have to give credit to [Professor Melissa O'Neill](https://www.cs.hmc.edu/~oneill/index.html) for making the PCG line of random number generators based on LCG random number generators. I probably would not have even considered looking into a better RNG method if it weren't for PCG.

You can find out more about PCG at [the offical PCG website](https://www.pcg-random.org/).

##

# License

This work is based on PCG which is licensed under Apache 2.0 and GNU MP which is licensed under LGPL 3.0 and GPL 2.0.

`SPDX-License-Identifier: Apache-2.0 AND LGPL-3.0 AND GPL-2.0`