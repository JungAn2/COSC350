#!/bin/sh

read number

for i in $(seq 1 to 10); do
  echo -n "$number"
done
exit 0
