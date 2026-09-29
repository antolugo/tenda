# Blocco conta-assi e circuiti di binario in audiofrequenza (cdb AF) su una linea AV a 250 km/h

**Analisi comparativa multi-agente con voti da 0.1 a 9.9**

> Voto alto = soluzione migliore nel criterio: più sicura, più economica, più disponibile, ecc.
> CA = blocco conta-assi (Frauscher FAdC/RSR180, Thales/Hitachi AzLM, Siemens Clearguard ACM200, ecc.)
> cdb AF = circuiti di binario jointless in audiofrequenza (UM71/UM2000, TI21/EBI Track, FTGS, cdb AF RFI)

---

## 0. Scenario di riferimento e metodo

**Scenario:**
- linea AV/AC a 250 km/h (predisposta a 300);
- segnalamento ERTMS/ETCS Livello 2 senza segnali laterali;
- trazione 25 kV 50 Hz, con 3 kV cc su interconnessioni e nodi;
- sezioni di blocco da 1,3 a 2,7 km;
- tracciato in parte su ballast, in parte su platea (slab track), con gallerie e viadotti lunghi;
- finestre di manutenzione notturne ridotte e distanziamento commerciale di 3-5 minuti.

**Metodo:** sette agenti specialistici hanno lavorato in parallelo, ciascuno su un dominio, valutando da 8 a 14 sotto-criteri con voto e motivazione tecnica. Ogni agente ha poi espresso un voto sintetico di dominio. La sintesi finale è una media pesata tra domini, con un'analisi di sensibilità sui pesi.

| # | Agente / dominio | Sotto-criteri |
|---|---|---|
| 1 | Costi (CAPEX + LCC 40 anni) | 12 |
| 2 | Manutenzione, affidabilità, disponibilità (RAM) | 12 |
| 3 | Sicurezza (SIL, guasti pericolosi, fattore umano) | 13 |
| 4 | Prestazioni tecniche, EMC, integrazione | 13 |
| 5 | Esercizio, capacità, gestione del degrado | 12 |
| 6 | Ambiente, clima, interfaccia con l'infrastruttura | 14 |
| 7 | Normativa, certificazione, interoperabilità, strategia | 12 |

**Totale: 88 sotto-criteri valutati.**

> **Avvertenza.** I valori economici e affidabilistici sono ordini di grandezza (±40-50%) ricavati da letteratura tecnica, dati dei costruttori e prassi europea. Non vengono da listini o statistiche FRACAS di RFI/Italferr. Le informazioni sulle scelte di singoli gestori (HS2, ADIF, Infrabel) e su eventuali indirizzi formali di RFI sono segnalate come **da verificare**. Prima di usare i risultati per una decisione di progetto, vanno ricalibrati sui dati reali del gestore.

---

## 1. Principio di funzionamento, in breve

| Aspetto | Conta-assi | cdb AF |
|---|---|---|
| Principio | Conta gli assi in ingresso e in uscita dalla sezione con sensori induttivi a doppio sistema: libero se i conteggi coincidono | Un segnale AF modulato viaggia nelle rotaie da TX a RX, l'asse cortocircuita le rotaie (shunt) e il ricevitore cade |
| Uso delle rotaie | Nessuno: le rotaie restano libere per il ritorno della trazione e per la messa a terra | Le rotaie sono il conduttore del segnale |
| Natura del fail-safe | Logico/software: memoria del conteggio | Fisico: assenza di segnale = occupato |
| Stato dopo un disturbo | Occupato e disturbato, **serve un reset** | **Si ripristina da solo** quando il disturbo cessa |
| Lunghezza della sezione | Praticamente illimitata (dipende solo dalla comunicazione) | Circa 1-1,5 km in condizioni sfavorevoli di ballast o platea |
| Rotaia rotta | Non rilevata | Rilevata **in parte**, senza garanzia |
| Codici al treno | No | Sì, se codificato (BACC/TVM), ma inutile in L2 puro |

---

## 2. Risultati per dominio

### 2.1 Costi: CAPEX e LCC su 40 anni (agente 1)

