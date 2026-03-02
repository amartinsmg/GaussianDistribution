# GaussianDistribution

GaussianDistribution is an exploratory multi-language project created to experiment with:

- Different programming languages
- Different database engines
- Distinct database access strategies (serial vs block inserts)
- Runtime and driver behavior
- Development experience across ecosystems

This project **does not aim to provide a rigorous or production-grade benchmark**.  
Instead, it was built as a hands-on laboratory to better understand how different stacks behave under similar workloads.

---

## Project Overview

Each implementation:

1. Computes the Normal Cumulative Distribution Function (CDF) using a Taylor series approximation.
2. Generates values for `x` in the range `[-5.00, 5.00]`.
3. Inserts the results into a database table.
4. Measures total execution time.

The approximation used is:

$$
P(X \le x) = \frac{1}{2} + \frac{1}{\sqrt{2 \pi}} e^{\frac{1}{2}(\frac{x - \mu}{\sigma})^2} \cdot \sum_{n = 0}^{\infty}{\frac{1}{1 \cdot 3 \cdot 5 ... (2n + 1)}x^{2n+1}}
$$

Each language has implementations targeting multiple databases and using different write patterns.

---

## Languages Used

- [C](src/c/)
- [C#](src/cs/)
- [Java](src/java/)
- [JavaScript](src/js/)
- [PHP](src/php/)
- [Python](src/py/)

This project was also an exercise in learning and exploring languages beyond my primary stack, implementing equivalent logic across ecosystems and understanding their runtime characteristics.

---

## Databases Tested

- SQLite
- MySQL
- MariaDB
- PostgreSQL

Database environments, except SQLite, are containerized using Docker.

---

## Insert Strategies

Two main database access patterns were tested:

### Serial Insert

- One `INSERT` per loop iteration
- Multiple roundtrips to the database
- Higher driver and network overhead

### Block Insert

- Multiple `INSERT` statements concatenated and executed at once
- Single roundtrip
- Lower overhead
- Highlights the impact of driver and database parsing behavior

The goal was to observe the performance differences between these approaches across languages and database engines.

---

## Runtime Environment

| Language              | Compiler or RE                |
| --------------------- | ----------------------------- |
| [C](src/c/)           | GNU C Compiler (MinGW) 11.2.0 |
| [C#](src/cs/)         | .NET SDK 6.0.4                |
| [Java](src/java/)     | Java RE 18.0.2                |
| [JavaScript](src/js/) | Node 18.7.0                   |
| [PHP](src/php/)       | Zend Engine 4.1.9             |
| [Python](src/py)      | CPython 3.10.6                |

---

## Average Runtime

|                   | [C](src/c/) | [Python](src/py) | [PHP](src/php/) | [Java](src/java/) | [JavaScript](src/js/) | [C#](src/cs/) |
| ----------------- | ----------- | ---------------- | --------------- | ----------------- | --------------------- | ------------- |
| SQLite serial     | 19.110s     | 19.915s          | 19.316s         | 19.921s           | 19.715s               | 20.194s       |
| SQLite block      | 19.369s     | 19.435s          | 19.918s         | 20.259s           | 19.589s               | 19.949s       |
| MySQL serial      | 11.621s     | 11.841s          | 11.248s         | 12.593s           | 11.494s               | 12.220s       |
| MySQL block       | 0.419s      | 0.435s           | 0.345s          | 9.469s            | 9.651s                | 9.975s        |
| MariaDB serial    | 7.739s      | 7.076s           | 6.126s          | 6.044s            | 6.881s                | 6.419s        |
| MariaDB block     | 0.317s      | 0.355s           | 0.366s          | 4.383s            | 4.995s                | 5.248s        |
| PostgreSQL serial | 7.900s      | 8.175s           | 7.444s          | 7.583s            | 8.071s                | 8.603s        |
| PostgreSQL block  | 0.244s      | 0.651s           | 0.808s          | 0.973s            | 0.566s                | 1.081s        |

<sup>Measurements were taken using `time` command in a laptop with Windows 10 (10.0.22000) laptop with Intel Core i5-8250U and 8 GB of RAM using GNU bash.<sup>

## Environment & Automation

### Docker

Database instances are containerized using Docker and Docker Compose.

To create the database containers:

```bash
./create_db.sh
```

Make sure you have:

- Docker Engine
- Docker Compose
- SQLite3 installed

### Build Automation

All compilable source files can be compiled using:

```sh
make
```

To compile a specific language:

```sh
make c
make java
make cs
```

The build system uses custom automation scripts to:

- Compile each language in a standardized way
- Handle JDBC and database drivers when needed
- Generate executable JARs (Java)
- Publish self-contained binaries (.NET)
- Normalize output artifacts into the build/ directory

Before compiling, verify paths inside:

- `Makefile`
- `compile_java.sh`
- `compile_cs.sh`

and ensure all required compilers and runtimes are installed.

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
