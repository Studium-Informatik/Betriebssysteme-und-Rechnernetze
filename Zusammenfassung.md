# Prozessor
[[GBR VL 03]]
https://man7.org/linux/man-pages/man1/ps.1.html


```bash
PROCESS STATE CODES
    D    uninterruptible sleep (usually I/O)
    R    running or runnable (on run queue)
    S    interruptible sleep (waiting for an event to complete)
    T    stopped by job control signal
    t    stopped by debugger during trace
    Z    defunct ("zombie") process, terminated but not reaped by its parent
    X    dead (should never be seen)
```

|**Symbol**|**Bedeutung**|
|---|---|
|`<`|Prozess mit hoher Priorität|
|`N`|Prozess mit niedriger Priorität|
|`L`|Seiten im Speicher gesperrt|
|`s`|Sitzungsleiter (Session Leader)|
|`l`|Mehrthread-Prozess (multi-threaded)|
|`+`|Prozess läuft im Vordergrund|
Beispiel: `Ss+` = schlafender Sitzungsleiter im Vordergrund.