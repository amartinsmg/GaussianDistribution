# GaussianDistribution

It's a personal project for a distribution calculator program. It was made in different languages and using distinct databases. Each language has a program for each database. Each of them uses a function that calculates the approximation of the normal cumulative distribution function (CDF) using this Taylor series approximation:

$$
P(X \le x) = \frac{1}{2} + \frac{1}{\sqrt{2 \pi}} e^{\frac{1}{2}(\frac{x - \mu}{\sigma})^2} \cdot \sum_{n = 0}^{\infty}{\frac{1}{1 \cdot 3 \cdot 5 ... (2n + 1)}x^{2n+1}}
$$

The main objective of this project is to observe the difference in syntax and runtime of each programming language and the difference in runtime for each database connection.

### Compilers and Runtime Environment

| Language              | Compiler or RE                |
| --------------------- | ----------------------------- |
| [C](src/c/)           | GNU C Compiler (MinGW) 11.2.0 |
| [C#](src/cs/)         | .NET SDK 6.0.4                |
| [Java](src/java/)     | Java RE 18.0.2                |
| [JavaScript](src/js/) | Node 18.7.0                   |
| [PHP](src/php/)       | Zend Engine 4.1.9             |
| [Python](src/py)      | CPython 3.10.6                |

### Average Runtime

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

<sup>**Note:** The measurements in this table were performed using the `time` command in a laptop with Windows 10.0.22000, Intel Core i5-8250U and 8 GB of RAM in GNU bash.<sup>

All compilable source files can be compiled using this command:

```sh
make
```

<sup>**Note**: before compiling, open the [Makefile](./Makefile) and [compile_java.sh](./compile_java.sh) and verify if the variables store, respectively, the actual location of the necessary files, as well as make sure you have [GNU Make](https://www.gnu.org/software/make/) and all compilers installed.</sub>

If you want to compile single languages, you can add the file extension after the `make` command, e.g., to compile just the programs written in C, use this command:

```sh
make c
```

To create a container for each database, run the command below:

```sh
./create_db.sh
```

<sub>**Note**: before run this command, make sure you have installed the [Docker engine](https://docs.docker.com/engine/install/), the [Docker Compose](https://docs.docker.com/compose/install/) and [SQLite3](https://www.sqlite.org/index.html).</sub>
