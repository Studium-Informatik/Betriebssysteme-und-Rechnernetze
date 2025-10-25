---
tags:
  - Vorlesung
  - WiSe_25-26
  - GBR
createdAt: 2025-10-21
---
[PDF](02-1-Prozessverwaltung.pdf)

[[02-1-Prozessverwaltung.pdf#page=6|Definition 11]]:
![[Notes-Prozesszyklus.excalidraw]]


### Abnormales Prozessverhalten
[[02-1-Prozessverwaltung.pdf#page=7|Abnormales Prozessverhalten]]

- **Deadlock:** Der Prozess ist blockiert und es erfolgt kein Zustandswechsel mehr.  
- **Livelock:** Der Prozess wechselt ständig zwischen Zuständen, ohne in seiner Programmausführung voranzukommen.  
- **Starvation:** Der Prozess bleibt rechenbereit, erhält aber keine Rechenzeit und kann daher nicht fortfahren


### Ablauf Koordination
Ein BS hat eine Vielzahl von nebenläufigen Aktivitäten zu kontrollieren

1. Polling := Aktiv reihum sich um die verschiedenen Aktivitäten kümmern (NIC, Benutzerprozesse, Plattencontroller, ...)
   Vorteil: Fair
   Nachteil: CUP-Zeit verschwendung wenn keine Aktivität vom BS erforderlich ist => Overhead
2. Unterbrechung


### Abreitsweise der CPU
![[Notes-CPU_Arbeitsweise.excalidraw]]

| Prozess | Zustand initial | 1          | 2         | 3            | 4            |
| ------- | --------------- | ---------- | --------- | ------------ | ------------ |
| A       | rechnend        | rechnend   | rechnend  | rechenbereit | rechenbereit |
| B       | blockiert       | blockiert  | blockiert | blockiert    | rechenbereit |
