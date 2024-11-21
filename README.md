
# Calculation of cryptographic characteristics for a cipher based on a generalized Feistel network

## Cipher Specification

$F:Z_2^n \times Z_2^n\to Z_2^n$ - bijective in the second variable function. $\omega_i \in Z_2^n\ (Z_{2^n})$ - words.

Round transformition $R^F[l,s]:Z_2^{mn} \to Z_2^{mn} $:

$R^F [l,s] (\omega_1,...,\omega_m)=(\omega_1,...,\omega_{s-1},F(\omega_l,\omega_s),\omega_{s+1},...,\omega_m) $

<img src="img/round.png" alt="round" style="zoom:85%;" />

The composition $R^F[l_1,s_1]R^F[l_2,s_2]...R^F[l_h,s_h]$ implements substitution on the $nm$-bit block: $\Phi^F_N : Z_2^{nm}\to Z_2^{nm}$

Subtitution parameters: $n, m, h$, where $h$ - number of rounds (or *height*).
Network (sequence of pairs ($l$, $s$)) - also public parameter. The secret parameter is $F$ (tipical size $n$ - byte, so $n=8 $).

Example Network for 7 Rounds: $m=4,\ h=7$, and network $N=(1,2),(2,4),(4,3),(3,1),(1,2),(2,1),(1,4) $

<img src="img/example.png" alt="example" style="zoom:80%;" />

## Experiment

1. This work considers networks only $(s_0, s_1), (s_1, s_2),..., (s_{i\ mod(m)}, s_{i+1\ mod(m)}),... = (1,2),(2,3),(3,4),... $
2. An equally probable choice of $F$ with the return from the set of all matrices whose rows are permutations (the cardinality of such a set is $(2^{n}!)^{2^{n}} \sim 2^{n2^{2n}}$).
3. Calculate MDP, AI, NL.

## Build

```bash
cd ~
git clone https://github.com/jmpleo/netcip-crypt-char.git
cd ~/netcip-crypt-char
```

### Research Build

1. You need `cmake` to build this porject.

   ```bash
   cd ~/netcip-crypt-char/netcip-research
   ```

   and run

   ```bash
   ./build.sh <N> <M> <H>
   ```
   or
   ```powershell
   cmake . -D__N=<N> -D__M=<M> -D__H=<H>
   cmake --build build
   ```

2. Build range configuration

   Linux:
   ```bash
   ./brut-build.sh
   ```

3. Run Computing

   For example, NL-computing:

   ```bash
   cd ~/netcip-crypt-char/netcip-research/stat
   ../bin/netcip-nl-<N>-<M>-<H>
   # saving in ./netstat-nl-<N>-<M>-<H>.csv
   ```

### Application Build

`crypto++` required:

```bash
sudo apt install libcrypto++-dev
```

```bash
cd ~/netcip-crypt-char/netcip-application
cmake -B build
cd build
make
```

after this tests and speedtest binaries created - run it:

```bash
~/netcip-crypt-char/netcip-application/bin/netcip-test
~/netcip-crypt-char/netcip-application/bin/netcip-speedtest
```

#### Speedtest:

- `Linux debian 6.1.0-23-amd64 #1 SMP PREEMPT_DYNAMIC Debian 6.1.99-1 (2024-07-15) x86_64 GNU/Linux ` 
- `Intel(R) Core(TM) i5-10210U CPU @ 1.60GHz`
- `crypto++ 8`

```
8  bytes                       | Enc Blocks/min  | Dec Blocks/min  | Enc-Dec Blocks/min
--------------------------------------------------------------------------------
Blowfish                       | 818.841         | 825.038         | 416.373        
CAST-128                       | 741.3           | 745.784         | 362.473        
DES                            | 498.625         | 499.465         | 248.119        
DES-EDE3                       | 184.71          | 184.881         | 92.1633        
GOST                           | 438.543         | 446.962         | 219.253        
RC2                            | 358.133         | 735.364         | 243.359        
RC5                            | 1482.22         | 1794.94         | 856.433        
netcip1_8x8                    | 1495.05         | 1370.41         | 827.033        
netcip2_8x8                    | 1721.72         | 777.488         | 451.4          

16 bytes                       | Enc Blocks/min  | Dec Blocks/min  | Enc-Dec Blocks/min
--------------------------------------------------------------------------------
AES                            | 2554.44         | 2711.69         | 1268.38        
CAST-256                       | 337.406         | 337.879         | 169.483        
Camellia                       | 451.797         | 457.897         | 224.39         
MARS                           | 454.278         | 437.827         | 224.196        
RC6                            | 644.934         | 622.436         | 324.915        
Serpent                        | 267.742         | 293.042         | 138.751        
netcip1_8x16                   | 845.018         | 786.203         | 492.607        
netcip2_8x16                   | 937.803         | 403.071         | 231.096        

crypto++: 870
```



## Founded

> Cherednik, I. V. On the use of binary operations for the construction of a multiply transitive class of block transformations / I. V. Cherednik // Discrete Mathematics and Applications.  2021.  31: 2. P. 91–111.) (Scopus, WoS) // https://www.mathnet.ru/rus/dm1597

