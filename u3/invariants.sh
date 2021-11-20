#!/bin/bash
echo "Space invariant"

cat $1 | grep ' ' -o | wc -l && cat $2 | grep ' ' -o | wc -l

echo "-------"
echo "Line invariant"

cat $1 | wc -l && cat $2 | wc -l
