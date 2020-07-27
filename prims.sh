#
#   module  : prims.sh
#   version : 1.1
#   date    : 07/23/20
#
#   Generate runtime.c and builtin.h
#
echo checking runtime.c and builtin.h
todo=0
ls -1Q src/*.c | sed 's/^/#include /' >prims.tmp
if [ ! -f runtime.c -o ! -f builtin.h ]
then
  echo creating runtime.c and builtin.h
  todo=1
else
  diff runtime.c prims.tmp
  if [ $? -eq 0 ]
  then
    echo runtime.c and builtin.h are up-to-date
    rm prims.tmp
  else
    echo updating runtime.c and builtin.h
    todo=1
    rm -f trans.c table.c
  fi
fi
if [ $todo -eq 1 ]
then
  rm -f runtime.c builtin.h
  mv prims.tmp runtime.c
  sed 's/.*\//void do_/;s/\..*/(void);/' <runtime.c | sed 's/void do_pop(/intptr_t do_pop(/' >builtin.h
fi
