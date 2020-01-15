# Garfield++

---
User’s guideを見ればだいたい分かる

---
高田さんの講習会

Url：[Garfield++ lecture session home page](http://ppwww.phys.sci.kobe-u.ac.jp/~upic/garfield/)

GmshとElmerを用いた解析

---
* FEMTETを用いた解析

ExcelでFEMTETの電圧と電流の出力を出せる。

Componentをvoxelに変換

---
## How to code

---
### Gmsh
```Gmsh
$ cd Gmsh
$ . runElmer.sh
$ cd src
$ make
$ cd ..
$ ./ViewFLD
$ root wire_e_field.root
[0] .ls
TFile**   y0.root	
 TFile**  y0.root	
  KEY: TH2F E_hist;1  wire_e_field
  KEY: TH2F V_hist;1
[1]V_hist->Draw("cont1")
```
rootが起動して、等電位線が表示される。

---
### FEMTET

FEMTETでGeometryを作成し、電場計算を行う
その電位と電場の情報を位置ごとにcsvに出力できる。
そのcsvファイルをdatファイルに変換することでGarfiled++に導入できる。
```
$ cd FEMTET/src
$ make
$ cd ..
$ ./ViewFLD
$ root wire_e_field.root
[0] .ls
TFile**		y0.root	
 TFile*		y0.root	
  KEY: TH2F	E_hist;1	wire_e_field
  KEY: TH2F	V_hist;1
[1]V_hist->Draw("cont1")
```
rootが起動して、等電位線が表示される。






