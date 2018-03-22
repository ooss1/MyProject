#!/bin/bash

#gcc -I/root/parson-master/ main.c parson.c -o main
#./main
#mv ./example.json /root/share

i=1
while [ $i -lt 5 ] 
do 
#	cp ./example.json /root/share
#	cp /nfsroot/root/example.json /root/share
	cp ./example.json /home/student/final_share
	sleep 10
done
