#ifndef PROFILER_H_
#define PROFILER_H_

typedef enum {
    PROFILER_LOG_EVERYTHING        = 0,
    PROFILER_LOG_INFO              = 1,
    PROFILER_LOG_ALERT             = 2,
    PROFILER_LOG_ERROR             = 3,
    PROFILER_LOG_NOTHING           = 4,
} ProfilerLogLevel;

#define PROFILER_NO_THRESHOLD 0
#define PROFILER_NS           1
#define PROFILER_MS           1000
#define PROFILER_SEC          1000000

void profiler_init(ProfilerLogLevel log_level);
void profiler_begin(const char *name, long threshold_ns);
void profiler_end();
void profiler_clear();

#endif // PROFILER_H_


#ifdef PROFILER_IMPLEMENTATION

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct {
    const char *name;
    clock_t start;
    long threshhold;
} Profiler;

typedef struct {
    Profiler *profilers;
    int count;
    int capacity;
    ProfilerLogLevel log_level;
} ProfilerStack;

static ProfilerStack *stack;                        

void profiler_init(ProfilerLogLevel log_level) {

    stack = malloc(sizeof(ProfilerStack));
    if (!stack) {
        if (log_level <= PROFILER_LOG_ERROR)
            fprintf(stderr, "[PROFILER ERROR] malloc failed.\n");
        return;
    }

    

    stack->count = 0;
    stack->capacity = 8; // Default capacity
    stack->log_level = log_level > PROFILER_LOG_NOTHING ? PROFILER_LOG_EVERYTHING : log_level;
    stack->profilers = malloc(sizeof(Profiler) * stack->capacity);
    if (!stack->profilers) {
        if (stack->log_level <= PROFILER_LOG_ERROR) {
            fprintf(stderr, "[PROFILER ERROR] malloc failed.\n");
        }
        return;
    }
}

void profiler_begin(const char *name, long threshold_ns) {

    if (stack->count >= stack->capacity) {
        // double the capacity 
        stack->capacity *= 2;
        stack->profilers = realloc(stack->profilers, sizeof(Profiler) * stack->capacity);
        if (!stack->profilers) {
            if (stack->log_level <= PROFILER_LOG_ERROR) {
                fprintf(stderr, "[PROFILER ERROR] malloc failed.\n");
            }
            return;
        }
    }

    stack->count += 1;
    stack->profilers[stack->count].threshhold = threshold_ns;
    stack->profilers[stack->count].name = name ? name : "profiler";
    stack->profilers[stack->count].start = clock();
}

void profiler_end() {
    if (stack->count <= 0) {
        if (stack->log_level <= PROFILER_LOG_ERROR) {
            fprintf(stderr, "[PROFILER ERROR] no profilers are currently running.\n");
        }
        return;
    }

    clock_t duration = clock() - stack->profilers[stack->count].start;

    if (stack->profilers[stack->count].threshhold == 0 || duration < stack->profilers[stack->count].threshhold) {
        if (stack->log_level <= PROFILER_LOG_INFO) {
            printf(
                "[PROFILER INFO] %s took: %lds %ldms %ldns\n",
                stack->profilers[stack->count].name,
                duration / CLOCKS_PER_SEC,              // seconds
                duration % CLOCKS_PER_SEC / 1000,       // milliseconds
                duration % 1000                         // nanoseconds
            );
        }
    } else {
        if (stack->log_level <= PROFILER_LOG_ALERT) {
            printf(
                "[PROFILER ALERT] %s took: %lds %ldms %ldns\n",
                stack->profilers[stack->count].name,
                duration / CLOCKS_PER_SEC,              // seconds
                duration % CLOCKS_PER_SEC / 1000,       // milliseconds
                duration % 1000                         // nanoseconds
            );
        } 
    }
    
    stack->count -= 1;
}

void profiler_clear() {
    free(stack->profilers);
    free(stack);
}

#endif // PROFILER_IMPLEMENTATION
