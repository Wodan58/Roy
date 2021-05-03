#
#   module  : trans.sh
#   version : 1.3
#   date    : 04/27/21
#
#   Generate trans.c
#
echo checking trans.c
todo=0
if [ ! -f trans.c ]
then
  echo creating trans.c
  todo=1
else
  for i in src/*.c gui/*.c
  do
    if [ $i -nt trans.c ]
    then
      echo updating trans.c
      todo=1
      break
    fi
  done
fi
if [ $todo -eq 0 ]
then
  echo trans.c is up-to-date
  exit
fi
rm -f trans.c
for i in src/*.c gui/*.c
do
  file=`basename $i`
  name=`expr $file : '\(.*\)\.c'`
  sed -n '/\/\*\*/ {
	N
	s/.*\n\(^[^ ]*\).*/enter("\1", do_'$name');\n/
	P
  }' <$i
done | sort | sed 's/do_pop)/(void (*)(void))do_pop)/' >trans.c
