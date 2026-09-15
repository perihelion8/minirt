#!/usr/bin/env python3
"""Requires an X display. Test failure of every wrapped GUI malloc."""
from pathlib import Path
import json, os, subprocess
ROOT=Path(__file__).resolve().parents[1];os.chdir(ROOT)
OUT=Path(os.environ.get('MINIRT_TEST_OUT','/tmp/minirt-stress'));OUT.mkdir(exist_ok=True)
sources=[str(p) for p in Path('src').rglob('*.c') if not p.name.endswith('_bonus.c') and str(p) not in ['src/main.c','src/scene/cylinder_transforms.c','src/loader/parser_light.c','src/loader/parser_line.c','src/renderer/renderer_intersection.c']]
sources+=['src/loader/parser_line_bonus.c','src/loader/parser_light_bonus.c','src/loader/parser_hyperboloid_bonus.c','src/renderer/renderer_intersection_bonus.c','src/renderer/renderer_hyperboloid_bonus.c']
libs=[str(p) for p in Path('lib/libft').glob('*.c')]
subprocess.run(['gcc','-g','-O1','-Iinclude','-Ilib/libft','-Ilib/mlx_linux','tests/gui_alloc_harness.c']+sources+libs+['lib/mlx_linux/libmlx.a','-Wl,--wrap=malloc,--wrap=calloc','-lX11','-lXext','-lm','-lz','-o',str(OUT/'gui_alloc')],check=True)
base=[str(OUT/'gui_alloc'),'0','hyperboloid_bonus.rt']
r=subprocess.run(base,capture_output=True,text=True,timeout=30,check=True)
print(r.stdout,flush=True)
count=int(r.stdout.split('GUI allocations=')[1].split()[0])
results=[]
for i in list(range(count+1))+list(range(-1,-count-1,-1)):
    cmd=['valgrind','--track-origins=yes','--leak-check=full','--show-leak-kinds=all','--errors-for-leak-kinds=all','--error-exitcode=97','--log-file='+str(OUT/f'gui_alloc_{i}_valgrind.log'),str(OUT/'gui_alloc'),str(i),'hyperboloid_bonus.rt']
    r=subprocess.run(cmd,capture_output=True,text=True,timeout=40)
    (OUT/f'gui_alloc_{i}.log').write_text(r.stdout+r.stderr)
    results.append({'allocation':i,'exit':r.returncode,'output':r.stdout})
    print(i,r.returncode,r.stdout.strip(),flush=True)
# Failure of SHM image allocation enters a two-malloc fallback.
for second in [count+1,count+2]:
    tag=f'{count}_and_{second}'
    cmd=['valgrind','--track-origins=yes','--leak-check=full','--show-leak-kinds=all','--errors-for-leak-kinds=all','--error-exitcode=97','--log-file='+str(OUT/f'gui_alloc_{tag}_valgrind.log'),str(OUT/'gui_alloc'),str(count),'hyperboloid_bonus.rt',str(second)]
    r=subprocess.run(cmd,capture_output=True,text=True,timeout=40)
    (OUT/f'gui_alloc_{tag}.log').write_text(r.stdout+r.stderr)
    results.append({'allocation':tag,'exit':r.returncode,'output':r.stdout})
    print(tag,r.returncode,r.stdout.strip(),flush=True)
subprocess.run(['gcc','-g','-O1','-Iinclude','-Ilib/libft','-Ilib/mlx_linux','tests/gui_resize_harness.c']+sources+libs+['lib/mlx_linux/libmlx.a','-Wl,--wrap=malloc,--wrap=calloc','-lX11','-lXext','-lm','-lz','-o',str(OUT/'gui_resize')],check=True)
for first,second in [(0,0),(1,0),(-1,0),(1,2),(1,3)]:
    tag=f'resize_{first}_{second}'
    cmd=['valgrind','--track-origins=yes','--leak-check=full','--show-leak-kinds=all','--errors-for-leak-kinds=all','--error-exitcode=97','--log-file='+str(OUT/f'gui_alloc_{tag}_valgrind.log'),str(OUT/'gui_resize'),str(first),str(second)]
    r=subprocess.run(cmd,capture_output=True,text=True,timeout=40)
    (OUT/f'gui_alloc_{tag}.log').write_text(r.stdout+r.stderr)
    results.append({'allocation':tag,'exit':r.returncode,'output':r.stdout})
    print(tag,r.returncode,r.stdout.strip(),flush=True)
(OUT/'gui_alloc_summary.json').write_text(json.dumps(results,indent=2))
raise SystemExit(0 if all(r['exit']==0 for r in results) else 1)
