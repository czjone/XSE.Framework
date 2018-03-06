#!/bin/bash

### configs
buildRoot="build"
shellRoot=$(cd `dirname $0`; pwd)

# @usage: initEnv()
# @args: no args.
initEnv() {
  # 1、create build root.
  # 2、switch to build root.
  shellRoot=$(cd `dirname $0`; pwd)
  cd $shellRoot
  if [ ! -d ${buildRoot} ]; then
    mkdir ${buildRoot}
  # else
  #   rm -rf ${buildRoot}
  #    mkdir ${buildRoot}
  fi

  #swith to build root.
  cd $buildRoot
}

cmakeBuild() {
  if [ $2 == "clean" ]; then
    cd ${shellRoot}/$buildRoot
    if [ -d $1 ]; then
      rm -rf $1
    fi
  fi

  if [[ $2 == "build" ]]; then
    mkdir ${shellRoot}/$buildRoot/$1
    cd ${shellRoot}/$buildRoot/$1
    cmake ../../$1
    make  
  fi
}

################# start build BLL ############
# $1= fnode,$2=build|clean,$3=debug|release
initEnv
cmakeBuild $1 $2 $3