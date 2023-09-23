# profiler

This C profiler is used to messure time during runtime. A quick example is provided [here](#quick-example).  
This profilers mesuares nanoseconds accurate. Internally the profiler is stackbased so that no comparision have to be made to determine the end of one profiler.

## Features

- Nanosecond accurate measuring
- Optional thresholds for each profiler
- Filterable levels of outputs (errors, alerts and infos)

## Todos

- File as output instead of console
- C++ compatible
- Windows compatible

## Dependencies

None.

## Quick example

### C file

```c
// Define PROFILER_IMPLEMENTATION if it is not defined anywhere else in your project.
#define PROFILER_IMPLEMENTATION
// Include the library.
#include "profiler.h"

int main() {

    // Init the internal Profiler structure. Malloc() gets called, so you need to call clear_profilers() to avoid memory leakage.
    // The log_level filters the log messages that get printed to the console.
    profiler_init(PROFILER_LOG_EVERYTHING);

    // Start the clock of a profiler. The first arguments is used to reference this profiler.
    // The second one is an optional threshold. If the timer exceeds the threshold, the log_level is of type PROFILER_LOG_ALERT instead of PROFILER_LOG_INFO.
    // If the threshold is 0, it gets ignored.
    profiler_begin("Adder", 0);

    // Sample code, that is getting measured.
    long result = 0;
    for (size_t i = 0; i < 1000*1000*1000; ++i) {
        result += i;
    }

    // End the last created profiler. The internal structure is stackbased, so that no comparisons have to be made for more optimal performance.
    profiler_end();

    // Call this function if all the profiling is finished to free the memory allocated by init_profilers().
    profiler_clear();

    return 0;
}
```

### Console output

```
[PROFILER INFO] Adder took: 2s 127ms 52ns
```