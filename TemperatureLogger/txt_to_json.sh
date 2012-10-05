#!/bin/sh


INFILE=TEMPLOG.TXT

LINES=`wc -l ${INFILE} | awk '{print $1}'`

echo "{"
echo "  \"temperatures\": ["

i=0
for t in `cat ${INFILE} | sed 's/\r/\n/g' | awk '{print $1}'`
do
  
  echo -n "    [${i}, ${t}]"
  
  i=`expr $i + 1`
  
  if [ $i -lt $LINES ]
  then
    echo -n ','
  fi
  
  echo
  
done

echo "  ]"
echo "}"
