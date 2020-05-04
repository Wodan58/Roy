#
#   module  : regres2.mak
#   version : 1.2
#   date    : 03/06/20
#
regres: fib2 gcd2 test2 jp-joytst2 flatjoy2 jp-reprodtst2 modtst2 jp-nestrec2 laztst2 jp-church2 grmtst2 mtrtst2 reptst2 tutorial2 symtst2 plgtst2

fib2:
	@echo fib
	-./fib | diff -w - OUT/fib.out

gcd2:
	@echo gcd
	-./gcd 24 54 | diff -w - OUT/gcd.out

test2:
	@echo test1
	-./test1 | diff -w - OUT/test1.out

jp-joytst2:
	@echo jp-joytst
	-./jp-joytst | diff -w - OUT/jp-joytst.out

flatjoy2:
	@echo flatjoy
	-./flatjoy | diff -w - OUT/flatjoy.out

jp-reprodtst2:
	@echo jp-reprodtst
	-./jp-reprodtst | diff -w - OUT/jp-reprodtst.out

modtst2:
	@echo modtst
	-./modtst | diff -w - OUT/modtst.out

jp-nestrec2:
	@echo jp-nestrec
	-./jp-nestrec | diff -w - OUT/jp-nestrec.out

laztst2:
	@echo laztst
	-./laztst | diff -w - OUT/laztst.out

joytut2:
	@echo joytut
	-./joytut <joytut.inp | diff -w - OUT/joytut.out

jp-church2:
	@echo jp-church
	-./jp-church | diff -w - OUT/jp-church.out

grmtst2:
	@echo grmtst
	-./grmtst | diff -w - OUT/grmtst.out

mtrtst2:
	@echo mtrtst
	-./mtrtst | diff -w - OUT/mtrtst.out

reptst2:
	@echo reptst
	./reptst | diff -w - OUT/reptst.out

tutorial2:
	@echo tutorial
	-./tutorial <tutorial.inp | diff -w - OUT/tutorial.out

symtst2:
	@echo symtst
	-./symtst | diff -w - OUT/symtst.out

plgtst2:
	@echo plgtst
	-./plgtst | diff -w - OUT/plgtst.out

lsptst2:
	@echo lsptst
	-./lsptst <lsptst.inp | diff -w - OUT/lsptst.out
