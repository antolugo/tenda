# Scarta per titolo abbigliamento, gadget, riproduzioni ecc. Uso: python3 filter.py new.jsonl sel.jsonl
import json, re, sys
bad = re.compile(r't-shirt|tshirt|maglia|maglietta|felpa|profum|parfum|eau de|scatola|box|sacchett|dust ?bag|cover|custodia|portachiavi|poster|catalog|rivista|adesiv|cartolin|stile|tipo |ispirat|replica|riproduz|imitaz|simil|inspired|style|camicia|gonna|vestito|jeans|scarpe|sneaker|borsa|pantalon|giacca|cintura|cappello|sciarpa|occhiali|lego|funko|barbie|peluche|candela|biglietto|packaging|ricambio|lampadina|tazza|mug|pigiama|calzin|reggiseno|costume|smalto|crema|trucco|telefono|iphone|samsung|cuffie|cavo|caricatore|manuale|libretto istruzioni|dvd|blu-ray|tcg|funko', re.I)
n = 0
with open(sys.argv[2], 'w') as out:
    for l in open(sys.argv[1]):
        j = json.loads(l)
        if not j.get('img') or bad.search(j['t'].split(', Condizioni')[0]):
            continue
        out.write(json.dumps(j) + '\n'); n += 1
print('dopo filtro:', n)
