*This project has been created as part of the 42 curriculum by admin.*

## Description

The classic dining-philosophers concurrency problem from the 42 curriculum.
Each philosopher is a `pthread`; each fork is a `pthread_mutex_t`. The program
simulates philosophers thinking, taking two forks, eating, and sleeping in a
circle around a table, with a watchdog thread that detects starvation and
reports the first death within 10 ms.

This repository contains the mandatory part (`philo/`). The optional bonus
(`philo_bonus/`) — philosophers as processes synchronized by a named
semaphore — has not been implemented yet.

## Instructions

Build from the `philo/` directory:

```sh
cd philo
make            # builds ./philo
make clean      # remove .o files
make fclean     # remove .o files and the binary
make re         # fclean + all
```

Run the simulation:

```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep \
        [number_of_times_each_philosopher_must_eat]
```

All time arguments are in milliseconds. With the optional 5th argument, the
simulation stops once every philosopher has eaten at least that many times;
without it, the simulation stops only when a philosopher dies.

Examples:

```sh
./philo 5 800 200 200          # five philosophers, classic survivable params
./philo 4 410 200 200          # tight timing — common death-detection test
./philo 1 800 200 200          # single philosopher must die (only one fork)
./philo 5 800 200 200 7        # stop after each philosopher has eaten 7 times
```

Log format (subject §V):

```
<timestamp_ms> <X> has taken a fork
<timestamp_ms> <X> is eating
<timestamp_ms> <X> is sleeping
<timestamp_ms> <X> is thinking
<timestamp_ms> <X> died
```

## Resources

- *Operating Systems: Three Easy Pieces* — chapters on concurrency, threads,
  locks, and condition variables.
- The POSIX threads man pages (`pthread_create`, `pthread_mutex_lock`,
  `pthread_join`, etc.).
- The classic Dijkstra paper introducing the dining-philosophers problem.

### AI usage

AI assistance was used to produce this README
