# Crea una griglia con le foto grandi di ogni annuncio (det_<id>.jpg). Uso: python3 detailsheet.py det.json
import json,urllib.request,ssl,io,sys,re
from PIL import Image,ImageDraw
ctx=ssl.create_default_context(cafile='/root/.ccr/ca-bundle.crt')
res=json.load(open(sys.argv[1]))
for r in res:
    urls=[re.sub(r'/\d+x\d+/','/f800/',u) for u in r['imgs']][:6]
    ims=[]
    for u in urls:
        try: ims.append(Image.open(io.BytesIO(urllib.request.urlopen(urllib.request.Request(u,headers={'User-Agent':'Mozilla/5.0'}),context=ctx,timeout=20).read())).convert('RGB'))
        except Exception as e:
            try: ims.append(Image.open(io.BytesIO(urllib.request.urlopen(urllib.request.Request(r['imgs'][len(ims)],headers={'User-Agent':'Mozilla/5.0'}),context=ctx,timeout=20).read())).convert('RGB'))
            except: pass
    if not ims: continue
    W=500; cols=3; rows=(len(ims)+cols-1)//cols
    sh=Image.new('RGB',(W*cols,W*rows),'white')
    for k,im in enumerate(ims):
        im.thumbnail((W-4,W-4)); sh.paste(im,((k%cols)*W+2,(k//cols)*W+2))
    sh.save(f"det_{r['id']}.jpg",quality=85)
    print(r['id'],'|',r['price'],'| sold' if r['sold'] else '','|',r['title'],'||',r['desc'][:500])
