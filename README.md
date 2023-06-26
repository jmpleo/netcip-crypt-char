
# Computing cryptographic characteristics for generalized Feistel network -based cipher

1. Algebraic Immunity
2. Max Differential Probability

### Specification cipher

1 Round. Round function $F$ - bijective in the second variable,

$F:Z_2^n \times Z_2^n\to Z_2^n,\  \omega_i \in Z_2^n\ (or\ Z_{2^n})$


<img src="img/round.png" alt="round" style="zoom:85%;" />

Cipher parameters: $n, m, h$, where $h$ - number of rounds (or *height*). $F$ - secret key

Example Network for 7 Rounds: ($m=4,\ h=7$)

<img src="img/example.png" alt="example" style="zoom:80%;" />

### Build

1. You need `cmake` to build this porject.

   ```bash
   cmake -S . -B build
   ```

2. One-build configuration (to ./build)

   ```bash
   ./build.sh <N> <M> <H>
   ```

3. More configuration

   ```bash
   # change parameters range and run
   ./brut-build.sh
   ```

### Run Computing

```bash
cd build
./netcip-<N>-<M>-<H>
# saving in netstat-<N>-<M>-<H>.csv
```
