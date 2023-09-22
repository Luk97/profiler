# profiler

This C profiler is used to messure time during runtime. A quick example is [here](##Example) provided

## Example

```html
#include "profiler.h"

#define PROFILER_CAPACITY 8

int main() {

    init_profilers(PROFILER_CAPACITY);

    begin_profiler("Adder Profiler");

    long result = 0;
    for (size_t i = 0; i < 1000*1000*1000; ++i) {
        result += i;
    }

    end_profiler();

    clear_profilers();

    return 0;
}