| # | Sotto-criterio | CA | cdb AF | Nota |
|---|---|---|---|---|
| 1 | Apparecchiature per sezione e per km | **7.5** | 4.6 | CA ≈ 20-40 k€/sezione, cdb ≈ 35-60 k€ (condensatori di compensazione ogni 60-100 m) |
| 2 | Cavi e shelter/PPF | **7.8** | 4.0 | Il cdb vincola le distanze TX/RX dal posto periferico, il CA è concentrabile su fibra o IP |
| 3 | Connessioni di binario e ritorno TE | **8.2** | 3.5 | Il cdb richiede bond, unità di accordo, vincoli EN 50122 e gestione della cc a 3 kV |
| 4 | Opere e installazione, finestre d'esercizio | **7.8** | 4.2 | Il cdb richiede circa 2-3 volte più ore in finestra notturna |
| 5 | Progettazione, taratura, EMC | **7.2** | 4.0 | Il cdb richiede un piano frequenze e una taratura per ogni sezione |
| 6 | Messa in servizio e collaudo | **7.3** | 4.8 | Il collaudo del cdb costa circa 1,5-2 volte |
| 7 | Energia | **7.6** | 5.6 | Pesa meno del 2% del costo totale di possesso (TCO) |
| 8 | Manutenzione ordinaria e ricambi | **7.2** | 4.6 | CA ≈ 1-2 k€/sezione/anno, cdb ≈ 2,5-5 k€ |
| 9 | Costo dei disservizi (reset e false occupazioni) | 5.2 | **6.3** | Ogni reset su AV costa circa 1-10 k€ tra ritardi e penali |
| 10 | Sistemi compensativi per la rotaia rotta | 4.5 | **7.5** | Con il CA serve più diagnostica a ultrasuoni o una fibra DAS (≈5-15 k€/km) |
| 11 | Obsolescenza e rinnovo a metà vita | **6.2** | 4.8 | UM71 e TI21 sono a fine vita |
| 12 | Retrofit e migrazione | **7.6** | 3.8 | |
| | **Voto di dominio** | **7.1** | **4.7** | |

**TCO indicativo su 40 anni per km di doppio binario:**
- **CA ≈ 150-320 k€/km**
- **cdb AF ≈ 270-560 k€/km**

Il CA costa circa il 35-45% in meno. Il risultato si ribalta solo se ci sono cdb già esistenti e funzionanti da rinnovare solo nell'elettronica, oppure se si impone un sistema dedicato e costoso di rilevamento della rotaia rotta.

### 2.2 Manutenzione, affidabilità e disponibilità (RAM) (agente 2)

| # | Sotto-criterio | CA | cdb AF | Nota |
|---|---|---|---|---|
| 1 | MTBF intrinseco | **7.8** | 6.5 | Il cdb ha molti componenti passivi in campo (unità di accordo, bond, condensatori) |
| 2 | Robustezza ambientale (ballast, galleria, sale) | **8.2** | 5.0 | Il cdb dipende da una resistenza di ballast ≥ 1,5-3 Ω·km |
| 3 | EMC (trazione, freni) | 6.3 | 6.2 | Parità: il CA è vulnerabile ai freni a correnti parassite e magnetici, il cdb alle armoniche |
| 4 | Reset e recupero in ETCS L2 | 4.5 | **8.5** | Punto debole principale del CA |
| 5 | MTTR e diagnosi del guasto | **7.8** | 5.5 | CA ≈ 1-2 h, cdb ≈ 2-4 h, con guasti intermittenti legati all'umidità |
| 6 | Interferenza con i lavori al binario | **6.5** | 5.0 | Sensori a morsetto contro bond da risaldare |
| 7 | Carico di manutenzione preventiva | **8.0** | 5.5 | CA ≈ 0,3-0,8 interventi/km/anno, cdb ≈ 1-2 |
| 8 | Diagnostica remota e manutenzione predittiva | **8.3** | 6.8 | |
| 9 | Competenze richieste al personale | **7.0** | 5.5 | Le competenze AF sono sempre più rare |
| 10 | Ricambi, vita utile, obsolescenza | **6.8** | 6.5 | |
| 11 | Rotaia rotta come valore manutentivo | 2.5 | **8.0** | |
| 12 | Sezioni lunghe, gallerie, viadotti | **8.5** | 5.5 | |
| | **Voto di dominio** | **7.1** | **6.0** | |

