#!/usr/bin/env python3
"""Repeatable headless stress tests. Outputs/builds live in /tmp/minirt-stress."""
import json, os, random, subprocess, sys
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
os.chdir(ROOT)
OUT=Path(os.environ.get('MINIRT_TEST_OUT','/tmp/minirt-stress')); OUT.mkdir(exist_ok=True)
CORPUS=OUT/'corpus'; CORPUS.mkdir(exist_ok=True)
BASE=['A 0.2 255,255,255','C 0,0,-10 0,0,1 60','L -3,5,-5 0.7 255,255,255','sp 0,0,5 2 255,255,255']
cases=[]
def case(name,body,mandatory,bonus=None):
    path=CORPUS/(name+'.rt'); path.write_bytes(body.encode() if isinstance(body,str) else body)
    cases.append((path,mandatory,mandatory if bonus is None else bonus))
def change(name,index,line,expected=False,bonus=None):
    lines=BASE.copy(); lines[index]=line; case(name,'\n'.join(lines)+'\n',expected,bonus)
case('valid','\n'.join(BASE)+'\n',True)
case('no_newline','\n'.join(BASE),True)
case('crlf','\r\n'.join(BASE)+'\r\n',True)
case('whitespace',' \t\n'+'\n\n'.join('  '+s.replace(' ','\t')+'  ' for s in BASE),True)
case('reordered','\n'.join(reversed(BASE)),True)
case('empty','',False)
for i in range(4): case('missing_'+str(i),'\n'.join(BASE[:i]+BASE[i+1:]),False)
for i in range(3): case('duplicate_'+str(i),'\n'.join(BASE+[BASE[i]]),False,i==2)
for kind in ['sp','cy','hy']:
    shape=kind+' 0,0,5 '+('' if kind=='sp' else '0,1,0 ')
    for value in ['0','-1','-0','0.0']:
        change(kind+'_dimension_'+value,3,shape+value+('' if kind=='sp' else ' 2')+' 255,255,255')
    if kind!='sp': change(kind+'_zero_height',3,shape+'2 0 255,255,255')
    change(kind+'_valid',3,shape+'2'+('' if kind=='sp' else ' 4')+' 255,255,255',kind!='hy',True)
change('plane',3,'pl 0,0,5 0,1,0 255,255,255',True)
for index in range(4):
    change('trailing_'+str(index),index,BASE[index]+' junk')
    change('joined_id_'+str(index),index,BASE[index].replace(' ','',1))
    for cut in range(len(BASE[index])): change(f'truncated_{index}_{cut}',index,BASE[index][:cut],None)
for token in ['nan','inf','-inf','1e309','1e2','--1','+','-','.','1..0','0x10','9'*400,'2147483648','-2147483649']:
    name=str(len(cases))
    change('fov_'+name,1,'C 0,0,-10 0,0,1 '+token)
    change('color_'+name,0,'A 0.2 '+token+',255,255')
    change('ratio_'+name,0,'A '+token+' 255,255,255')
for axis in ['0,0,0','1,1,1','2,0,0','0,0','0,,1','1 0 0']:
    change('axis_'+str(len(cases)),1,'C 0,0,-10 '+axis+' 60')
for fov in ['-1','181']: change('fov_range_'+fov,1,'C 0,0,-10 0,0,1 '+fov)
for fov in ['0','180']: change('fov_boundary_'+fov,1,'C 0,0,-10 0,0,1 '+fov,True)
for ratio in ['0','1']: change('ratio_boundary_'+ratio,0,'A '+ratio+' 0,255,0',True)
for color in ['-1,0,0','256,0,0','0,0','0,,0','0,0,0,0']: change('color_range_'+str(len(cases)),0,'A 0.2 '+color)
for idx in [0,5,30]:
    body='\n'.join(BASE).encode(); case('nul_'+str(idx),body[:idx]+b'\0'+body[idx:],False)
case('nul_hidden_suffix','\n'.join(BASE).encode()+b'\0BAD',False)
case('long_whitespace',' '*100000+'\n'+'\n'.join(BASE),True)
case('long_number','A '+'9'*100000+' 255,255,255\n'+'\n'.join(BASE[1:]),False)
case('many_shapes','\n'.join(BASE+[BASE[3]]*1500),True)
case('many_lights','\n'.join(BASE+[BASE[2]]*1000),False,True)
# Render a broad set of valid mixed scenes and numerical extremes.
for i in range(60):
    axis=['0,1,0','0,0,1','1,0,0','0.6,0.8,0'][i%4]
    shape=['sp','cy','pl','hy'][i%4]
    position=f'{i%7-3},{i%3-1},{4+i%8}'
    line=shape+' '+position+' '+('' if shape=='sp' else axis+' ')
    if shape!='pl': line+=str(1+i%4)+' '+('' if shape=='sp' else str(2+i%5)+' ')
    line+=f'{80+i*2},180,210'
    change(f'generated_{i:02d}',3,line,shape!='hy',True)
