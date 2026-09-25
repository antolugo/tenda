// Apre annunci per ID e salva titolo, descrizione, prezzo e foto. Uso: OUT=det.json node details.js <id> <id> ...
const { chromium } = require(require('child_process').execSync('npm root -g').toString().trim()+'/playwright');
const fs=require('fs');
const crypto=require('crypto');
function proxySpki(){const pem=fs.readFileSync('/root/.ccr/ca-bundle.crt','utf8').match(/-----BEGIN CERTIFICATE-----[\s\S]+?-----END CERTIFICATE-----/g)||[];return pem.map(p=>new crypto.X509Certificate(p)).filter(c=>/Anthropic/.test(c.subject)).map(c=>crypto.createHash('sha256').update(c.publicKey.export({type:'spki',format:'der'})).digest('base64'));}
(async()=>{
 const b = await chromium.launch({args:['--ignore-certificate-errors-spki-list='+proxySpki().join(',')]});
 const p = await b.newPage({locale:'it-IT', userAgent:'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/141.0.0.0 Safari/537.36'});
 const res=[];
 for (const id of process.argv.slice(2)){
  try{
   await p.goto('https://www.vinted.it/items/'+id, {waitUntil:'domcontentloaded'});
   await p.waitForTimeout(4500);
   const r = await p.evaluate(()=>{
     const d=document.querySelector('[itemprop="description"]');
     const h=document.querySelector('h1');
     const imgs=[...document.querySelectorAll('img')].map(i=>i.src).filter(s=>/images\d*\.vinted\.net\/t\//.test(s));
     const price=(document.body.innerText.match(/[\d.,]+\s?€/)||[''])[0];
     const sold=/Venduto|Riservato/.test(document.body.innerText.slice(0,3000));
     return {title:h?h.innerText:'',desc:d?d.innerText.replace(/\s+/g,' '):'',imgs:[...new Set(imgs)],price,sold};
   });
   r.id=id; res.push(r); console.error(id, r.imgs.length);
  }catch(e){console.error(id,'ERR',e.message)}
 }
 fs.writeFileSync(process.env.OUT||'det.json',JSON.stringify(res));
 await b.close();
})();
