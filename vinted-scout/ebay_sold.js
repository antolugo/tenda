// Prezzi di vendita reali da eBay (inserzioni concluse e vendute). Uso: node ebay_sold.js "query1" "query2" ...
const { chromium } = require(require('child_process').execSync('npm root -g').toString().trim() + '/playwright');
const fs = require('fs'), crypto = require('crypto');
function proxySpki(){const pem=fs.readFileSync('/root/.ccr/ca-bundle.crt','utf8').match(/-----BEGIN CERTIFICATE-----[\s\S]+?-----END CERTIFICATE-----/g)||[];return pem.map(p=>new crypto.X509Certificate(p)).filter(c=>/Anthropic/.test(c.subject)).map(c=>crypto.createHash('sha256').update(c.publicKey.export({type:'spki',format:'der'})).digest('base64'));}
(async()=>{
 const b=await chromium.launch({args:['--ignore-certificate-errors-spki-list='+proxySpki().join(',')]});
 const p=await b.newPage({locale:'it-IT',userAgent:'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/141.0.0.0 Safari/537.36'});
 p.setDefaultTimeout(30000);
 for(const q of process.argv.slice(2)){
  try{
   await p.goto('https://www.ebay.it/',{waitUntil:'domcontentloaded'}).catch(()=>{}); await p.waitForTimeout(2000); await p.goto('https://www.ebay.it/sch/i.html?_nkw='+encodeURIComponent(q)+'&LH_Sold=1&LH_Complete=1&_ipg=120',{waitUntil:'domcontentloaded'});
   await p.waitForTimeout(3000);
   const rows=await p.$$eval('li.s-item, li.s-card, .srp-results li',els=>els.map(e=>e.innerText.replace(/\s+/g,' ')).filter(t=>/EUR|€/.test(t)));
   console.log(JSON.stringify({q,title:await p.title(),n:rows.length,rows:rows.slice(0,60)}));
  }catch(e){console.log(JSON.stringify({q,err:e.message.split('\n')[0]}))}
 }
 await b.close();
})();
