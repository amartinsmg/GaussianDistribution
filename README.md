# GaussianDistribution

### Average Runtime

|                   | [C](src/c/) | [Python](src/py) | [PHP](src/php/) | [Java](src/java/) | [JavaScript](src/js/) | [C#](src/cs/) |
| ----------------- | ----------- | ---------------- | --------------- | ----------------- | --------------------- | ------------- |
| SQLite serial     | 19.110s     | 19.915s           | 19.316s         | 19.921s           | 19.715s               | 20.194s       |
| SQLite block      | 19.369s     | 19.435s          | 19.918s         | 20.259s           | 19.589s               | 19.949s       |
| MySQL serial      | 11.621s     | 11.841s          | 11.248s         | 12.593s           | 11.494s               | 12.220s       |
| MySQL block       | 0.419s      | 0.435s           | 0.345s          | 9.469s            | 9.651s                | 9.975s        |
| MariaDB serial    | 7.739s      | 7.076s           | 6.126s          | 6.044s            | 6.881s                | 6.419s        |
| MariaDB block     | 0.317s      | 0.355s           | 0.366s          | 4.383s            | 4.995s                | 5.248s        |
| PostgreSQL serial | 7.900s      | 1.168s           | 7.444s          | 7.583s            | 8.071s                | 8.603s        |
| PostgreSQL block  | 0.244s      | 0.374s           | 0.808s          | 0.973s            | 0.566s                | 1.081s        |
