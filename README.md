# C N-Body Simulation

Simple n-body simulation written entirely in C. Uses periodic boundary conditions and a tempered version of Newton's law of gravity to limit extra close encounters. Python 3.6+ required to plot properly.

To build library:
```
make
```

To build simulation executable:
```
cd sims
make
```

To run the example simulation:
```
./sims/sim.exe sim.config
```
The ```sim.config``` parameters are:
```
fn -> filename
n_thread -> number of threads for parallelization
niter -> number of iterations
nb -> number of bodies
td -> timestep in sec
mass_low -> lower bound on masses of bodies
mass_up -> upper bound on masses of bodies
vel_low -> lower bound on each component of velocity
vel_up -> upper bound on each component of velocity
cubelen -> simulation cube size in AU
```
The default config parameters should produce a nice animation.

The masses and velocities are distributed in a uniform distribution between the upper and lower bounds.

To plot an animation:
```
./scripts/plot.py ./sims/out.txt
```
