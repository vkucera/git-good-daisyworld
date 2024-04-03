# The Daisyworld simulation

**Daisyworld** <sup> [[1]](#bibliography)</sup> is a computer simulation of a
_hypothetical world_ orbiting around a star whose radiant energy slowly varies
with time.

Its original version was introduced by James Lovelock and Andrew Watson as a
_toy model_ to show how **living creatures** (_biotas_) **and the environment**
they populate **evolve as an interconnected system**, one affecting the other.

**The only living beings** populating Daisyworld are (indeed) **daises**, that
(in the simplest model) exist in two varieties: _white-_ and _black-_ petaled.
**White-daisies** mostly _reflect light_, while **black-daisies** mostly absorb
light.

The light absorbed or reflected (_albedo_) by daisies, contributes to the
variation of the temperature of a local patch of land, or to the overall
Daisyworld average temperature, respectively.

The simulation **tracks the two daisy populations** and the Daisyworld **average
temperature** as the **sun luminosity varies**.

Several variants of the _toy model_ were developed over the years (e.g.
deterministic, as the one described above, or stochastic - some examples can be
found in<sup> [[2]](#bibliography)</sup> and<sup> [[3]](#bibliography)</sup>).

## Design
In this simulation the world is represented by a matrix of cells that can either be barren or populated by one of two types of daisy (black or white).

The temperature of the patches of land are determined by the albedo of their surface, different for black and white daisy and barren land, and the solar luminosity.

The temperature of a patch of land influences the temperature of the neighbouring terrain.

The flowers age with the ticks of the simulation and die out when they reach a specific age, turning their patch of land barren.

The live flowers spread to the neighbouring land based on seeding probability dependent on their local temperature.

## Compile and run

The `CMakeLists.txt` file makes it easy to compile and run the code:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
build/daisyworld
```

Alternatively you can manually run the compilation with something like:

```bash
g++ main.cpp daisy.cpp world.cpp
```

## Output

The simulation will output a result similar to the one shown below:

```bash
💮💮🌸🌸🌸🌸🌸💮💮  
🌸💮💮🌸🌸🌸🌸🌸🌸🌸
🌸💮💮💮🌸🌸🌸🌸🌸🌸
💮🌸💮🌸🌸🌸🌸🌸🌸🌸
🌸💮🌸💮💮🌸🌸💮💮🌸
🌸🌸🌸💮💮🌸🌸🌸💮🌸
  🌸🌸💮💮🌸💮🌸💮💮
  🌸🌸🌸🌸🌸🌸💮💮🌸
    🌸🌸🌸🌸🌸🌸🌸🌸
            🌸🌸🌸🌸

Global temperature: 29.1791
```

## Bibliography

[[1]](https://onlinelibrary.wiley.com/doi/abs/10.1111/j.1600-0889.1983.tb00031.x)
Watson, A.J.; Lovelock, J.E (1983). "Biological homeostasis of the global
environment: the parable of Daisyworld". Tellus. 35B (4): 286–9.

[[2]](https://gingerbooth.com/html5/daisy/help/index.html) An Online Daisyworld
simulator with many options, which includes and document both deterministic
and stochastic evolution models.

[[3]](http://ccl.northwestern.edu/netlogo/models/Daisyworld) A NetLogo version
of a stochastic Daisyworld model.