### 2.3 Sicurezza (agente 3)

| # | Sotto-criterio | CA | cdb AF | Nota |
|---|---|---|---|---|
| 1 | Integrità SIL4 e fail-safe del dispositivo | **9.0** | 8.5 | Entrambi disponibili in versioni certificate SIL4 |
| 2 | Mancato shuntaggio (ruggine, foglie, sabbia, contaminazione) | **9.6** | 4.5 | È **il** guasto pericoloso strutturale del cdb |
| 3 | Veicoli leggeri o con pochi assi | **8.0** | 4.0 | |
| 4 | Armoniche di trazione (25 kV, chopper, 3 kV cc) | **7.5** | 5.5 | Rischio di un "libero" spurio nel cdb |
| 5 | Cross-talk e zona di sintonia | **8.8** | 5.5 | Il cdb ha 20-30 m di zona "sfumata" ai giunti elettrici |
| 6 | Conteggio errato, ruota lenta o oscillante | 7.5 | **9.0** | |
| 7 | Freni a correnti parassite e freni magnetici | 5.5 | **7.0** | Tema specifico dell'AV |
| 8 | Rilevamento della rotaia rotta | 0.5 | **5.0** | Nel cdb è solo opportunistico, non una funzione SIL |
| 9 | Veicoli introdotti o rimossi lateralmente | 2.5 | **6.5** | **È il guasto pericoloso più grave del CA** |
| 10 | Reset e ripristino dopo una mancanza di alimentazione | 3.5 | **8.5** | |
| 11 | Deviatoi e stazioni | **8.5** | 6.0 | |
| 12 | Compatibilità con ETCS L2, Hybrid L3 e moving block | **8.5** | 6.5 | |
| 13 | Fattore umano nei modi degradati | 4.0 | **7.0** | Rischio di un reset convalidato "per abitudine" |
| | **Voto di dominio** | **6.9** | **6.4** | Media pesata sui criteri 2, 9, 10 e 13 |

I due sistemi hanno **profili di rischio diversi**:
- il cdb ha un rischio **fisico e ambientale**: shunt e armoniche;
- il CA ha un rischio **logico e umano**: reset e veicoli inseriti in sezione.

Su una linea AV le rotaie sono lucidate dal traffico e il materiale rotabile è omologato e omogeneo. Il principale rischio del cdb (lo shunt) quindi si riduce molto. Resta però presente su precedenze, comunicazioni e interconnessioni.

### 2.4 Prestazioni tecniche, EMC e integrazione (agente 4)

| # | Sotto-criterio | CA | cdb AF | Nota |
|---|---|---|---|---|
| 1 | Velocità e discriminazione degli assi (250 → 350 km/h) | 8.6 | **8.8** | Sensori certificati fino a 400-450 km/h; a 350 km/h la ruota passa sul sensore in circa 1-2 ms |
| 2 | Lunghezza massima della sezione | **9.6** | 4.2 | Un blocco da 2,7 km richiede 2-3 cdb in cascata |
| 3 | Slab track, viadotti, gallerie | **8.4** | 4.8 | |
| 4 | EMC con materiale rotabile e trazione (ERA/ERTMS/033281) | **7.0** | 6.0 | Per il cdb i limiti di corrente armonica restano in parte nazionali |
| 5 | Ritorno di trazione e messa a terra (EN 50122, 2×25 kV) | **9.5** | 4.5 | |
| 6 | Zone deviatoio e flessibilità topologica | **9.0** | 5.0 | |
| 7 | Tempi di occupazione e liberazione, capacità | **8.5** | 7.5 | Il cdb ha ritardi di rilascio di circa 1-3 s |
| 8 | Disponibilità e ripristino dopo un disturbo | 6.5 | **7.5** | |
| 9 | Integrazione con ACC/ACCM, IXL e RBC | **8.8** | 7.8 | Il CA si collega nativamente via IP (EULYNX SCI-TDS, RaSTA) |
| 10 | Trasmissione dei codici e backup nazionale | 3.0 | **8.5** | Criterio con **peso basso** in L2 puro |
| 11 | Evoluzione verso L3 e moving block | **8.0** | 6.5 | |
| 12 | Scalabilità e architettura distribuita | **8.8** | 6.0 | |
| 13 | Rotaia rotta e funzioni ausiliarie | 3.5 | **7.0** | |
| | **Voto di dominio** | **8.2** | **6.3** | |

