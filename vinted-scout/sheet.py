# Crea griglie di anteprime numerate. Uso: python3 sheet.py sel.jsonl prefisso
import json,sys,os,urllib.request,ssl
from PIL import Image,ImageDraw
from concurrent.futures import ThreadPoolExecutor
ctx=ssl.create_default_context(cafile='/root/.ccr/ca-bundle.crt')
items=[json.loads(l) for l in open(sys.argv[1])]
prefix=sys.argv[2]
os.makedirs('th',exist_ok=True)
def get(it):
    fn='th/'+it['u'].split('/items/')[1].split('-')[0]+'.jpg'
    if not os.path.exists(fn) and it.get('img'):
        try:
            req=urllib.request.Request(it['img'],headers={'User-Agent':'Mozilla/5.0'})
            open(fn,'wb').write(urllib.request.urlopen(req,context=ctx,timeout=20).read())
        except Exception as e: return None
    return fn if os.path.exists(fn) else None
with ThreadPoolExecutor(16) as ex: fns=list(ex.map(get,items))
W,H,C=260,300,6
pairs=[(i,f) for i,f in enumerate(fns) if f]
for s in range(0,len(pairs),30):
    chunk=pairs[s:s+30]; rows=(len(chunk)+C-1)//C
    sheet=Image.new('RGB',(W*C,H*rows),'white'); d=ImageDraw.Draw(sheet)
    for k,(i,f) in enumerate(chunk):
        try: im=Image.open(f).convert('RGB'); im.thumbnail((W-6,H-40))
        except: continue
        x,y=(k%C)*W,(k//C)*H
        sheet.paste(im,(x+3,y+3))
        d.rectangle([x,y+H-36,x+W,y+H],fill='black')
        d.text((x+4,y+H-34),f"#{i} {items[i]['price']}",fill='yellow')
        d.text((x+4,y+H-20),items[i]['t'][:40],fill='white')
    sheet.save(f'{prefix}_{s//30}.jpg',quality=80)
print(len(pairs))
