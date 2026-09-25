# vinted-scout

Ricerca oraria di oggetti di design, vetro, ceramica, argento, orologi, fotocamere e libri
sottoprezzati su Vinted Italia.

## Come funziona
1. `run.sh [prezzo_max]` apre in Chromium headless le ricerche di `queries.txt`, ordinate per
   "più recenti" e con prezzo massimo (predefinito 50 €). Tiene solo gli annunci mai visti,
   memorizzati in `work/seen.json` e inizializzati da `seen.json`.
2. `filter.py` scarta per titolo abbigliamento, gadget e riproduzioni dichiarate.
3. `sheet.py` crea in `work/` delle griglie numerate (`s_N.jpg`) con le anteprime da guardare.
4. Per i candidati, `details.js` scarica descrizione e foto complete (`OUT=det.json node details.js <id>...`)
   e `detailsheet.py det.json` crea una griglia grande per ciascuno (`det_<id>.jpg`).

## Requisiti
Node con Playwright globale, Chromium in `/opt/pw-browsers`, Python 3 con Pillow.
Il TLS del proxy viene gestito fidandosi solo delle sue CA (pin SPKI), senza disattivare i controlli.
