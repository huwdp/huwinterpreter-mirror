#!/bin/bash
make -C ../build-HuwInterpreter-Desktop-Release/
cp ../build-HuwInterpreter-Desktop-Release/HuwInterpreter huwcode/bin/huwcode
./linuxdeployqt-continuous-x86_64.AppImage huwcode/share/applications/huwcode.desktop -bundle-non-qt-libs
#mv dist.AppImage huwcode-linux-x86_64.AppImage
#export HuwCode=huwcode-linux-x86_64.AppImage
dt=`date '+%d%m%Y%H%M%S'`
mv AppRun "releases/huwcode$dt"
