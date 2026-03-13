# HashWorkloadDBTest

HashWorkloadDBTest is an exploratory multi-language project created to experiment with:

- Different programming languages
- Different database engines
- Distinct database write strategies (serial vs block inserts)
- Runtime and database driver behavior
- Development experience across ecosystems

This project **does not aim to provide a rigorous or production-grade benchmark**.  
Instead, it was built as a hands-on laboratory to explore how different language runtimes and database drivers behave under a simple and deterministic workload.

---

## Project Overview

Each implementation:

1. Generates a sequence of integer values.
2. Computes a deterministic **32-bit hash** for each value.
3. Inserts the results into a database table.
4. Measures the total execution time.

The hash function used is a lightweight integer mixing function designed to produce well-distributed 32-bit values with minimal computational overhead.

Example implementation:

```c
int32_t hash32(int32_t x) {
  x ^= x >> 16;
  x *= 0x7feb352d;
  x ^= x >> 15;
  x *= 0x846ca68d;
  x ^= x >> 16;
  return x;
}
```

---

## Languages Used

- [C](implementations/c/)
- [Java](implementations/java/)
- [PHP](implementations/php/)
- [Python](implementations/py/)

This project was also an exercise in learning and exploring languages beyond my primary stack, implementing equivalent logic across ecosystems and understanding their runtime characteristics.

---

## Databases Tested

- SQLite
- MySQL
- MariaDB
- PostgreSQL

Database environments, except SQLite, are containerized using Docker to ensure reproducibility.

---

## Insert Strategies

Two main database access patterns were tested:

### Serial Insert

- One transaction per insert
- 1001 individual `INSERT` statements
- Multiple roundtrips to the database
- Higher transaction and driver overhead

### Block Insert

- A single transaction
- One INSERT statement containing 1001 values
- Single database roundtrip
- Lower overhead and improved throughput

The purpose of comparing these approaches is to observe how database engines, drivers, and language runtimes handle different write patterns.

---

## Runtime Environment

| Language | Compiler or RE |
| -------- | -------------- |
| C        | GNU C Compiler |
| Java     | Java RE        |
| PHP      | Zend Engine    |
| Python   | CPython        |

---

## Average Runtime

|                   | C   | Python | PHP | Java |
| ----------------- | --- | ------ | --- | ---- |
| SQLite serial     | s   | s      | s   | s    |
| SQLite block      | s   | s      | s   | s    |
| MySQL serial      | s   | s      | s   | s    |
| MySQL block       | s   | s      | s   | s    |
| MariaDB serial    | s   | s      | s   | s    |
| MariaDB block     | s   | s      | s   | s    |
| PostgreSQL serial | s   | s      | s   | s    |
| PostgreSQL block  | s   | s      | s   | s    |

<sup>Measurements were taken using `time` command in a laptop with Windows 10 (10.0.22000) laptop with Intel Core i5-8250U and 8 GB of RAM using GNU bash.<sup>

---

## Environment & Automation

### Docker

Database instances are containerized using Docker and Docker Compose.

To create the database containers:

```bash
./create_containers.sh
```

Make sure you have:

- Docker Engine
- Docker Compose

### Build

Each language implementation is organized in its own directory inside `implementations/`.

Some languages provide their own build automation through a local `Makefile`.  
For example:

```sh
cd implementations/c
make
```

```sh
cd implementations/java
make
```

The Java implementation also uses a helper scripts to manage JDBC dependencies and generate executable `.jar` files.

Other implementations (JavaScript, PHP, Python) can be executed directly using their respective runtimes.

Before building, ensure that the required compilers and runtimes are installed and verify any paths defined inside the corresponding Makefile or helper scripts.

---

## Limitations

This project is intentionally simplified and does not simulate real-world production conditions. It does not include:

- Concurrent clients
- Index tuning
- Network latency simulation
- Transaction benchmarking
- Prepared statement reuse comparisons
- Production-grade durability configurations

The results reflect controlled local execution under simplified conditions.

---

## Purpose

The main purpose of this repository is exploratory:

- Compare syntax and developer experience across languages
- Observe runtime differences
- Compare database driver behavior
- Understand the impact of serial vs block inserts
- Explore build systems and containerized environments

It serves as a personal multi-stack laboratory rather than a definitive performance benchmark.
