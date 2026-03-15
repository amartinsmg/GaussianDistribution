# HashInsertBenchmark

**Hash Insert Benchmark** is an exploratory multi-language project created to experiment with:

- Different programming languages
- Different database engines
- Distinct database write strategies (serial vs block inserts)
- Runtime and database driver behavior
- Development experience across ecosystems

This project **does not aim to provide a rigorous or production-grade benchmark**.  
Instead, it was built as a hands-on laboratory to explore how different language runtimes and database drivers behave under a simple and deterministic workload.

It is was also an exercise in learning and exploring languages beyond my primary stack, implementing equivalent logic across ecosystems and understanding their runtime characteristics.

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

### Languages Used

| Language                      | Compiler or Runtime Enviroment |
| ----------------------------- | ------------------------------ |
| [C](implementations/c/)       | GNU C Compiler 13.3.0          |
| [Java](implementations/java/) | OpenJDK 21.0.10                |
| [PHP](implementations/php/)   | Zend Engine v4.3.6             |
| [Python](implementations/py/) | CPython 3.14.3                 |

---

### Databases Tested

| Database        | Version |
| --------------- | ------- |
| SQLite          | 3.45.1  |
| SQLite (Java)   | 3.51.2  |
| SQLite (PHP)    | 3.45.1  |
| SQLite (Python) | 3.51.2  |
| MySQL           | 9.6.0   |
| MariaDB         | 12.2.2  |
| PostgreSQL      | 18.3    |

Database environments, except SQLite, are containerized using Docker to ensure reproducibility.

---

### Insert Strategies

Three database write patterns were tested to observe how different drivers, runtimes, and database engines behave under distinct insertion workloads.

Each test inserts **10,000 rows** into a table using different execution strategies.

#### Serial Insert

- One transaction per insert (autocommit enabled)
- 10,000 individual INSERT statements
- 10,000 database roundtrips
- Highest transaction and driver overhead

Example:

```sql
INSERT INTO table (hash) VALUES (...);
INSERT INTO table (hash) VALUES (...);
INSERT INTO table (hash) VALUES (...);
```

Each statement is executed individually.

---

#### Batch Insert

- A single execution containing multiple INSERT statements
- A single transaction (explicit BEGIN / COMMIT, depending on the interface)
- 10,000 individual INSERT statements executed together
- Single database roundtrip

Example:

```sql
BEGIN;

INSERT INTO table (hash) VALUES (...);
INSERT INTO table (hash) VALUES (...);
INSERT INTO table (hash) VALUES (...);

COMMIT;
```

All `INSERT` statements are concatenated and sent to the database **in a single execution block**.

---

#### Bulk Insert

- A single transaction
- One INSERT statement containing multiple values
- Single database roundtrip
- Lowest parsing and protocol overhead

Example:

```sql
INSERT INTO table (hash) VALUES
(...),
(...),
(...);
```

---

## Purpose

The main purpose of this repository is exploratory. It was created as a practical environment to experiment with multiple programming languages, database systems, and database access patterns under a similar workload.

The project aims to:

- Compare syntax, tooling, and developer experience across different languages
- Observe runtime and driver behavior when interacting with databases
- Evaluate how different insert strategies affect performance
- Explore build automation and containerized database environments

By comparing these strategies, the project also allows observation of how database engines such as MySQL, MariaDB, PostgreSQL, and SQLite handle different write patterns, particularly regarding:

- transaction management overhead
- SQL parsing cost
- database roundtrips
- driver execution behavior

This repository should be viewed as a personal multi-stack laboratory rather than a rigorous or production-grade performance benchmark.

---

## Test Environment

All experiments were executed under the following environment:

- **OS:** Ubuntu 24.04.3 LTS (WSL2)
- **Container runtime:** Docker 29.2.1
- **CPU:** Xeon E5-2640v3
- **Memory:** 16 GB RAM
- **Storage:** 500 GB NVMe SSD (PCIe 3.0)

---

## Average Runtime

|                   | C         | Java      | PHP       | Python    |
| ----------------- | --------- | --------- | --------- | --------- |
| SQLite serial     | 1m26.763s | 1m55.697s | 1m27.594s | 2m10.120s |
| SQLite batch      | 52ms      | 485ms     | 82ms      | 128ms     |
| SQLite bulk       | 39ms      | 542ms     | 63ms      | 98ms      |
| PostgreSQL serial | 22.686s   | 23.080s   | 30.182s   | 29.773s   |
| PostgreSQL batch  | 245ms     | 564ms     | 324ms     | 544ms     |
| PostgreSQL bulk   | 76ms      | 596ms     | 107ms     | 329ms     |
| MySQL serial      | 1m8.350s  | 1m6.481s  | 1m6.483s  | 1m8.387s  |
| MySQL batch       | 1.476s    | 1.075s    | 1.521s    | 223ms     |
| MySQL bulk        | 263ms     | 930ms     | 242ms     | 234ms     |
| MariaDB serial    | 27.003s   | 25.314s   | 23.886s   | 26.093s   |
| MariaDB batch     | 894ms     | 983ms     | 806ms     | 232ms     |
| MariaDB bulk      | 188ms     | 893ms     | 164ms     | 203ms     |

<sup>Measurements were taken using `time` command in GNU bash.<sup>

---

## Key Observations

- The insert strategy had a significantly larger impact on performance than the programming language used.
- Serial inserts were consistently orders of magnitude slower, mainly due to transaction overhead.
- Bulk inserts generally provided the best performance, minimizing parsing and roundtrip costs.
- Batch inserts reduced transaction overhead, but still required parsing multiple SQL statements.
- SQLite showed very strong performance in bulk workloads due to its embedded architecture.
- Differences between programming languages were noticeable but much smaller than the impact of transaction strategy.

---

## Limitations

This project is intentionally simplified and does not simulate real-world production conditions. It does not include:

- Concurrent clients
- Index tuning
- Network latency simulation
- Production-grade durability configurations

The results reflect controlled local execution under simplified conditions.

---

## Security Note

Some implementations in this repository generate SQL statements dynamically using string formatting.

For example, the Python implementations use **f-strings** to construct bulk and batch `INSERT` statements, while other languages such as C, PHP, and Java use formatted strings with `%d`.

This approach is used intentionally to keep the benchmark simple and to minimize driver-side overhead when generating large multi-row `INSERT` statements.

In this project, the values inserted into the database are internally generated integers, which eliminates the risk of SQL injection.

However, in real-world applications it is recommended to use **parameterized queries or prepared statements**, especially when handling user-provided data.

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

PHP and Python implementations can be executed directly using their respective runtimes.

Before building, ensure that the required compilers and runtimes are installed and verify any paths defined inside the corresponding Makefile or helper scripts.
