#
#   module  : defs.sh
#   version : 1.1
#   date    : 09/11/23
#
#   Generate defs.h
#   The directory needs to be given as parameter.
#
echo checking defs.h
todo=0
if [ ! -f $1/defs.h ]
then
  echo creating defs.h
  todo=1
else
  for i in $1/src/*.c
  do
    if [ $i -nt $1/defs.h ]
    then
      echo updating defs.h
      todo=1
      break
    fi
  done
fi
if [ $todo -eq 0 ]
then
  echo defs.h is up-to-date
  exit
fi
rm -f $1/defs.h
for i in $1/src/*.c
do
  j=`basename $i`
  j=`echo $j | tr '[a-z]' '[A-Z]' | sed 's/\./_/'`
  echo "#define $j"
done >$1/defs.h
