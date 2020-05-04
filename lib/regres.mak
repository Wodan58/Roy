#
#   module  : regres.mak
#   version : 1.2
#   date    : 03/06/20
#
regres: fib2 gcd2 test2 jp-joytst2 flatjoy2 jp-reprodtst2 modtst2 jp-nestrec2 laztst2 joytut2 jp-church2 grmtst2 mtrtst2 reptst2 tutorial2 symtst2 plgtst2 lsptst2

fib2:
	@echo fib
	-../joy fib.joy | diff -w - OUT/fib.out

gcd2:
	@echo gcd
	-../joy gcd.joy 24 54 | diff -w - OUT/gcd.out

test2:
	@echo test1
	-../joy test1.joy | diff -w - OUT/test1.out

jp-joytst2:
	@echo jp-joytst
	-../joy jp-joytst.joy | diff -w - OUT/jp-joytst.out

flatjoy2:
	@echo flatjoy
	-../joy flatjoy.joy | diff -w - OUT/flatjoy.out

jp-reprodtst2:
	@echo jp-reprodtst
	-../joy jp-reprodtst.joy | diff -w - OUT/jp-reprodtst.out

modtst2:
	@echo modtst
	-../joy modtst.joy | diff -w - OUT/modtst.out

jp-nestrec2:
	@echo jp-nestrec
	-../joy jp-nestrec.joy | diff -w - OUT/jp-nestrec.out

laztst2:
	@echo laztst
	-../joy laztst.joy | diff -w - OUT/laztst.out

joytut2:
	@echo joytut
	-../joy joytut.joy | diff -w - OUT/joytut.out

jp-church2:
	@echo jp-church
	-../joy jp-church.joy | diff -w - OUT/jp-church.out

grmtst2:
	@echo grmtst
	-../joy grmtst.joy | diff -w - OUT/grmtst.out

mtrtst2:
	@echo mtrtst
	-../joy mtrtst.joy | diff -w - OUT/mtrtst.out

reptst2:
	@echo reptst
	-../joy reptst.joy | diff -w - OUT/reptst.out

tutorial2:
	@echo tutorial
	-../joy tutorial.joy | diff -w - OUT/tutorial.out

symtst2:
	@echo symtst
	-../joy symtst.joy | diff -w - OUT/symtst.out

plgtst2:
	@echo plgtst
	-../joy plgtst.joy | diff -w - OUT/plgtst.out

lsptst2:
	@echo lsptst
	-../joy lsptst.joy | diff -w - OUT/lsptst.out
