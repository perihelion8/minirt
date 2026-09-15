#!/usr/bin/env python3
"""Real executable CLI tests; add --gui for X11 window/input/exit tests."""
import json, os, subprocess, sys, signal
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]; os.chdir(ROOT)
OUT=Path(os.environ.get('MINIRT_TEST_OUT','/tmp/minirt-stress')); OUT.mkdir(exist_ok=True)
ENV={**os.environ,'ASAN_OPTIONS':'detect_leaks=0:halt_on_error=1'}
common=[str(p) for p in Path('src').rglob('*.c') if not p.name.endswith('_bonus.c') and str(p) not in ['src/scene/cylinder_transforms.c','src/loader/parser_light.c','src/loader/parser_line.c','src/renderer/renderer_intersection.c']]
libs=[str(p) for p in Path('lib/libft').glob('*.c')]
results=[]
for mode in ([] if '--only-gui' in sys.argv or '--fullscreen-only' in sys.argv else ['mandatory','bonus']):
    suffix='_bonus' if mode=='bonus' else ''
    sources=common+['src/loader/parser_line'+suffix+'.c','src/loader/parser_light'+suffix+'.c','src/renderer/renderer_intersection'+suffix+'.c']
    if mode=='bonus': sources+=['src/loader/parser_hyperboloid_bonus.c','src/renderer/renderer_hyperboloid_bonus.c']
    for san in [False,True]:
        tag='app_'+mode+('_san' if san else '_debug'); binary=OUT/tag
        cmd=['gcc','-Wall','-Wextra','-Werror','-O1','-g','-Iinclude','-Ilib/libft','-Ilib/mlx_linux']+sources+libs+['lib/mlx_linux/libmlx.a','-lXext','-lX11','-lm','-lz','-o',str(binary)]
        if san: cmd+=['-fsanitize=address,undefined,float-cast-overflow','-fno-sanitize-recover=all']
        subprocess.run(cmd,check=True)
        cases=[('no_args',[]),('extra_args',['x.rt','y.rt']),('missing',['/tmp/minirt-stress/missing.rt']),('wrong_extension',['Makefile']),('directory',[str(OUT/'corpus/directory.rt')]),('empty',[str(OUT/'corpus/empty.rt')]),('bad_number',[str(OUT/'corpus/long_number.rt')]),('nul',[str(OUT/'corpus/nul_hidden_suffix.rt')]),('no_display',[str(OUT/'corpus/valid.rt')])]
        for name,args in cases:
            prefix=[] if san else ['valgrind','--track-origins=yes','--leak-check=full','--show-leak-kinds=all','--errors-for-leak-kinds=all','--error-exitcode=97','--log-file='+str(OUT/(tag+'_'+name+'_valgrind.log'))]
            r=subprocess.run(prefix+[str(binary)]+args,capture_output=True,env={**ENV,'DISPLAY':':9876'},timeout=20)
            (OUT/(tag+'_'+name+'.log')).write_bytes(r.stdout+r.stderr)
            passed=r.returncode==1 and b'Error\n' in r.stdout+r.stderr
            results.append({'name':tag+'_'+name,'exit':r.returncode,'pass':passed})
        print(tag,'CLI complete',flush=True)
if '--gui' in sys.argv or '--only-gui' in sys.argv or '--fullscreen-only' in sys.argv:
    subprocess.run(['gcc','-Wall','-Wextra','-Werror','-g','tests/gui_driver.c','-lX11','-o',str(OUT/'gui_driver')],check=True)
    configs=[('mandatory_san','exercise','scenes/example.rt'),('bonus_san','exercise','hyperboloid_bonus.rt'),('mandatory_debug','close','scenes/example.rt'),('bonus_debug','close','hyperboloid_bonus.rt'),('bonus_san','escape','multiple_lights_bonus.rt'),('mandatory_debug','fullscreen','tests/fullscreen.rt'),('bonus_debug','fullscreen_close','tests/fullscreen.rt')]
    if '--fullscreen-only' in sys.argv:
        configs=[c for c in configs if c[1].startswith('fullscreen')]
    for mode,action,scene in configs:
        tag='gui_'+mode+'_'+action
        prefix=[] if mode.endswith('_san') else ['valgrind','--track-origins=yes','--leak-check=full','--show-leak-kinds=all','--errors-for-leak-kinds=all','--error-exitcode=97','--log-file='+str(OUT/(tag+'_valgrind.log'))]
        cmd=[str(OUT/'gui_driver'),action,str(OUT/(tag+'.ppm'))]+prefix+[str(OUT/('app_'+mode)),scene]
        with (OUT/(tag+'.log')).open('w') as log:
            p=subprocess.Popen(cmd,stdout=log,stderr=log,env=ENV,start_new_session=True)
            try: code=p.wait(timeout=900)
            except subprocess.TimeoutExpired:
                os.killpg(p.pid,signal.SIGTERM); p.wait();code=124
        results.append({'name':tag,'exit':code,'pass':code==0})
        print(tag,'exit',code,flush=True)
if ('--only-gui' in sys.argv or '--fullscreen-only' in sys.argv) and (OUT/'app_summary.json').exists():
    previous=json.loads((OUT/'app_summary.json').read_text())
    names={r['name'] for r in results}
    results=[r for r in previous if r['name'] not in names]+results
(OUT/'app_summary.json').write_text(json.dumps(results,indent=2))
print('PASS:',sum(r['pass'] for r in results),'/',len(results),flush=True)
sys.exit(0 if all(r['pass'] for r in results) else 1)
