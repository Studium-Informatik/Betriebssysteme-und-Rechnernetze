### Teil I: Grundlagen Betriebssysteme

# 1.  Einführung
## 1.1. Definition eines Betriebssystems
### 1.1.1. Als Basis der Betriebsarten (DIN 44300)
### 1.1.2. Als virtuelle Maschine
### 1.1.3. Als Ressourcenverwalter
### 1.1.4. Schichtenmodell eines Rechensystems
### 1.1.5. Instruction Set Architecture (ISA)
## 1.2. Aufgaben eines Betriebssystems
### 1.2.1. Prozessverwaltung
#### 1.2.1.1. Definition Prozess (process, task)
#### 1.2.1.2. Prozesskontext (Programmcode, Stack, Datensegment, Verwaltungsinformationen)
#### 1.2.1.3. Laufzeit und Relationen (sequentielle, nebenläufige, parallele Prozesse)
#### 1.2.1.4. Systemaufrufe (System Calls)
### 1.2.2. Speicherverwaltung
#### 1.2.2.1. Virtuelle Adressierung
#### 1.2.2.2. Swapping
#### 1.2.2.3. Demand Paging
### 1.2.3. Verwaltung des Dateisystems
#### 1.2.3.1. Logische Sicht (Dateien, Verzeichnisse)
#### 1.2.3.2. Hierarchische Struktur (Beispiel UNIX)
#### 1.2.3.3. Schutz und Zugriffsrechte (rwx, Owner, Group, Others)
### 1.2.4. Geräteverwaltung
### 1.2.5. Monitoring, Accounting, Auditing
## 1.3. Betriebsarten und Modi
### 1.3.1. Einprogramm-/Mehrprogrammbetrieb
### 1.3.2. Stapelbetrieb/Dialogbetrieb
### 1.3.3. User-Mode vs. Kernel-Mode
### 1.3.4. Hardwareunterstützung (Program Status Word)
## 1.4. Geschichte der Betriebssysteme
### 1.4.1. 1. Generation (Röhren, keine BS)
### 1.4.2. 2. Generation (Transistoren, Stapelverarbeitung)
### 1.4.3. 3. Generation (ICs, Multiprogramming, Time-Sharing, UNIX)
### 1.4.4. 4. Generation (LSI/VLSI, PC, POSIX, Linux)
## 1.5. Architektur von Betriebssystemen
### 1.5.1. Monolithische Systeme (Beispiel Linux)
### 1.5.2. Microkernel-Architektur (Vorteile/Nachteile)
### 1.5.3. Architekturbeispiel Windows NT (Kernel, Manager, HAL)

