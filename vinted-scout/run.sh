#!/bin/bash
# Un giro completo: nuovi annunci -> filtro per titolo -> griglie di anteprime in ./work
set -e
cd "$(dirname "$0")"
mkdir -p work && rm -f work/s_*.jpg
[ -f work/seen.json ] || cp seen.json work/seen.json
python3 -c "import PIL" 2>/dev/null || pip install -q pillow
node scrape.js queries.txt work/new.jsonl work/seen.json "${1:-50}"
python3 filter.py work/new.jsonl work/sel.jsonl
cd work && python3 ../sheet.py sel.jsonl s && ls s_*.jpg 2>/dev/null | wc -l
