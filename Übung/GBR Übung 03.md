---
tags:
  - Übung
  - Hausaufgabe
  - WiSe_25-26
  - GBR
createdAt: 2025-11-26
---
[PDF](blatt03.pdf)

# 3

## 3.1 Echtzeit-Scheduling und Prioritäten

### a)
Nein, da die Summe aller Rechenzeiten größer ist als die größte Deadline.

### b)
Priorität nach Deadline-Monotonic Scheduling:

| Prozess | Deadline |
| ------- | -------- |
| P1      | 10       |
| P2      | 10       |
| P4      | 10       |
| P5      | 14       |
| P3      | 15       |


Sortieren nach $r_i$

| Prozess | r_i |
| ------- | --- |
| P1      | 0   |
| P2      | 1   |
| P4      | 8   |

$P1 < P2 < P4$

Daraus ergibt sich die Bedingung für die Prioritäten:

$$
P1 < P2 < P4 < P5 < P3
$$

## 3.2 Linux CFS-Scheduling
### a)

```tikz
\usetikzlibrary{arrows.meta, positioning}

\begin{document}

\begin{tikzpicture}[
    ->, >=Stealth, thick,
    level distance=1.5cm,
    level 1/.style={sibling distance=6cm},
    level 2/.style={sibling distance=3cm},
    level 3/.style={sibling distance=1.5cm},
    bnode/.style={circle, draw=black, fill=black, text=white, minimum size=1cm, font=\bfseries\sffamily},
    rnode/.style={circle, draw=red, fill=red, text=white, minimum size=1cm, font=\bfseries\sffamily},
    nilnode/.style={rectangle, draw=black, fill=black, text=white, minimum size=0.6cm, font=\sffamily\scriptsize}
]


\node [bnode] {Root}
    child { node [rnode] {tg1}
        child { node [bnode] {P2} 
	        child { node [nilnode] {NIL} } 
	        child { node [nilnode] {NIL} }
	    }
        child { node [bnode] {P3} 
	        child { node [nilnode] {NIL} }
	        child { node [nilnode] {NIL} }
		}
    }
    child { node [rnode] {P1} 
		child { node [nilnode] {NIL} }
		child { node [nilnode] {NIL} }
	};

\end{tikzpicture}

\end{document}
```

### b)
Sinnvolle Zeitpunkte können sein:
1. **Periodisch:** Durch System-Tick sicherstellen, dass lang laufende Prozesse ihre Zeit angerechnet bekommen und ggf. verdrängt werden können.
    
2. **Zustandswechseln:** Sobald ein Prozess die CPU freiwillig abgibt oder geweckt wird, damit seine Platzierung im Red-Black-Tree korrekt ist.
    

Der CFS aktualisiert die vruntime über den function call `update_curr()`, welcher an folgenden Stellen steht:

- `scheduler_tick()`: Periodisch bei jedem Timer-Tick (Interval Abhängig von der `HZ`-Konfiguration)
    
- `dequeue_entity()` / `enqueue_entity()`: Wenn ein Task schlafen geht oder aufwacht
    
- `put_prev_task()`: Wenn ein Task verdrängt wird oder `yield()` aufruft.

### c)
$$
\text{vruntime} = \text{delta\_exec} \times \frac{ \text{NICE\_0\_LOAD}}{\text{weight}}
$$

$NICE\_0\_LOAD=1024$
$P3\_NICE=NICE\_\text{-2}=1586$

$$
\displaylines{
vruntime_{P3} &=& 10ms \times \frac{1024}{1586} &\approx &6,46ms\\
vruntime_{tg1} &=& 10ms \times \frac{1024}{1024} &=& 10ms\\
}
$$

### d)

Time Slice basierend auf den Gewichten in der Hierarchie.

* Gesamtgewicht Root: $1024 (P1) + 1024 (tg1) = 2048$
* P1: $50\%$
* tg1: $50\%$

Zeit für P1: $1000ms \times 0,5 = 500ms$
Zeit für tg1: $1000ms \times 0,5 = 500ms$


die Zeit von `tg1` auf SubTask aufteilen.
* Gewicht P2 (Nice 0): **1024**
* Gewicht P3 (Nice -2): **1586**
* Gesamtgewicht in tg1: $1024 + 1586 = 2610$

Zeit für P2:
$$\text{Zeit}_{P2} = 500ms \times \frac{1024}{2610} \approx 500ms \times 0,3923 = 196,17ms$$

Zeit für P3:
$$\text{Zeit}_{P3} = 500ms \times \frac{1586}{2610} \approx 500ms \times 0,6077 = 303,83ms$$

| Prozess | CPU-Zeit  |
| :------ | :-------- |
| **P1**  | 500,00 ms |
| **P2**  | 196,17 ms |
| **P3**  | 303,83 ms |

$500 + 196,17 + 303,83 \approx 1000$
