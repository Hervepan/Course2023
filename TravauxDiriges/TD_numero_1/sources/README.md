
# TD1

`pandoc -s --toc README.md --css=./github-pandoc.css -o README.html`


## lscpu
```
Architecture :                          x86_64
Mode(s) opératoire(s) des processeurs : 32-bit, 64-bit
Address sizes:                          48 bits physical, 48 bits virtual
Boutisme :                              Little Endian
Processeur(s) :                         16
Liste de processeur(s) en ligne :       0-15
Identifiant constructeur :              AuthenticAMD
Nom de modèle :                         AMD Ryzen 7 4800H with Radeon Graphics
Famille de processeur :                 23
Modèle :                                96
Thread(s) par cœur :                    2
Cœur(s) par socket :                    8
Socket(s) :                             1
Révision :                              1
Frequency boost:                        enabled
Vitesse maximale du processeur en MHz : 2900,0000
Vitesse minimale du processeur en MHz : 1400,0000
BogoMIPS :                              5789.57
Drapaux :                               fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush mmx fxsr sse sse2 ht syscall nx mmxext fxsr_opt pdpe1gb rdtscp lm constant_tsc rep_good nopl nonstop_tsc cpuid extd_apicid aperfmperf rapl pni pclmulqdq monitor ssse3 fma cx16 sse4_1 sse4_2 movbe popcnt aes xsave avx f16c rdrand lahf_lm cmp_legacy svm extapic cr8_legacy abm sse4a misalignsse 3dnowprefetch osvw ibs skinit wdt tce topoext perfctr_core perfctr_nb bpext perfctr_llc mwaitx cpb cat_l3 cdp_l3 hw_pstate ssbd mba ibrs ibpb stibp vmmcall fsgsbase bmi1 avx2 smep bmi2 cqm rdt_a rdseed adx smap clflushopt clwb sha_ni xsaveopt xsavec xgetbv1 xsaves cqm_llc cqm_occup_llc cqm_mbm_total cqm_mbm_local clzero irperf xsaveerptr rdpru wbnoinvd cppc arat npt lbrv svm_lock nrip_save tsc_scale vmcb_clean flushbyasid decodeassists pausefilter pfthreshold avic v_vmsave_vmload vgif v_spec_ctrl umip rdpid overflow_recov succor smca
Virtualisation :                        AMD-V
Cache L1d :                             256 KiB (8 instances)
Cache L1i :                             256 KiB (8 instances)
Cache L2 :                              4 MiB (8 instances)
Cache L3 :                              8 MiB (2 instances)
Nœud(s) NUMA :                          1
Nœud NUMA 0 de processeur(s) :          0-15
Vulnerability Itlb multihit:            Not affected
Vulnerability L1tf:                     Not affected
Vulnerability Mds:                      Not affected
Vulnerability Meltdown:                 Not affected
Vulnerability Mmio stale data:          Not affected
Vulnerability Retbleed:                 Mitigation; untrained return thunk; SMT enabled with STIBP protection
Vulnerability Spec store bypass:        Mitigation; Speculative Store Bypass disabled via prctl and seccomp
Vulnerability Spectre v1:               Mitigation; usercopy/swapgs barriers and __user pointer sanitization
Vulnerability Spectre v2:               Mitigation; Retpolines, IBPB conditional, STIBP always-on, RSB filling, PBRSB-eIBRS Not affected
Vulnerability Srbds:                    Not affected
Vulnerability Tsx async abort:          Not affected

```
## Produit matrice-matrice



### Permutation des boucles

*Expliquer comment est compilé le code (ligne de make ou de gcc) : on aura besoin de savoir l'optim, les paramètres, etc. Par exemple :*

`make all && ./TestProduct.exe 1024`


  ordre           | time    | MFlops  | MFlops(n=2048) 
------------------|---------|---------|----------------
i,j,k (origine)   | 8.4325  | 254.585 |   262.424              
j,i,k             | 8.37455 | 256.43  |   265.112 
i,k,j             | 33.4779 | 64.1462 |   99.0055  
k,i,j             | 34.5388 | 62.1761 |   100.097
j,k,i             | 0.51521 | 4168.16 |   4124.92   
k,j,i             | 0.89188 | 2407.79 |   2365.47


Dans le cas où la boucle i est en dernière, on va pouvoir charger en cache plusieurs case de la matrice et ces cases pourront être utilisées dans la suite de la boucle. Si ce n'est pas le cas, on va devoir recharger le cache plus de fois depuis la ram, ce qui va ralentir le temps d'execution.


### OMP sur la meilleur boucle 

On rajoute la ligne #pragma omp parallel for avant la boucle pour avoir le parallelisme

`make TestProductMatrix.exe && OMP_NUM_THREADS=8 ./TestProductMatr.exe 1024`

  OMP_NUM         | MFlops(1024)  | MFlops(n=2048) | MFlops(n=512)  | MFlops(n=4096)
