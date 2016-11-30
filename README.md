## Compilation

In the root directory, run:

`$ make`

## Running

To run the Scoreboard Simulator:

`$ ./scoSim ./lab3a.s`

To run the Scoreboard Simulator in debug mode:

`$ ./scoSim -d ./lab3a.s`

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

## Cycle Data and NOP Counting

Due to the changes made to the parsing of `*.s` files, the exact
counts of this data may be unattainable. This stems from the fact that
we implemented all of the MIPS pseudo-instructions to parse into their
legitimate counterparts.

Since this data is necessary for us to pass however, here are our
program's close approximations:


|                     | A       | B       | C       |
|---------------------|---------|---------|---------|
| Total Instructions  | 338     | 94      | 82      |
| Total Cycles        | 198     | 162     | 48      |
| Single Cycle "Time" | 2704    | 752     | 656     |
| Multi Cycle "Time"  | 198     | 162     | 48      |
| Calculated Speedup  | 13.6566 | 4.64198 | 13.6667 |
| NOP Count           | 198     | 21      | 8       |