# 2.  Prozessverwaltung
## 2.1. Prozesserzeugung und -verwaltung
### 2.1.1. Prozessbestandteile (Text, Stack, Data, Kontext)
### 2.1.2. Prozesskontrollblock (PCB) / Prozessleitblock
### 2.1.3. Hardwarekontext vs. Softwarekontext
### 2.1.4. Prozesszustände (rechnend, rechenbereit, blockiert)
### 2.1.5. Zustandsübergänge (Admit, Dispatch, Timeout, Event Wait/Occurs, Release)
### 2.1.6. Abnormales Prozessverhalten (Deadlock, Livelock, Starvation)
### 2.1.7. Unterbrechungen (Interrupts)
#### 2.1.7.1. Asynchrone Unterbrechungen (Hardware Interrupts)
#### 2.1.7.2. Synchrone Unterbrechungen (Traps, System Calls, Exceptions)
#### 2.1.7.3. Unterbrechungsvektor und Behandlungsroutinen
### 2.1.8. UNIX-Prozesserzeugung
#### 2.1.8.1. `fork()` (Eltern- und Kindprozess, Copy-on-Write)
#### 2.1.8.2. `execve()`
#### 2.1.8.3. `exit()`
#### 2.1.8.4. `wait()`
#### 2.1.8.5. Zombie-Prozesse
## 2.2. Scheduling
### 2.2.1. Klassen von Schedulingverfahren
#### 2.2.1.1. Deterministisch vs. Nicht-deterministisch (Offline vs. Online)
#### 2.2.1.2. Verdrängend (preemptive) vs. nicht verdrängend (non-preemptive)
### 2.2.2. Metriken und Kriterien
#### 2.2.2.1. Wartezeit, Bedienzeit, Verweilzeit
#### 2.2.2.2. Durchsatz
#### 2.2.2.3. Fairness
#### 2.2.2.4. Echtzeitbedingungen (Ready time, Deadline)
### 2.2.3. Strategien
#### 2.2.3.1. FIFO (First In First Out) / FCFS
#### 2.2.3.2. SJF (Shortest Job First) / Shortest Next CPU Burst
#### 2.2.3.3. Approximation der CPU-Burst-Länge (Exponentielle Glättung)
#### 2.2.3.4. Round Robin (Zeitscheibenverfahren)
#### 2.2.3.5. Prioritäten-basiertes Scheduling (Statisch, Dynamisch)
#### 2.2.3.6. Priority Boosting
#### 2.2.3.7. Priority Inversion
### 2.2.4. Beispiel: BSD Scheduling (Multilevel Feedback Queue, Load Average)
### 2.2.5. Beispiel: Windows Scheduling
#### 2.2.5.1. Thread-Zustände (ready, running, standby, waiting, transition)
#### 2.2.5.2. Prioritätsklassen (Real-Time, High, Normal, Idle)
#### 2.2.5.3. Relative Prioritäten
#### 2.2.5.4. Priority Boosting und Quantum Stretching
#### 2.2.5.5. SMP-Support (Affinity Scheduling)
### 2.2.6. Beispiel: Linux Scheduling
#### 2.2.6.1. O(1) Scheduler (Active/Expired Arrays)
#### 2.2.6.2. Completely Fair Scheduler (CFS)
##### 2.2.6.2.1. Red-Black-Tree
##### 2.2.6.2.2. Virtual Runtime (vruntime)
##### 2.2.6.2.3. Task Group Scheduling
#### 2.2.6.3. EEVDF (Earliest Eligible Virtual Deadline First)
## 2.3. Thread-Konzepte
### 2.3.1. Definition Thread (Leichtgewichtsprozess) vs. Task
### 2.3.2. User-Level vs. Kernel-Level Threads
### 2.3.3. Mapping-Modelle (Many-to-one, One-to-one, Many-to-many)
### 2.3.4. POSIX Threads (Pthreads)
#### 2.3.4.1. `pthread_create`, `pthread_join`, `pthread_exit`, `pthread_detach`
- **`pthread_create`** → Thread starten
- **`pthread_join`** → Auf Thread warten / Rückgabewert holen
- **`pthread_exit`** → Thread explizit beenden
- **`pthread_detach`** → Thread unabhängig laufen lassen, Ressourcen automatisch freigeben

#### 2.3.4.2. Thread-Safety / Reentrancy
### 2.3.5. Java Threads (`extends Thread`, `run`)
### 2.3.6. Threads in Python (Global Interpreter Lock - GIL)
## 2.4. Interprozesskommunikation (IPC)
### 2.4.1. Signale (SIGKILL, SIGINT, SIGSTOP, etc.)
#### 2.4.1.1. Signalbehandlung (Default Action, Catching, Ignoring)
### 2.4.2. Pipes (Unidirektional, gepuffert, File Descriptors)
### 2.4.3. Sockets
#### 2.4.3.1. Communication Domains (AF_INET, AF_UNIX)
#### 2.4.3.2. Socket-Adressen und Ports
#### 2.4.3.3. Client-Server-Modell
#### 2.4.3.4. Byte Order (Big Endian vs. Little Endian)
#### 2.4.3.5. Systemaufrufe (`socket`, `bind`, `listen`, `accept`, `connect`)
#### 2.4.3.6. I/O-Multiplexing (`select`, `poll`, `epoll`)

# 3.  Synchronisation nebenläufiger Prozesse
## 3.1. Grundlagen
### 3.1.1. Race Conditions
### 3.1.2. Kritischer Bereich
### 3.1.3. Wechselseitiger Ausschluss (Mutual Exclusion)
### 3.1.4. Koordinationsprobleme (Producer-Consumer, Readers-Writers)
## 3.2. Fehlerbeispiele
### 3.2.1. Therac-25 (Softwarefehler in der Strahlentherapie)
## 3.3. Lösungsansätze
### 3.3.1. Synchronisationshardware (Interrupts sperren)
### 3.3.2. Busy Waiting (Spin Locking)
#### 3.3.2.1. Peterson-Algorithmus
### 3.3.3. Semaphore (Dijkstra)
#### 3.3.3.1. Operationen (DOWN/P, UP/V)
#### 3.3.3.2. Binäre Semaphore (Mutex)
#### 3.3.3.3. Anwendung auf Producer-Consumer und Readers-Writers
### 3.3.4. Monitore (Hoare, Brinch Hansen)
#### 3.3.4.1. Bedingungsvariablen (`wait`, `signal`)
#### 3.3.4.2. Java Monitore (`synchronized`, `wait`, `notify`, `notifyAll`)
#### 3.3.4.3. Pthread Mutex und Condition Variables
### 3.3.5. Nachrichtensysteme (Message Passing)
#### 3.3.5.1. `send`, `receive`
#### 3.3.5.2. Mailboxen

