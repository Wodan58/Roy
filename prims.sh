#
#   module  : prims.sh
#   version : 1.3
#   date    : 06/21/22
#
#   Generate runtime.c and builtin.h
#   The directory needs to be given as parameter.
#
echo checking runtime.c and builtin.h
todo=0
ls -1Q $1/src/*.c | sed 's/^/#include /' >prims.tmp
if [ ! -f $1/runtime.c -o ! -f $1/builtin.h ]
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
  rm -f $1/runtime.c $1/builtin.h
  mv prims.tmp $1/runtime.c
  sed 's/.*\//void do_/;s/\..*/(void);/' <$1/runtime.c | sed -f $1/table.sed >$1/builtin.h
  touch $1/builtin.c
fi
