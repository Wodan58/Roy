#
#   module  : prims.sh
#   version : 1.2
#   date    : 04/27/21
#
#   Generate runtime.c and builtin.h
#
echo checking runtime.c and builtin.h
todo=0
ls -1Q src/*.c gui/*.c | sed 's/^/#include /' >prims.tmp
if [ ! -f runtime.c -o ! -f builtin.h ]
then
  echo creating runtime.c and builtin.h
  todo=1
else
  diff prims.tmp runtime.c
  if [ $? -eq 0 ]
  then
    echo runtime.c and builtin.h are up-to-date
    rm prims.tmp
  else
    echo updating runtime.c and builtin.h
    todo=1
  fi
fi
if [ $todo -eq 1 ]
then
  rm -f runtime.c builtin.h
  mv prims.tmp runtime.c
  sed 's/.*\//void do_/;s/\..*/(void);/' <runtime.c | sed 's/void do_pop(/intptr_t do_pop(/' >builtin.h
fi