------------------|---------------|----------------|----------------|---------------
1                 |    4176.03    |    3949.90     |     4111.41    |     2512.53     
2                 |    3888.67    |    3916.92     |     3977.05    |     3279.72     
3                 |    3659.18    |    3942.16     |     4136.15    |     3270.93     
4                 |    3705.01    |    3906.86     |     3662.20    |     3589.37     
5                 |    3728.30    |    3183.32     |     3572.56    |     3982.88     
6                 |    3660.07    |    3405.14     |     3722.74    |     3443.42     
7                 |    3786.54    |    3985.71     |     4035.13    |     4637.36     
8                 |    3894.19    |    4112.97     |     4017.34    |     4407.27    
No OMP            |    4071.18    |    4030.87     |     4043.33    |     4042.5


  OMP_NUM         | SpeedUp(1024) | SpeedUp(n=2048) | SpeedUp(n=512)  | SpeedUp(n=4096)
------------------|---------------|-----------------|-----------------|-----------------
1                 |      1.02     |      0.97       |      1.01       |      0.65
2                 |      0.95     |      0.97       |      0.98       |      0.85
3                 |      0.89     |      0.97       |      1.02       |      0.84
4                 |      0.91     |      0.96       |      0.90       |      0.93
5                 |      0.91     |      0.78       |      0.88       |      1.03
6                 |      0.89     |      0.84       |      0.92       |      0.89
7                 |      0.93     |      0.98       |      0.99       |      1.20
8                 |      0.95     |      1.02       |      0.99       |      1.14  



### OMP sur la pire boucle

  OMP_NUM         | MFlops(1024)  | MFlops(n=2048) | MFlops(n=512)  | MFlops(n=4096)
------------------|---------------|----------------|----------------|---------------
1                 |    2314.92    |    2379.79     |    3670.07     |     2440.86
2                 |    2356.75    |    2371.71     |    2929.11     |     2456.25
3                 |    2357.22    |    2367.26     |    3632.03     |     2477.29
4                 |    2380.65    |    2392.67     |    4263.4      |     2475.93
5                 |    2333.87    |    2372.91     |    3810.18     |     2477.45
6                 |    2384.93    |    2392.77     |    2822.12     |     2445.15
7                 |    2341.55    |    2373.52     |    3850.94     |     2448.79
8                 |    2393.16    |    2361.01     |    3636.02     |     2480.03 
No OMP            |    193.733    |    236.347     |    266.094     |     236.094


  OMP_NUM         | SpeedUp(1024) | SpeedUp(n=2048) | SpeedUp(n=512)  | SpeedUp(n=4096)
------------------|---------------|-----------------|-----------------|-----------------
1                 |     11.94     |     10.06       |     13.79       |     10.33    
2                 |     12.16     |     10.03       |     11.00       |     10.40    
3                 |     12.16     |     10.01       |     13.64       |     10.49    
4                 |     12.28     |     10.12       |     16.02       |     10.48    
5                 |     12.04     |     10.03       |     14.31       |     10.49    
6                 |     12.31     |     10.12       |     10.60       |     10.35    
7                 |     12.08     |     10.04       |     14.47       |     10.37    
8                 |     12.35     |     9.98        |     13.66       |     10.50    

On voit qu'avec le bon agencement des boucles pour utiliser au mieux le cache, le speedup n'est pas très visible.
Cependant avec le pire agencement de boucle, on obtient des speed up de l'ordre du *10 qui est très impressionant.

### Produit par blocs

`make TestProduct.exe && ./TestProduct.exe 1024`

szBlock        |   	MFlops	     |   MFlops(n=2048)	|   MFlops(n=512)	 |   MFlops(n=4096)
---------------|-----------------|-----------------|-----------------|------------------
origine(=max)  |     3776.64     |     4118.08     |     5314.82     |     3999.71     
32             |     3920.33     |     4042.86     |     3732.59     |     4021.61     
64             |     3968.08     |     4060.71     |     3682.79     |     3866.59     
128            |     3703.80     |     3743.56     |     3645.21     |     3859.44     
256            |     4125.55     |     3975.58     |     5047.70     |     3966.98     
512            |     4048.57     |     3883.20     |     4822.36     |     3866.94     
1024           |     3861.62     |     3708.67     |     3467.63     |     3573.40   




### Bloc + OMP

  szBlock      | OMP_NUM | MFlops  | MFlops(n=2048) | MFlops(n=512)  | MFlops(n=4096)
---------------|---------|---------|----------------|----------------|-----------------
A.nbCols       |  1      |  4056   |    3956        |     2856       |   4023         
512            |  8      | 6177.288|    12861.74    |    3587.136    |   13588.69     
---------------|---------|---------|----------------|----------------|----------------
Speed-up       |         |  1.523  |     3.251      |    1.2565      |   3.46875      
---------------|---------|---------|----------------|-----------------|----------------



### Comparaison with BLAS

   BLAS        |    	MFlops	   |  MFlops(n=2048) |   MFlops(n=512) |  MFlops(n=4096) 
---------------|-----------------|-----------------|-----------------|------------------
    blas       |     20156       |      23256      |      15032      |     19982     


# Tips 

```
	env 
	OMP_NUM_THREADS=4 ./produitMatriceMatrice.exe
```

```
    $ for i in $(seq 1 4); do elap=$(OMP_NUM_THREADS=$i ./TestProductOmp.exe|grep "Temps CPU"|cut -d " " -f 7); echo -e "$i\t$elap"; done > timers.out
```
