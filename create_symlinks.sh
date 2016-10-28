#!/bin/bash
#
# create_symlinks.sh: Code in the 'common' directory will be used by all
# the sample apps. In order to avoid tracking duplicated code for each sample,
# this script is provided to create symlinks for each subdirectory under
# 'common' inside the 'src' directory of each sample app. This allows each
# sample app to compile with all required sources under the 'src' directory,
# as is required by Zephyr/Kbuild.

base=$(pwd)
top="common"
services="arduino101_services"
arduino="arduino"

# Important to use absolute paths for link sources
services_path="$base"/"$top"/"$services"
arduino_path="$base"/"$top"/"$arduino"

for d in */
do
    if [ "$d" == "$top" ] || [ ! -d "$d"/src ]
    then
        continue
    fi

    service_link="$base"/"$d"/src/"$services"
    arduino_link="$base"/"$d"/src/"$arduino"

    [ -L "$service_link" ] || ln -s "$services_path" "$service_link"
    [ -L "$arduino_link" ] || ln -s "$arduino_path" "$arduino_link"
done

ln -s "$services_path" "$arduino_path"
