---
tags:
  - Vorlesung
  - WiSe_25-26
  - GBR
createdAt: 2025-10-28
---
[[02-1-Prozessverwaltung.pdf#page=6|Begin]]

**PCB**: Process Controll Block

![[Drawing 2025-10-28 10.27.52.excalidraw]]


### Ablauf von fork()

1 Neuen Processblock
- Teil der Einträge werden neu gesetzt:
  PID, PPI, ...
- Teil der Einträge werden auf Null gesetzt:
  CPU-Verbrauch, Timer, ....
- Teil der Einträge werden vom Elternprocess kopiert:
  Zeiger auf offene Dateidesktiptoren, Prozessgruppe, Signalzustand, Nice-Wert,...
2

3

### Prozesskontrollblock
! Descriptor !

Copy on write

Bemerkung 1:
Seit 4.4 BSD effizientere implementierung von Schritt 2 im fork: Copy on Write

Die Seiten im virtuellen Adressraum als "copy on write" makiert, falls einer der beiden Prozesse eine Seite im Virtuellen Adressraum modifizieren will => Kopieren

$$
fork=
\begin{cases}
0 & \text{im Child}\\
\text{Child-PID}  & \text{im Parent}
\end{cases}
$$