for exp in [20,75,150,155,200,300,-20,-75,-150,-155,-200,-300]:
    number=('1'+'0'*exp) if exp>=0 else ('0.'+'0'*(-exp-1)+'1')
    for kind in ['sp','cy','hy']:
        change(f'extreme_{kind}_{exp}',3,kind+' 0,0,5 '+('' if kind=='sp' else '0,1,0 ')+number+('' if kind=='sp' else ' '+number)+' 255,255,255',kind!='hy',True)
case('allocation_mix','\n'.join(BASE+[BASE[3]]*25),True)
(CORPUS/'directory.rt').mkdir(exist_ok=True)
cases.append((CORPUS/'directory.rt',False,False))
cases.append((CORPUS/'missing.rt',False,False))
wrong=CORPUS/'wrong.txt'; wrong.write_text('\n'.join(BASE)); cases.append((wrong,False,False))
random.seed(420)
for i in range(2500):
    body=bytearray(('\n'.join(BASE)+'\n').encode())
    for _ in range(random.randint(1,8)):
        pos=random.randrange(len(body)); op=random.randrange(3)
        if op==0: body[pos]=random.randrange(256)
        elif op==1: del body[pos]
        else: body[pos:pos]=bytes([random.randrange(256)])
    case(f'fuzz_{i:04d}',body,None)
common=[str(p) for d in ['src/loader','src/math','src/renderer'] for p in Path(d).glob('*.c') if not p.name.endswith('_bonus.c') and p.name not in ['parser_line.c','parser_light.c','renderer_intersection.c']]+['src/scene/scene.c','src/scene/camera.c','src/linkedlist/linkedlist.c','src/color.c']
libft=[str(p) for p in Path('lib/libft').glob('*.c')]
def build(mode,san):
    suffix='_bonus' if mode=='bonus' else ''
    sources=common+['src/loader/parser_line'+suffix+'.c','src/loader/parser_light'+suffix+'.c','src/renderer/renderer_intersection'+suffix+'.c']
    if mode=='bonus': sources+=['src/loader/parser_hyperboloid_bonus.c','src/renderer/renderer_hyperboloid_bonus.c']
    binary=OUT/(mode+('_san' if san else '_debug'))
    cmd=['gcc','-Wall','-Wextra','-Werror','-g','-O1','-Iinclude','-Ilib/libft','-Isrc/loader','-Isrc/renderer','tests/stress_harness.c']+sources+libft+['-Wl,--wrap=malloc','-lm','-o',str(binary)]
    if mode=='bonus': cmd+=['-DBONUS']
    if san: cmd+=['-fsanitize=address,undefined,float-cast-overflow','-fno-sanitize-recover=all','-fno-omit-frame-pointer']
    subprocess.run(cmd,check=True)
    return binary
ENV={**os.environ,'ASAN_OPTIONS':'detect_leaks=0:halt_on_error=1'}
summary={'cases_per_build':len(cases),'runs':[]}
for mode in ['mandatory','bonus']:
    for san in [True,False]:
        binary=build(mode,san); tag=binary.name
        prefix=[] if san else ['valgrind','--leak-check=full','--show-leak-kinds=all','--errors-for-leak-kinds=all','--error-exitcode=97','--log-file='+str(OUT/(tag+'_valgrind.log'))]
        with (OUT/(tag+'_stderr.log')).open('w') as err:
            result=subprocess.run(prefix+[str(binary)]+[str(c[0]) for c in cases],stdout=subprocess.PIPE,stderr=err,text=True,env=ENV,timeout=180)
        (OUT/(tag+'_stdout.log')).write_text(result.stdout)
        actual={p:int(ok) for line in result.stdout.splitlines() if '\t' in line for ok,p in [line.split('\t',1)]}
        mismatches=[{'case':p.name,'expected':exp,'actual':actual.get(str(p))} for p,m,b in cases for exp in [b if mode=='bonus' else m] if exp is not None and actual.get(str(p))!=exp]
        entry={'build':tag,'exit':result.returncode,'completed':len(actual),'mismatches':mismatches}; summary['runs'].append(entry)
        print(json.dumps({k:v for k,v in entry.items() if k!='mismatches'}), 'mismatches:',len(mismatches),flush=True)
        for command in [['geometry'],['alloc',str(CORPUS/'valid.rt')],['alloc',str(CORPUS/'allocation_mix.rt')]]+([['alloc',str(ROOT/'hyperboloid_bonus.rt')]] if mode=='bonus' else []):
            logtag=tag+'_'+command[0]+('_'+Path(command[-1]).stem if command[0]=='alloc' else '')
            pp=[] if san else prefix[:-1]+['--log-file='+str(OUT/(logtag+'_valgrind.log'))]
            with (OUT/(logtag+'.log')).open('w') as log:
                r=subprocess.run(pp+[str(binary)]+command,stdout=log,stderr=log,env=ENV,timeout=120)
            entry[logtag]=r.returncode
            print(logtag, r.returncode,flush=True)
(OUT/'summary.json').write_text(json.dumps(summary,indent=2))
print('Results:',OUT)
if any(r['exit'] or r['mismatches'] or any(v for k,v in r.items() if k.startswith(r['build']+'_')) for r in summary['runs']):
    sys.exit(1)
