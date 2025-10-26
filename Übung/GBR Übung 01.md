---
tags:
  - Übung
  - Hausaufgabe
  - WiSe_25-26
  - GBR
createdAt: 2025-10-25
---
[PDF](blatt1.pdf)

# 1

## 1.1 Sizeof und Arrays

### a)
Das Array wird mit vom Typ `int` Initializiert. Eine Variable vom Typ `int` benötigt $4\text{ Byte}$ Speicherplatz. Somit braucht das Array insgesamt $4\text{ Byte}\cdot 8=32\text{ Byte}$ Speicherplatz.

### b)

`sizeof(a)` gibt die Gesamtgröße des Arrays in Byte zurück. Siehe a) => es ergibt sich eine Gesamtgröße von $32$ Byte.
Um die Anzahl der Elemente im Array zu berechnen kann man die Gesamtgröße des Arrays durch die Größe eines einzelnen
Elements teilen: `sizeof(a) / sizeof(a[0])`. Dies ergibt $32 \text{ Byte} / 4 \text{ Byte} = 8$ Elemente.

```c
int a [8];
int i;

for (i = 0; i < sizeof(a) / sizeof(a[0]); i ++) {
    a[i] = 1;
}
```

### c)

Der das Ergebnis wird `8` sein, da die Operation die Speichergröße des Datebtyps des Pointers zurück gibt.

### d)

Ein möglichkeit wäre die Übergabe der Arraygröße als zusätzlichen Parameter an die Funktion, da in C "Array Decay" ein
Array in einen Pointer umwandelt, wenn es an eine Funktion übergeben wird.

## 1.2

### a)
![[Pasted image 20251026180819.png]]

## 1.3
### a)
| **Header**  | **Meaning**       | **Erklärung**                                                                                                    |
| ----------- | ----------------- | ---------------------------------------------------------------------------------------------------------------- |
| **USER**    | User              | Der Benutzername des Eigentümers des Prozesses                                                                   |
| **PID**     | Process ID        | Die eindeutige Identifikationsnummer des Prozesses                                                               |
| **PPID**    | Parent Process ID | Die Prozess-ID des übergeordneten Prozesses                                                                      |
| **%CPU**    | CPU usage         | Der prozentuale Anteil der CPU-Zeit, den der Prozess seit seinem Start verwendet hat                             |
| **%MEM**    | Memory usage      | Der prozentuale Anteil des gesamten physischen Arbeitsspeichers, den der Prozess nutzt                           |
| **TT**      | Terminal          | Das Terminal, mit dem der Prozess verknüpft ist                                                                  |
| **STAT**    | Process state     | Der aktuelle Zustand des Prozesses                                                                               |
| **STARTED** | Start time/date   | Wann der Prozess gestartet wurde                                                                                 |
| **TIME**    | CPU time          | Die gesamte CPU-Zeit, die der Prozess bisher verwendet hat                                                       |
| **CMD**     | Command           | Der Befehl (und seine Argumente), mit dem der Prozess gestartet wurde                                            |

### b)
Der Prozess `3787` hat den Statuscode `S+`, welcher sich wie folgt aufschlüsseln lässt:

S: `interruptible sleep (waiting for an event to complete)`
\+: `is in the foreground process group`

- Der Prozess schläft und wartet auf Ereignisse (evt. Benutzereingabe)
- Er ist interaktiv und gehört zur ordergrundgruppe des Terminals

### c)
```
-+- 0956  root     login -- mschroetter
 \-+- 1009  mschroe  -zsh
   \-+- 1929  mschroe  tmux new-session
     \-+- 3828  mschroe  -zsh
       \--- 3967  mschroe  ps -eo user,pid,ppid
```
