### Betriebssysteme
#### Einführung & Architektur
##### Betriebssystem:
- Software/Schnittstelle zwischen Hardware und Anwendungen

##### Betriebsarten und Modi:
- User-Mode (Benutzermodus):
	- Anwendungen laufen mit eingeschränkten Rechten
	- Kein direkter Zugriff auf kritische Hardware oder Speicherbereiche
- Kernel-Mode (Kernmodus):
	- Betriebssystem läuft mit vollen Rechten
	- Uneingeschränkter Zugriff auf Hardware und Systemressourcen


- Systemaufrufe (System Calls):
	- Schnittstelle zwischen Anwendungen und Betriebssystem

##### Verwaltungsbereiche des Betriebssystems
- Prozessverwaltung:
    - Verwaltung laufender Programme (Prozesse)
    - Erzeugen, Beenden, CPU-Zuteilung (Scheduling), Synchronisation
        
- Speicherverwaltung:
    - Zuteilung des Hauptspeichers
    - Nutzung virtueller Adressen
        
- Dateisystem:
    - Organisation von Daten als Dateien in hierarchischen Verzeichnissen
    - Abstraktion der physischen Speicherung
    - Zugriffsschutz durch Rechte (Read, Write, Execute)
        
- Geräteverwaltung:
    - Verwaltung und Ansteuerung von Ein-/Ausgabe-Geräten
    - Einheitliche Schnittstelle trotz unterschiedlicher Hardware
        
- Monitoring / Accounting:
    - Überwachung der Systemleistung und -auslastung
    - Protokollierung und statistische Erfassung der Nutzung


# ?
POSIX (-Threads)

Scheduling-Algorithmen verhungern?
- Round-Robin
- Statische Prioritäten
- Windows-Scheduler

Red-Black-Tree

Task-Gruppe
nice Werte


semaphore und Mutex, Monitor
RW Lock


routing
IP

Error Detection