// Scarica gli annunci più recenti di Vinted per ogni query e salva solo quelli mai visti.
// Uso: node scrape.js <queries.txt> <out.jsonl> <seen.json> [prezzo_max]
const { chromium } = require(require('child_process').execSync('npm root -g').toString().trim() + '/playwright');
const fs = require('fs');
const crypto = require('crypto');

// Chromium non legge il CA bundle del proxy: fidati solo delle CA del proxy (pin SPKI), senza disattivare TLS.
function proxySpki() {
  const pem = fs.readFileSync('/root/.ccr/ca-bundle.crt', 'utf8').match(/-----BEGIN CERTIFICATE-----[\s\S]+?-----END CERTIFICATE-----/g) || [];
  return pem.map(p => new crypto.X509Certificate(p))
    .filter(c => /Anthropic/.test(c.subject))
    .map(c => crypto.createHash('sha256').update(c.publicKey.export({ type: 'spki', format: 'der' })).digest('base64'));
}

(async () => {
  const [qFile, outFile, seenFile, maxPrice = '50'] = process.argv.slice(2);
  const seen = new Set(fs.existsSync(seenFile) ? JSON.parse(fs.readFileSync(seenFile, 'utf8')) : []);
  const b = await chromium.launch({ args: ['--ignore-certificate-errors-spki-list=' + proxySpki().join(',')] });
  const p = await b.newPage({ locale: 'it-IT', userAgent: 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/141.0.0.0 Safari/537.36' });
  const qs = fs.readFileSync(qFile, 'utf8').split('\n').map(s => s.trim()).filter(Boolean);
  const out = fs.createWriteStream(outFile);
  p.setDefaultTimeout(25000);
  let fresh = 0;
  const save = () => fs.writeFileSync(seenFile, JSON.stringify([...seen]));
  // Watchdog: un giro non deve mai superare 40 minuti (evita di accavallarsi col successivo).
  setTimeout(() => { console.error('watchdog: stop'); save(); out.end(); process.exit(0); }, 40 * 60 * 1000).unref();
  for (const q of qs) {
    try {
      await p.goto('https://www.vinted.it/catalog?order=newest_first&price_to=' + maxPrice + '&search_text=' + encodeURIComponent(q), { waitUntil: 'domcontentloaded' });
      await p.waitForTimeout(5000);
      await p.mouse.wheel(0, 3000); await p.waitForTimeout(1500);
      const items = await p.$$eval('a[href*="referrer=catalog"]', as => as.map(a => {
        let el = a, img = null;
        for (let i = 0; i < 5 && el && !img; i++) { img = el.querySelector('img'); el = el.parentElement; }
        return { t: (a.getAttribute('title') || '').replace(/\s+/g, ' '), u: a.href.replace(/\?referrer=catalog/, ''), img: img ? img.src : null };
      }));
      for (const it of items) {
        const id = it.u.split('/items/')[1].split('-')[0];
        if (seen.has(id)) continue;
        seen.add(id); fresh++;
        const m = it.t.match(/([\d.]+) €/);
        out.write(JSON.stringify({ q, id, price: m ? m[1] : '?', ...it }) + '\n');
      }
    } catch (e) { console.error(q, 'ERR', e.message.split('\n')[0]); }
    save();
  }
  out.end();
  save();
  console.log('nuovi annunci:', fresh);
  await b.close();
})();
