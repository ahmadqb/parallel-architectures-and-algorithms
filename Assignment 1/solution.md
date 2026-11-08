# Assignment 1 – Solution

**Course:** Parallel Architectures and Parallel Algorithms

---

## Question 1: Floating-Point Addition and Pipelining

| # | Question | Answer |
|---|----------|--------|
| 1.1 | Time for one floating-point addition | **9 ns** |
| 1.2 | Unpipelined addition of 1000 pairs of floats | **9 000 ns** |
| 1.3 | Pipelined addition of 1000 pairs of floats | **2 012 ns** |
| 1.4 | Pipelined addition of 1000 pairs, where the first 250 are in L1 cache, the next 250 in L2 cache and the remaining 500 in main memory | **53 014 ns** |

**1.4 breakdown:**

```
14 + 2 000 + 2 000 + 49 000 = 53 014 ns
```

---

## Question 2: Cache Hit/Miss Sequences

Legend: **H** = hit, **M** = miss

**2.1**

```
M, H, M, H, M, M, H, M, M, M, M, M, M
```

**2.2**

```
M, H, M, H, M, M, M, M, M, M, M, M, M
```

---

## Question 3: Parallel Performance Measurements

All times are in seconds, and `p` is the number of processes/threads.

### Table 1

Average parallel time, T<sub>parallel</sub>:

| p | T<sub>parallel</sub> (avg) |
|:-:|---------------------------:|
| 2 | 0.155561 |
| 3 | 0.0883615 |
| 4 | 0.07296 |
| 5 | 0.128447 |
| 6 | 0.0838825 |

> **Note:** Not enough cores were available.

### Table 2

Average parallel and serial times:

| p | T<sub>parallel</sub> (avg) | T<sub>serial</sub> (avg) |
|:-:|---------------------------:|-------------------------:|
| 2 | 0.0782263 | 0.095424 |
| 3 | 0.0685653 | 0.1405212 |
| 4 | 0.07296 | 0.1856954 |
| 5 | 0.0897121 | 0.2331848 |
| 6 | n/a | 0.2819734 |

> **Note:** Memory ran out for p = 6.

### Speedup and Efficiency

Speedup is S = T<sub>serial</sub> / T<sub>parallel</sub>, and efficiency is E = S / p.

| p | Speedup | Efficiency |
|:-:|--------:|-----------:|
| 2 | 1.2198 | 0.6099 |
| 3 | 2.0494 | 0.6831 |
| 4 | 2.5451 | 0.6363 |
| 5 | 2.5992 | 0.5198 |
