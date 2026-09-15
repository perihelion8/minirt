#!/usr/bin/env python3
"""Run after run_stress.py: large scenes, offscreen images, static analysis, builds."""
import json,os,subprocess,tempfile,time
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1];os.chdir(ROOT)
OUT=Path(os.environ.get('MINIRT_TEST_OUT','/tmp/minirt-stress'))
ENV={**os.environ,'ASAN_OPTIONS':'detect_leaks=0:halt_on_error=1'}
results=[]
base=(OUT/'corpus/valid.rt').read_text()
for kind,line in [('shapes','sp 50,50,50 1 255,255,255\n'),('lights','L 0,10,0 0.001 255,255,255\n')]:
    p=OUT/f'large_{kind}.rt';p.write_text(base+line*20000)
    start=time.monotonic();r=subprocess.run([str(OUT/'bonus_san'),str(p)],capture_output=True,timeout=90,env=ENV)
    (OUT/f'large_{kind}.log').write_bytes(r.stdout+r.stderr)
    results.append({'kind':kind,'extra_nodes':20000,'exit':r.returncode,'seconds':round(time.monotonic()-start,3)})
(OUT/'large_summary.json').write_text(json.dumps(results,indent=2));assert all(r['exit']==0 for r in results)
images=[]
for p in sorted((OUT/'corpus').glob('generated_*.rt'))[:16]+[Path('hyperboloid_bonus.rt'),Path('multiple_lights_bonus.rt')]:
    dest=OUT/(p.stem+'.ppm')
    subprocess.run([str(OUT/'bonus_san'),'render',str(p),str(dest)],check=True,env=ENV)
    images.append(str(dest))
(OUT/'render_summary.json').write_text(json.dumps(images,indent=2))
analyzer=OUT/'analyzer';analyzer.mkdir(exist_ok=True)
files=[p for p in Path('src').rglob('*.c') if str(p)!='src/scene/cylinder_transforms.c']
with (analyzer/'warnings.log').open('w') as log:
    for p in files:
        subprocess.run(['gcc','-Wall','-Wextra','-fanalyzer','-g','-O0','-Iinclude','-Ilib/libft','-Ilib/mlx_linux','-c',str(p),'-o',str(analyzer/(p.stem+'.o'))],stdout=log,stderr=log,check=True)
assert (analyzer/'warnings.log').stat().st_size==0
build=Path(tempfile.mkdtemp(prefix='minirt-clean-',dir='/tmp'))
cmd=['make','-j4','OBJ_DIR='+str(build/'obj'),'NAME='+str(build/'miniRT'),'BONUS_NAME='+str(build/'miniRT_bonus'),'all','bonus']
with (OUT/'fresh-build.log').open('w') as log:subprocess.run(cmd,stdout=log,stderr=log,check=True)
r=subprocess.run(cmd,capture_output=True,text=True,check=True)
assert 'gcc ' not in r.stdout and ' -o ' not in r.stdout
(OUT/'fresh-build-summary.json').write_text(json.dumps({'exit':r.returncode,'second_build':r.stdout,'path':str(build)},indent=2))
print('PASS: 2 large scenes, 18 renders,',len(files),'static-analysis files, fresh/repeat builds')
