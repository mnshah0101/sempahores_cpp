# Semaphores in C++

This repository contains implementations of various synchronization primitives and concurrency patterns using semaphores in C++. The project demonstrates practical examples of common synchronization problems and their solutions.

## Components

The project includes several implementations:

1. **Reader-Writer Lock** (`read_wrtier.cpp`)
   - Implements a reader-writer lock using semaphores
   - Allows multiple readers or a single writer at a time
   - Demonstrates concurrent read access with exclusive write access

2. **Barrier Synchronization** (`barrier_sync.cpp`)
   - Implements a barrier synchronization mechanism
   - Ensures all threads reach a certain point before proceeding

3. **Fork-Join Pattern** (`fork-join.cpp`)
   - Demonstrates the fork-join parallel programming pattern
   - Shows how to create and synchronize multiple threads

4. **Rendezvous Pattern** (`rendevous.cpp`)
   - Implements the rendezvous synchronization pattern
   - Ensures two threads meet at a specific point before proceeding

5. **No-Starve Mutex** (`no_starve_mutex.cpp`)
   - Implements a mutex that prevents thread starvation
   - Ensures fair access to shared resources

## Requirements

- C++11 or later
- POSIX-compliant operating system (for semaphore support)
- CMake (for building)

## Building and Running

To build the project:

```bash
mkdir build
cd build
cmake ..
make
```

To run a specific example (e.g., reader-writer):

```bash
./read_wrtier <num_readers> <num_writers> <loops>
```

## Usage Examples

### Reader-Writer Lock
```bash
./read_wrtier 3 2 5  # 3 readers, 2 writers, 5 loops each
```

### Barrier Synchronization
```bash
./barrier_sync <num_threads>
```

## Implementation Details

Each implementation uses POSIX semaphores (`sem_t`) for synchronization. The code demonstrates:
- Proper semaphore initialization and cleanup
- Thread-safe operations
- Common concurrency patterns
- Error handling and resource management

