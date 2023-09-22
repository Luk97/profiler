# profiler

This C profiler is used to messure time during runtime. A quick example is provided [here](## Example).  
This profilers mesuares nanoseconds accurate. Internally the profiler is stackbased so that no comparision have to be made to determine the end of one profiler.

## Todo

- Comment the code
- Add dynamic capacity
- Add file as output
- Add threshold to create time warnings

## Example

```c
// Define PROFILER_IMPLEMENTATION if it is not defined anywhere else in your project.
// Omit it in cases, where the implemation is already defined in the project to avoid linking errors.
#define PROFILER_IMPLEMENTATION
// Include the library.
#include "profiler.h"

int main() {

    // This is the amount of profilers that can run at the same time.
    int profiler_capacity = 8;

    // Init the internal Profiler structure. Malloc() gets called, so you need to call clear_profilers() to avoid memory leakage.
    init_profilers(profiler_capacity);

    // Start the clock of a profiler. The internal structure is stackbased, so that the last created profiler will finish first.
    begin_profiler("Adder");

    // Sample code, that is getting measured.
    long result = 0;
    for (size_t i = 0; i < 1000*1000*1000; ++i) {
        result += i;
    }

    // End the last created profiler. The internal structure is stackbased, so that no comparisons have to be made for more optimal performance.
    end_profiler();

    // Call this function if all the profiling is finished to free the memory allocated by init_profilers().
    clear_profilers();

    return 0;
}

Console output:
```
[PROFILER INFO] Adder took: 2s 127ms 52ns

