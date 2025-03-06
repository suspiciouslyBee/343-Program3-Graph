This is a Graph class implemented for 343. It implements all public functions
required for program 3 without memory leaks and with clear understandable code.

Other notes of interest:
I figured out how to implement Dykstra's with recursion through a static hash
table. If the public function allowed, I would return this table directly
instead of writing to the global variable provided. The recursion allows me to
dynamically keep a note of which edge each node is checking.

I decided to make this use STL classes to get familiar with the suite and quirks
. As a side effect, I did not have to program around dynamic memory at the Graph
class level, nor any other classes. This made it easier to keep track of the
program flow and data within during design.

Compiling:
g++ -std=c++14 -g -Wall -Wextra *.cpp -o A3