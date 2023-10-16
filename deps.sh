#
#   module  : deps.sh
#   version : 1.4
#   date    : 10/16/23
#
#   Generate deps.h
#   The directory needs to be given as parameter.
#
echo checking deps.h
todo=0
if [ ! -f $1/deps.h ]
then
  echo creating deps.h
  todo=1
else
  for i in $1/src/*.c
  do
    if [ $i -nt $1/deps.h ]
    then
      echo updating deps.h
      todo=1
      break
    fi
  done
fi
if [ $todo -eq 0 ]
then
  echo deps.h is up-to-date
  exit
fi
rm -f $1/deps.h
for i in $1/src/*.c
do
  j=`basename $i`
  j=`echo $j | tr '[a-z]' '[A-Z]' | sed 's/\./_/'`
  k=`grep "[^e]code(" $i | sed 's/.*code(env, \(.*\));/\1C/'`
  l=`grep "_(env);" $i | sed 's/[ \t]*\(.*\)(env);/\1C/'`
  done=0
  if [ "$k" != "" ]
  then
    echo "#ifndef $j"
    done=1
  fi
  if [ $done -eq 0 ]
  then
    if [ "$l" != "" ]
    then
      echo "#ifndef $j"
      done=1
    fi
  fi
  if [ "$k" != "" ]
  then
    echo "$k" | tr '[a-z]' '[A-Z]' | sed 's/^/#undef /'
  fi
  if [ "$l" != "" ]
  then
    echo "$l" | tr '[a-z]' '[A-Z]' | sed 's/^/#undef /'
  fi
  if [ $done -eq 1 ]
  then
    echo "#endif"
  fi
done >$1/deps.h
for i in $1/*.c
do
  k=`grep "[^e]code(env" $i | sed 's/.*code(env, \(.*\));/\1C/'`
  l=`grep "_(env);" $i | sed 's/[ \t]*\(.*\)(env);/\1C/'`
  if [ "$k" != "" ]
  then
    echo "$k" | tr '[a-z]' '[A-Z]' | sed 's/^/#undef /'
  fi
  if [ "$l" != "" ]
  then
    echo "$l" | tr '[a-z]' '[A-Z]' | sed 's/^/#undef /'
  fi
done >>$1/deps.h
