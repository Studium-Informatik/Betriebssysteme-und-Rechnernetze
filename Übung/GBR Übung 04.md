---
tags:
  - Übung
  - Hausaufgabe
  - WiSe_25-26
  - GBR
createdAt: 2025-12-13
---
[PDF](blatt04.pdf)

### 4.1: Syscall
#### a)
C-Bibliothek:
```c
#include <sys/time.h>

int main() {
	struct timeval tv;
	for(int i=0; i<10000000; i++) {
		gettimeofday(&tv, NULL);
	}
	return 0;
}
```

Syscall:
```c
#include <sys/syscall.h>
#include <unistd.h>
#include <sys/time.h>

int main() {
	struct timeval tv;
	for(int i=0; i<10000000; i++) {
		syscall(SYS_gettimeofday, &tv, NULL);
	}
	return 0;
}
```


#### b)
![[Pasted image 20251213170314.png]]

- Das lib-Programm ist deutlich schneller als die direkte syscall-Variante
- Bei lib fällt keine Systemzeit an
- Beim direkten syscall dominiert die Systemzeit.

-> gettimeofday führt keinen System Aufruf aus

#### c)
lib
![[Pasted image 20251213172028.png]]

syscall
![[Pasted image 20251213172209.png]]


Der Unterschied wird sichtbar bei libc +53 und syscall +60.

### 4.2: 
#### a)
-  Ausgabe 15:
      * `t1_main` ruft `t1_f1` auf. `x=3` wird auf den Stack gelegt (Offset `-0x4(%rbp)`). `p` wird auf die Adresse von `x` gesetzt. `t1_f1` kehrt zurück.
      * `t1_main` ruft `t1_f2` auf. Der Stack-Frame wird an derselben Stelle wie für `f1` erstellt. `y=5` wird an dieselbe relative Adresse gelegt (`-0x4(%rbp)`).
      * Gleichzeitig läuft `t2_main`. sleep(1), was T1 Zeit gibt, `p` zu setzen und `k` zu erhöhen (`k` wird 3).
      * T2 dereferenziert `*p`. Da `p` auf die Adresse `-0x4(%rbp)` zeigt (wo früher `x` war und jetzt `y` ist), liest es den Wert 5.
      * $k = k * (*p) \rightarrow 3 * 5 = 15$.

-  0, Zufallswerte oder Segfault:
      * Wenn T2 liest, nachdem `t1_f2` bereits zurückgekehrt ist, zeigt `p` in einen "ungültigen" Stackbereich unterhalb des aktuellen Stackpointers (oder in den Frame von `t1_main`). Der Wert ist dann Garbage.
      * Wenn T2 extrem schnell wäre (vor T1s `p=&x`), wäre `p` nicht initialisiert (Global `int* p` ist im BSS 0-initialisiert). Dereferenzierung von `NULL` führt zum Absturz (Segmentation Fault).

#### b)
Das Verhalten ist undefiniert, da ein "Dangling Pointer" entsteht, weil die globale Variable `p` mit der Adresse der lokalen Variable `x` belegt wird.
  * Sobald `t1_f1` endet (return), wird der Speicherbereich von `x` auf dem Stack freigegeben.
  * Der Zugriff auf diesen Speicherbereich durch einen anderen Thread (`t2_main`) ist ein klassischer "Use-after-free"-Fehler bzw. Zugriff auf verwaisten Speicher.
  

### 4.3
#### a)

| Zeit | Prozess | Aktion / Codezeile | Var-Änderung | Status |
| :--- | :--- | :--- | :--- | :--- |
| ZS 1 | R1 | 1. `DOWN(mutex_str)` | `mutex_str`=0 | OK |
| | | 2. `DOWN(sem_r)` | `sem_r`=0 | OK |
| | | 3. `DOWN(mutex_rc)` | `mutex_rc`=0 | OK |
| ZS 2** | R1 | 4. `readcount++` | `readcount`=1 | |
| | | 5. `if (readcount == 1)` -\> `DOWN(sem_w)` | `sem_w`=0 | Writer blockiert |
| | | 6. `UP(mutex_rc)` | `mutex_rc`=1 | |
| *Interrupt* | | *annkunft R2 und W1* | | |
| ZS 3 | R2 | 1. `DOWN(mutex_str)` | | Blockiert |
| ZS 4 | W1 | 1. `DOWN(mutex_wc)` | `mutex_wc`=0 | OK |
| | | 2. `writecount++` | `writecount`=1 | |
| | | 3. `if (writecount == 1)` -\> `DOWN(sem_r)` | | Blockiert |

=> R1 hält `mutex_str` und `sem_r`. R2 wartet auf `mutex_str`. W1 wartet auf `sem_r`.

#### b)

| Zeit | Prozess | Aktion / Codezeile | Var-Änderung | Status |
| :--- | :--- | :--- | :--- | :--- |
| ZS 1 | W1 | 1. `DOWN(mutex_wc)` | `mutex_wc`=0 | OK |
| | | 2. `writecount++` | `writecount`=1 | |
| | | 3. `if (writecount == 1)` -\> `DOWN(sem_r)` | `sem_r`=0 | Lesen gesperrt |
| *Interrupt* | | *annkunft R1* | | |
| ZS 2 | R1 | 1. `DOWN(mutex_str)` | `mutex_str`=0 | OK |
| | | 2. `DOWN(sem_r)` | | Blockiert |
| *Interrupt* | | *annkunft W2* | | |
| ZS 3 | W2 | 1. `DOWN(mutex_wc)` | | Blockiert |

### 4.5
#### a)
![[Pasted image 20251213175613.png]]
Unter `/proc/PID/fd/` befindet:
  * 0: Verweist auf `/dev/null` – Standard Input.
  * 1: Verweist auf Terminal (`/dev/pts/X`) – Standard Output.
  * 2: Verweist auf `/tmp/err_uid` – Standard Error.
  * 3: Verweist auf die temp Datei `/tmp/tempfileXXXXXX`.
      * `mkstemp(str3)` erstellt einen Dateideskriptor. Da 0, 1 und 2 belegt sind, ist 3 der nächste freie.

#### b)
![[Pasted image 20251213180559.png]]
  * Unterscheiden sich diese während der Ausführung des Programms?
      * Nein. Threads, die mit `pthread_create` erstellt werden, teilen sich (via `CLONE_FILES` Flag beim `clone`-Syscall) dieselbe Dateideskriptortabelle.
      * Wenn man `/proc/PID/task/TID/fd` für den Hauptthread und den Worker-Thread ansieht, sind die Einträge identisch.

  * Fork statt Thread:
      * Wenn statt `pthread_create` ein `fork()` verwendet wird, würde der Kindprozess eine Kopie der Dateideskriptortabelle erhalten.
      * Wenn der Elternprozess dann `close(fptr)` aufruft, wird nur sein Eintrag entfernt.
      * Der Kindprozess hätte den Dateideskriptor weiterhin offen und könnte erfolgreich schreiben.
      * => Prozesse haben getrennte Adressräume und Ressourcentabellen (Copy-on-Write bzw. Duplizierung beim Start), Threads teilen sich diese Ressourcen.