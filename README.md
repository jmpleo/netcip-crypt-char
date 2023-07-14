
# Calculation of cryptographic characteristics for a cipher based on a generalized Feistel network

### Cipher Specification

$F:Z_2^n \times Z_2^n\to Z_2^n$ - bijective in the second variable function. $\omega_i \in Z_2^n\ (Z_{2^n})$ - words.

Round transformition $R^F[l,s]:Z_2^{mn} \to Z_2^{mn} $:

$R^F [l,s] (\omega_1,...,\omega_m)=(\omega_1,...,\omega_{s-1},F(\omega_l,\omega_s),\omega_{s+1},...,\omega_m) $

<img src="img/round.png" alt="round" style="zoom:85%;" />

The composition $R^F[l_1,s_1]R^F[l_2,s_2]...R^F[l_h,s_h]$ implements substitution on the $nm$-bit block: $\Phi^F_N : Z_2^{nm}\to Z_2^{nm}$

Subtitution parameters: $n, m, h$, where $h$ - number of rounds (or *height*).
Network (sequence of pairs ($l$, $s$)) - also public parameter. The secret parameter is $F$ (tipical size $n$ - byte, so $n=8 $).

Example Network for 7 Rounds: $m=4,\ h=7$, and network $N=(1,2),(2,4),(4,3),(3,1),(1,2),(2,1),(1,4) $

<img src="img/example.png" alt="example" style="zoom:80%;" />

### Experiment

1. This work considers networks only $(s_0, s_1), (s_1, s_2),..., (s_{i\ mod(m)}, s_{i+1\ mod(m)}),... = (1,2),(2,3),(3,4),... $
2. An equally probable choice of $F$ with the return from the set of all matrices whose rows are permutations (the cardinality of such a set is $(2^{n}!)^{2^{n}} \sim 2^{n2^{2n}}$).
3. Calculate MDP, AI, NL.

### Build

1. You need `cmake` to build this porject.

   ```bash
   cd netcip-crypt-char
   cmake -S . -B build
   ```

2. One-build configuration (to ./build)

   Linux:
   ```bash
   ./build.sh <N> <M> <H>
   ```
   Windows:
   ```powershell
   cmake . -D__N=<N> -D__M=<M> -D__H=<H>
   cmake --build build
   ```

4. More configuration

   Linux:
   ```bash
   # change parameters range and run
   ./brut-build.sh
   ```

### Run Computing

For example, NL-computing:
```bash
cd stat
../bin/netcip-nl-<N>-<M>-<H>
# saving in ./netstat-nl-<N>-<M>-<H>.csv
```
