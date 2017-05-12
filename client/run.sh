#! /bin/bash

if [ -z "$BRANCH" ]; then
	BRANCH="rework_light"
fi

if [ -z "$PORT" ]; then
	PORT="4242"
fi

RTDIR="rt-$BRANCH"
CLDIR="cl"
GIT="http://github.com/lgatibel/42_rt.git"

if [ -d "$RTDIR/.git" ]; then
	cd "$RTDIR"
	git pull
	cd ..
else
	git clone -b "$BRANCH" "$GIT" "$RTDIR"
fi

if [ -d "$CLDIR" ]; then
	rm -rf "$CLDIR"
	mkdir "$CLDIR"
else
	mkdir "$CLDIR"
fi

echo Copying all cl files from "$RTDIR" to "$CLDIR"
find "$RTDIR/sources/cl" -print -exec cp {} "$CLDIR" \;
echo OK

sed -i '' 's/\.\.\/include\///' cl/obj_def.h