# 4.  Speicherverwaltung
## 4.1. Speicherhierarchie (Register, Cache, Hauptspeicher, Hintergrundspeicher)
## 4.2. Swapping
### 4.2.1. Definition
### 4.2.2. Externe Fragmentierung
### 4.2.3. Belegungsstrategien (First Fit, Next Fit, Best Fit, Worst Fit)
### 4.2.4. Buddy-Verfahren (Vermeidung externer Fragmente, Interne Fragmente)
## 4.3. Virtuelle Adressierung
### 4.3.1. Seiten (Pages) und Seitenrahmen (Page Frames)
### 4.3.2. Seitentabellen und MMU
### 4.3.3. Translation Lookaside Buffer (TLB)
### 4.3.4. Mehrstufige Seitentabellen
## 4.4. Paging-Verfahren
### 4.4.1. Seitenfehler (Page Fault)
### 4.4.2. Demand Paging
### 4.4.3. Seitenflattern (Thrashing)
### 4.4.4. Seitenersetzungsstrategien
#### 4.4.4.1. FIFO (Belady's Anomalie)
#### 4.4.4.2. LRU (Least Recently Used)
#### 4.4.4.3. Optimaler Algorithmus (Belady)
#### 4.4.4.4. Stack-Algorithmen
### 4.4.5. Working-Set-Modell
## 4.5. Beispiel UNIX Speicherverwaltung
### 4.5.1. Core Map
### 4.5.2. Pagedaemon
### 4.5.3. Two-handed Clock Algorithm
## 4.6. Beispiel Windows NT Speicherverwaltung
### 4.6.1. Minimum/Maximum Working Set
### 4.6.2. Automatic Working Set Trimming
## 4.7. Beispiel Linux Speicherverwaltung
### 4.7.1. Slab Allocator
### 4.7.2. Buddy-Listen (`free_area`)

# 5.  Dateisysteme
## 5.1. Grundlagen
### 5.1.1. Dateiattribute
### 5.1.2. Dateitypen (Benutzer, System, Executables wie ELF)
### 5.1.3. Operationen (`open`, `read`, `write`, `mmap`)
### 5.1.4. Verzeichnisstruktur
## 5.2. Implementierung
### 5.2.1. Inodes (UNIX)
### 5.2.2. Blockadressierung (direkt, einfach indirekt, doppelt indirekt)
### 5.2.3. Superblock
## 5.3. Konkrete Dateisysteme
### 5.3.1. Berkeley Fast File System (FFS)
#### 5.3.1.1. Zylindergruppen
#### 5.3.1.2. Fragmente
### 5.3.2. Linux Dateisysteme (Ext2, Ext3, Ext4)
#### 5.3.2.1. Journaling (Modes: Journal, Ordered, Writeback)
#### 5.3.2.2. Extents
### 5.3.3. Windows NTFS
#### 5.3.3.1. Master File Table (MFT)
#### 5.3.3.2. Resident Files (< 1KB)
#### 5.3.3.3. Attribute und Runs
## 5.4. Sicherheit und Zugriffsrechte
### 5.4.1. Protection Domain
### 5.4.2. Access Control Lists (ACLs)
### 5.4.3. Capability Lists
### 5.4.4. UNIX Zugriffsrechte (UID, GID, rwx)
### 5.4.5. Erweiterte ACLs unter Linux (setfacl, getfacl)

### Teil II: Grundlagen Rechnernetze

# 6.  Einführung Rechnernetze
## 6.1. Netzwerkkategorien
### 6.1.1. LAN (Local Area Network)
### 6.1.2. MAN (Metropolitan Area Network)
### 6.1.3. WAN (Wide Area Network, z.B. Starlink)
## 6.2. Referenzmodelle
### 6.2.1. ISO/OSI-Referenzmodell (7 Schichten)
#### 6.2.1.1. Bitübertragungsschicht (Physical Layer)
#### 6.2.1.2. Sicherungsschicht (Link Layer)
#### 6.2.1.3. Vermittlungsschicht (Network Layer)
#### 6.2.1.4. Transportschicht (Transport Layer)
#### 6.2.1.5. Sitzungsschicht (Session Layer)
#### 6.2.1.6. Darstellungsschicht (Presentation Layer)
#### 6.2.1.7. Anwendungsschicht (Application Layer)
### 6.2.2. TCP/IP-Referenzmodell
## 6.3. Standardisierung
### 6.3.1. IETF und RFCs

