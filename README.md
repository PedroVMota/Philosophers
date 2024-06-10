# Philosophers 42 Project Documentation

## Table of Contents
- [Introduction](#introduction)
- [Overview](#overview)
- [Usage](#usage)
- [Implementation](#implementation)
  - [Threads](#threads)
  - [Mutexes](#mutexes)
  - [Philosopher Simulation](#philosopher-simulation)
- [Building and Running](#building-and-running)
- [Testing](#testing)
- [Conclusion](#conclusion)
- [Acknowledgments](#acknowledgments)

## Introduction

The Philosophers project is part of the 42 curriculum, designed to introduce the basics of threading and process synchronization. Inspired by the classic dining philosophers problem, this project simulates philosophers sitting around a table, eating, thinking, and sleeping, with the challenge of managing resource access using threads and mutexes.

## Overview

In the Philosophers project:
- **Multiple philosophers** sit at a round table.
- There is a **large bowl of spaghetti** in the middle of the table.
- Philosophers **alternately eat, think, or sleep**.
- Each philosopher needs **two forks** to eat.
- Philosophers must avoid **starving** by managing shared forks with proper synchronization.

The main objective is to prevent race conditions and ensure that no philosopher starves by implementing proper use of threads and mutexes.

## Usage

### Arguments

The program takes the following command-line arguments:
1. `number_of_philosophers`: The number of philosophers and forks.
2. `time_to_die`: Time in milliseconds a philosopher can go without eating before dying.
3. `time_to_eat`: Time in milliseconds it takes for a philosopher to eat.
4. `time_to_sleep`: Time in milliseconds a philosopher spends sleeping.
5. `number_of_times_each_philosopher_must_eat` (optional): If specified, the simulation ends when each philosopher has eaten at least this many times.

Example usage:
```sh
./philo 5 800 200 200
./philo 5 800 200 200 7
```

## Implementation

### Threads

A **thread** is a single sequence stream within a process. Threads are used for small tasks. They share the same memory space, making them faster and more efficient than processes, which do not share memory space.

### Mutexes

A **mutex** (mutual exclusion) is a synchronization primitive used to prevent race conditions when multiple threads attempt to access a shared resource concurrently. Mutexes ensure that only one thread can access the resource at a time.

### Philosopher Simulation

1. **Initialization**: Create philosopher threads and mutexes for each fork.
2. **Philosopher Life Cycle**:
   - **Thinking**: The philosopher is contemplating and not interacting with the forks.
   - **Eating**: The philosopher picks up two forks (left and right), eats, and then puts down the forks.
   - **Sleeping**: After eating, the philosopher sleeps before starting to think again.

Each state change is logged with a timestamp and philosopher identifier.

## Building and Running

### Requirements

- The project must be written in C.
- A `Makefile` must be provided to compile the project with the following rules: `all`, `clean`, `fclean`, and `re`.
- Compilation flags: `-Wall -Wextra -Werror`.

### Compilation

To compile the project, run:
```sh
make
```

### Running

After compilation, run the program with the required arguments:
```sh
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

## Testing

To test the project, create various scenarios with different numbers of philosophers and times. Ensure that no philosopher starves and the program handles synchronization properly. Test cases might include:
- Minimal configuration: `./philo 1 800 200 200`
- Typical configuration: `./philo 5 800 200 200`
- Configuration with eating limits: `./philo 5 800 200 200 7`

## Conclusion

The Philosophers project provides a practical introduction to threading and synchronization in C. By simulating a classic synchronization problem, it teaches important concepts of concurrent programming, resource management, and process synchronization.

## Acknowledgments

This project is part of the 42 school curriculum, inspired by Edsger Dijkstra's classic dining philosophers problem. Special thanks to the 42 community for their support and resources.
