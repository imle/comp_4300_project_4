## Compilation

In the root directory, run:

`$ make`

## Running

To run the Scoreboard Simulator:

`$ ./scoSim ./lab4c.s`

To run the Scoreboard Simulator in debug mode:

`$ ./scoSim -d ./lab4c.s`

## Debug Mode

Allows you to view the memory before and after run.

## Info

Steven Imle
ski0005

John Desverreaux
jnd0011

## Implementation Issues

* The projects preceding this one became too complicated to implement
this portion directly in the source of the others, therefore we
decided to start a separate project for it.

* Only this full-reservation version of the scoSim was implemented
since it was deemed to difficult and time consuming to implement the
pipelined version.

## Cycle Data and NOP Counting

Due to the changes made to the parsing of `*.s` files, the exact
counts of this data may be unattainable. This stems from the fact that
we implemented all of the MIPS pseudo-instructions to parse into their
legitimate counterparts.

Since this data is necessary for us to pass however, here are our
program's close approximations:

### Full-Reservation Simulator

|                     | C       |
|---------------------|---------|
| Total Instructions  | 4123    |
| Total Cycles        | 4123    |
| NOP Count           | 2991    |
