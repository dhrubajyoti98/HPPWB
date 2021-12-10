# HPPWB - High Performance Physics Workstation Benchmark

HPPWB (High Performance Physics Workstation Benchmark) is an alternative suite for benchmarking workstations with specifically shared-memory architectures (for now).

## But Why and How?

While industry standard benchmarks like HPLinpack exist, which is used for making the TOP500 list, and is widely used across domains, such benchmarks use a fixed workload like solving a dense set of linear equations to measure the performance of a system. While that provides a nice standard, it is generally not reflective of real-life performance in variety of workloads.

In specific simulations and workloads which are characterisitic to physics research, not only we need to solve linear equations systems (which can be parallelized easily), but other not-so-parallelizable things like solving ODEs, PDEs and so on. We aim to tackle that problem with this suite - not only we use solving linear equations as a tool but also things like performing integrals, doing Monte-Carlo integrals and solving ODEs. We aim to add more features and tests in the future along with acclerators and distributed-memory architecture support.

## Compiling and Running

- Install OpenMP, GNU Scientific Library and git, if not already installed.
  
&rarr; For Ubuntu and it's derivatives

```console
sudo apt install libomp-dev
sudo apt install libgsl-dev
sudo apt install git
```

- Clone the repository into a folder.
  
```console
git clone git@github.com:dhrubajyoti98/HPPWB.git
```

- Change into the folder HPPWB and run "make" which should generate an executable "main_driver.run"
  
```console
cd HPPWB
make
```
&rarr; The compiler optimizations being passed to g++ are "-Ofast" and "-march=native".

- Run the benchmark using "./main_driver.run N" where N is an integer denoting the number of run-passes.
  
```console
./main_driver <number of run-passes>
```

## Next Features

1. Adding support for using config files to change the benchmark parameters rather than re-compiling the source.
2. Add GPU Compute Support.

## Author and Contact

Dhrubajyoti Biswas, dhrubajyoti98@gmail.com