### 2.5 Esercizio, capacità e gestione del degrado (agente 5)

| # | Sotto-criterio | CA | cdb AF | Nota |
|---|---|---|---|---|
| 1 | Frequenza di false occupazioni | **7.0** | 6.0 | |
| 2 | Autoripristino dopo guasti transitori | 3.5 | **8.8** | Argomento più forte a favore del cdb |
| 3 | Procedura di reset: tempi e rischio | 3.8 | **7.5** | Il reset preparatorio costa ≈ 10-20 min per sezione |
| 4 | Comportamento dopo una mancanza di alimentazione | 3.0 | **8.0** | Rischio di **reset in massa** (≈5-5.5 con buoni UPS) |
| 5 | Mezzi d'opera e restituzione della linea al mattino | 4.0 | **7.0** | Sezioni "sporche" alle 6:00 |
| 6 | Robustezza ambientale | **7.0** | 5.5 | |
| 7 | Capacità, distanziamento, sezioni lunghe | **7.8** | 7.3 | In L2 a blocco fisso la capacità dipende poco dalla tecnologia di rilevamento |
| 8 | Veicoli leggeri, manovre, treni diagnostici | **7.0** | 6.0 | |
| 9 | Manutenibilità (effetto sull'esercizio) | **7.5** | 6.0 | |
| 10 | Istruzioni e formazione DCO/DCCM (contesto RFI) | 4.5 | **8.0** | Il personale AV RFI è già formato sul cdb AF |
| 11 | Rotaia rotta come informazione per l'esercizio | 2.5 | **7.0** | |
| 12 | Interoperabilità e tendenze europee | **7.5** | 6.0 | |
| | **Voto di dominio** | 5.5 | **6.9** | Con mitigazioni robuste il CA sale a ≈ 6.5 |

**Impatto di una falsa occupazione a 250 km/h (stima):**
- il primo treno perde circa 8-20 minuti in marcia a vista (OS/SR) su 2,7 km;
- con un distanziamento di 3-5 minuti il ritardo si propaga, e un singolo evento può produrre **decine o oltre cento minuti di ritardo cumulato**.

**Conta più la durata del degrado che la sua frequenza.** È qui che il CA perde.

### 2.6 Ambiente, clima e interfaccia con l'infrastruttura (agente 6)

| # | Sotto-criterio | CA | cdb AF | Nota |
|---|---|---|---|---|
| 1 | Umidità, pioggia, allagamenti, resistenza del ballast | **8.6** | 4.2 | |
| 2 | Slab track e gallerie lunghe con percolazioni | **8.8** | 3.8 | Vantaggio decisivo in gallerie da 10-50 km |
| 3 | Qualità dello shunt (ruggine, fogliame, sabbia) | **9.2** | 3.5 | |
| 4 | Neve, ghiaccio, ghiaccio che cade dai rotabili | 6.3 | **6.6** | |
| 5 | Salsedine, sali, corrosione | **6.8** | 4.8 | |
| 6 | Temperature estreme (-20/+60 °C sulla rotaia) | **7.4** | 6.9 | Il sensore CA è qualificato per -40/+85 °C |
| 7 | Fulmini, sovratensioni, EMC | **6.9** | 5.6 | Il cdb è accoppiato galvanicamente a chilometri di rotaia |
| 8 | Vibrazioni a 250 km/h, spostamento d'aria, ballast volante | 5.9 | **7.1** | **Punto debole meccanico del CA** |
| 9 | Viadotti, apparecchi di dilatazione, deviatoi AV lunghi | **8.4** | 4.6 | |
| 10 | Lavori all'armamento | **6.2** | 5.4 | Nessuno dei due è davvero favorevole |
| 11 | Rotaia rotta (funzione legata all'infrastruttura) | 1.5 | **6.8** | |
| 12 | Furto di rame e vandalismo | **7.3** | 3.9 | |
| 13 | Ingombro degli enti di campo, accessibilità in galleria | **7.6** | 5.2 | |
| 14 | Sostenibilità nel ciclo di vita (rame, energia, RAEE) | **7.5** | 5.0 | |
| | **Voto di dominio** | **7.3** | **5.0** | |

### 2.7 Normativa, certificazione, interoperabilità e strategia (agente 7)

| # | Sotto-criterio | CA | cdb AF | Nota |
|---|---|---|---|---|
| 1 | Conformità alle STI CCS 2023 e a ERA/ERTMS/033281 v5 | **8.2** | 5.6 | La v5 armonizza quasi del tutto l'interfaccia CA-veicolo |
| 2 | Interoperabilità del materiale rotabile (treni esteri) | **8.4** | 4.8 | Il cdb richiede prove rete per rete (EN 50238-2) |
| 3 | Maturità della EN 50617 (parti 1 e 2) e certificabilità | **7.8** | 6.6 | |
| 4 | Omologazione in Italia (ANSFISA, RFI) | 7.0 | **7.4** | Il cdb AF è già omologato ed esercito sull'AV RFI |
| 5 | Prontezza per Hybrid L3 e moving block | **7.9** | 5.2 | |
| 6 | Allineamento con la strategia RFI (ACC-M, Piano ERTMS) | **8.3** | 4.9 | In L2 senza segnali la funzione "codici" del cdb non serve più |
| 7 | Mercato, fornitori, rischio di lock-in | **7.6** | 4.4 | Il CA ha un mercato ampio e l'interfaccia EULYNX |
| 8 | Obsolescenza su 30-40 anni | **7.7** | 4.6 | |
| 9 | Digitalizzazione IP e cybersecurity (IEC 62443, TS 50701) | **7.4** | 5.8 | |
| 10 | Manutenzione predittiva e digital twin | **7.8** | 6.2 | |
| 11 | Esperienza consolidata sulle reti AV europee | 6.6 | **7.9** | SNCF (LGV) e RFI (AV) usano storicamente il cdb AF |
| 12 | Funzioni di sicurezza intrinseche e accettabilità normativa | 5.9 | **8.1** | |
| | **Voto di dominio** | **7.6** | **5.8** | |

---

## 3. Temi trasversali: dove gli agenti convergono

Alcuni temi sono stati valutati da più agenti in modo indipendente. La convergenza ne rafforza l'affidabilità.

| Tema | Voti CA (min-max) | Voti cdb (min-max) | Lettura |
|---|---|---|---|
| **Rotaia rotta** | 0.5-4.5 | 5.0-8.0 | Vantaggio netto del cdb, ma solo **parziale e non certificato** (i bond di ritorno a 25 kV possono "scavalcare" la frattura). La barriera vera resta la diagnostica a ultrasuoni. |
| **Reset e autoripristino** | 3.0-6.5 | 7.5-8.8 | **Il vero tallone d'Achille del CA**, segnalato da 5 agenti su 7 |
| **Lunghezza della sezione, slab track, gallerie** | 8.4-9.6 | 3.8-5.5 | **Il vero tallone d'Achille del cdb** su una linea AV moderna |
| **EMC** | 5.5-7.5 | 5.5-6.2 | Sostanziale parità: il rischio si sposta (campi magnetici per il CA, armoniche per il cdb) ma non scompare |
| **Ritorno di trazione e messa a terra** | 8.2-9.5 | 3.5-4.5 | Il CA libera le rotaie, con grande beneficio per la progettazione TE a 2×25 kV |

---

## 4. Sintesi finale pesata

### 4.1 Pesi scelti per una linea AV a 250 km/h

| Dominio | Peso | CA | cdb AF | CA × peso | cdb × peso |
|---|---|---|---|---|---|
| Sicurezza | 25% | 6.9 | 6.4 | 1.73 | 1.60 |
| Esercizio e gestione del degrado | 18% | 5.5 | 6.9 | 0.99 | 1.24 |
| Manutenzione e RAM | 15% | 7.1 | 6.0 | 1.07 | 0.90 |
| Costi (LCC) | 15% | 7.1 | 4.7 | 1.07 | 0.71 |
| Prestazioni tecniche e integrazione | 12% | 8.2 | 6.3 | 0.98 | 0.76 |
| Ambiente e infrastruttura | 8% | 7.3 | 5.0 | 0.58 | 0.40 |
| Normativa e strategia | 7% | 7.6 | 5.8 | 0.53 | 0.41 |
| **TOTALE** | **100%** | | | **6.9** | **6.0** |

### 4.2 Analisi di sensibilità: il risultato regge?

| Scenario di pesi | CA | cdb AF | Esito |
|---|---|---|---|
| Base (tabella 4.1) | **6.9** | 6.0 | CA +0.9 |
| Pesi uguali (1/7 ciascuno) | **7.1** | 5.9 | CA +1.2 |
| Priorità a sicurezza ed esercizio (35% + 25%) | **6.8** | 6.2 | CA +0.6 |
| Esercizio dominante (esercizio 40%, sicurezza 25%) | **6.5** | 6.3 | CA +0.2, **quasi parità** |
| Base con CA "mitigato" (UPS, reset preparatorio automatizzato, procedure di restituzione della linea; esercizio 6.5, sicurezza 7.3) | **7.2** | 6.0 | CA +1.2 |

**Il conta-assi resta in vantaggio in tutti gli scenari.** Il margine si assottiglia solo se si pesa quasi esclusivamente la regolarità dell'esercizio e **non** si adottano mitigazioni sul reset.

---

## 5. Vantaggi e svantaggi in sintesi

### Blocco conta-assi

**Vantaggi**
- TCO su 40 anni inferiore di circa il 35-45%, con meno componenti in campo, meno rame e meno ore in finestra notturna.
- Nessuna dipendenza da resistenza di ballast, platea, umidità in galleria, sale o ruggine.
- Nessun problema di shunt: rileva anche veicoli leggeri, rotaie ossidate, foglie e sabbia.
- Sezioni di qualsiasi lunghezza con due soli punti di conteggio; topologia libera nei deviatoi.
- Rotaie libere per il ritorno di trazione e per la messa a terra (EN 50122, 2×25 kV, 3 kV cc).
- Interfacce IP standard (EULYNX), diagnostica e manutenzione predittiva native, mercato concorrenziale.
- Allineato alle STI CCS 2023 e a ERA 033281 v5, e pronto per Hybrid L3 e moving block.

**Svantaggi**
- **Reset**: dopo un disturbo la sezione resta occupata. Il reset diretto espone all'errore umano, quello preparatorio costa 10-20 minuti di marcia a vista.
- **Mancanza di alimentazione**: rischio di reset in massa se non c'è un UPS o una memoria di stato validata.
- **Veicoli introdotti o rimossi in mezzo alla sezione** (carrelli, mezzi strada-rotaia): è il guasto pericoloso più grave, mitigato solo con procedure.
- **Non rileva la rotaia rotta.**
- Sensori esposti a vibrazioni a 250 km/h, ballast volante, ghiaccio, rincalzatrici, freni a correnti parassite e freni magnetici.
- Nel contesto RFI AV richiede nuove istruzioni operative, formazione DCO/DCCM e un nuovo dossier di sicurezza (CSM-RA, ISA, ANSFISA).

### Circuiti di binario in audiofrequenza

**Vantaggi**
- **Autoripristino**: nessun reset, e la sezione torna libera quando il disturbo cessa.
- Fail-safe fisico: la perdita del segnale equivale a sezione occupata.
- Rilevamento (parziale) della rotaia rotta.
- Tecnologia consolidata sull'AV RFI e sulle LGV SNCF, con personale già formato.
- Può trasmettere codici (BACC, TVM) per il backup nazionale, utile solo sulle interconnessioni.
- Nessun sensore meccanico esposto sul fungo della rotaia.

**Svantaggi**
- Lunghezza utile limitata (≈1-1,5 km), quindi più cdb per blocco e più punti di guasto.
- Forte dipendenza da ballast e platea: gallerie umide, viadotti e slab track sono critici.
- Il mancato shunt è un guasto pericoloso strutturale (ruggine, foglie, sabbia, veicoli leggeri).
- Vincoli pesanti sul ritorno di trazione e sulla messa a terra; armoniche 25 kV e 3 kV cc.
- CAPEX e manutenzione circa 2 volte quelli del CA, molto rame (furti), competenze AF in calo.
- Interoperabilità del materiale rotabile legata a parametri nazionali; UM71 e TI21 obsoleti, mercato di nicchia.

---

## 6. Raccomandazione

**Per una linea AV nuova a 250 km/h in ETCS L2 il blocco conta-assi è la scelta preferibile** (6.9 contro 6.0), a patto che:

1. sia adottato il **reset preparatorio o supervisionato come regola**, con treno di spazzamento in On Sight/Staff Responsible integrato con l'RBC, e con il reset diretto limitato a casi eccezionali, doppia verifica e registrazione. Nel CSM-RA va trattato come pericolo di primo livello;
2. l'alimentazione sia ad **alta disponibilità** (UPS dedicati, doppia alimentazione) e la memoria di stato validata SIL4, per evitare reset in massa;
3. si usino **architetture ridondate** (punti di conteggio sovrapposti, 2oo3) e sensori a morsetto con grado IP68, qualificati per -40/+85 °C e con protezioni antiurto;
4. la **mancata rilevazione della rotaia rotta** sia compensata con un piano di ultrasuoni rafforzato e documentato nel caso di sicurezza, ed eventualmente con monitoraggio in fibra (DAS) sui tratti critici;
5. ci siano **procedure congiunte con la manutenzione dell'armamento**: sezione fuori servizio durante i lavori e verifica e reset standardizzati alla restituzione della linea;
6. la **compatibilità EMC** con le flotte sia verificata, in particolare per freni a correnti parassite e freni magnetici (CLC/TS 50238-3, ERA 033281).

**Quando il cdb AF resta competitivo:**
- **linea esistente** già attrezzata con cdb AF funzionanti, dove basta rinnovare l'elettronica (evoluzione a basso rischio operativo, personale già formato);
- **interconnessioni e nodi** percorsi da treni non ETCS che hanno bisogno dei codici di ripetizione dei segnali;
- gestori che richiedono la rilevazione continua della rotaia rotta e non vogliono sistemi dedicati.

**Soluzione ibrida da considerare:** conta-assi in piena linea, nelle gallerie, sui viadotti e nei deviatoi, con cdb solo dove servono codici o dove un'analisi di rischio locale lo richiede.

---

## 7. Punti da verificare prima di una decisione di progetto

- Statistiche FRACAS reali di RFI su false occupazioni e reset (se esistono pilote CA) e sui guasti dei cdb AF AV.
- Prezzi di gara attuali (Italferr/RFI) per CA e cdb AF, e costo reale delle finestre notturne.
- Indirizzi formali di RFI (specifiche TC.SSB/TC.SCC) sul rilevamento treno nelle nuove linee AV e nel Piano accelerato ERTMS.
- Scelte effettive di HS2, ADIF e Infrabel sulle linee AV (segnalate come incerte dagli agenti).
- Parametri di compatibilità delle flotte che circoleranno (ETR 1000, ETR 500, Frecciarossa, treni esteri, eventuali ICE 3 con freno a correnti parassite).