# 7.  Sicherungsschicht (Layer 2)
## 7.1. Aufgaben
### 7.1.1. Rahmenbildung (Framing)
### 7.1.2. Fehlerkontrolle
### 7.1.3. Flusssteuerung
## 7.2. Fehlerbehandlung
### 7.2.1. Hamming-Abstand
### 7.2.2. Fehlerkorrektur (Hamming-Code)
### 7.2.3. Fehlererkennung (CRC - Cyclic Redundancy Check)
#### 7.2.3.1. Generatorpolynome
#### 7.2.3.2. Modulo-2-Arithmetik
## 7.3. Protokolle zur Flusssteuerung
### 7.3.1. Stop-and-Wait
### 7.3.2. PAR (Positive Acknowledgement with Retransmission)
### 7.3.3. Sliding Window (Schiebefenster)
#### 7.3.3.1. Go-Back-N
#### 7.3.3.2. Selective Repeat
### 7.3.4. Piggybacking
## 7.4. HDLC (High-level Data Link Control)
### 7.4.1. Rahmenformat (Flags, Bitstopfen)
### 7.4.2. Rahmentypen (I-Frames, S-Frames, U-Frames)
### 7.4.3. Betriebsarten (NRM, ARM, ABM)
## 7.5. PPP (Point-to-Point Protocol)
### 7.5.1. LCP (Link Control Protocol)
### 7.5.2. NCP (Network Control Protocol)
### 7.5.3. Zustandsautomat

# 8.  Lokale Netze (LAN)
## 8.1. Ethernet (IEEE 802.3)
### 8.1.1. CSMA/CD-Verfahren (Carrier Sense Multiple Access / Collision Detection)
### 8.1.2. Binary Exponential Backoff
### 8.1.3. Rahmenformat und Adressierung (MAC)
### 8.1.4. Kabeltypen (10Base5, 10Base2, 10Base-T, Glasfaser)
## 8.2. Wireless LAN (IEEE 802.11)
### 8.2.1. Hidden Station Problem
### 8.2.2. CSMA/CA (Collision Avoidance)
### 8.2.3. RTS/CTS (Ready to Send / Clear to Send)
### 8.2.4. NAV (Network Allocation Vector)
## 8.3. Zugangstechnologien
### 8.3.1. DSL
### 8.3.2. PPPoE (Discovery Stage, Session Stage)

# 9.  Vermittlungsschicht (Layer 3)
## 9.1. Aufgaben
### 9.1.1. Routing (Wegwahl)
### 9.1.2. Fragmentierung (MTU)
## 9.2. Routing-Verfahren
### 9.2.1. Statisch / Isoliert
#### 9.2.1.1. Fluten
#### 9.2.1.2. Hot-Potato
#### 9.2.1.3. Backward Learning
### 9.2.2. Adaptiv / Global
#### 9.2.2.1. Distance Vector Routing (RIP)
#### 9.2.2.2. Link State Routing (OSPF, Dijkstra-Algorithmus)
#### 9.2.2.3. BGP (Border Gateway Protocol) zwischen Autonomen Systemen
## 9.3. Internet Protocol (IPv4)
### 9.3.1. Adressierung (Klassen A-E, CIDR, Subnetze)
### 9.3.2. Header-Format (TTL, Protocol, Checksum)
### 9.3.3. Fragmentierung und Reassembly
### 9.3.4. Hilfsprotokolle
#### 9.3.4.1. ARP (Address Resolution Protocol)
#### 9.3.4.2. ICMP (Internet Control Message Protocol, Ping, Traceroute)

# 10. Transportschicht (Layer 4)
## 10.1. UDP (User Datagram Protocol)
### 10.1.1. Eigenschaften (Verbindungslos, unzuverlässig)
### 10.1.2. Header-Format
### 10.1.3. Pseudoheader für Checksummenberechnung
### 10.1.4. Ports (Well-Known Ports)
## 10.2. TCP (Transmission Control Protocol)