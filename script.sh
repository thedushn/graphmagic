#!/bin/bash

cp *.c makefile_folder/project/client/src
cp *.h makefile_folder/project/client/include
cp ./Client\ /*.h makefile_folder/project/server/include/
cp ./Client\ /*.c makefile_folder/project/server/src/
cp *.c /home/dushn/forthelove/project/client/src/
cp *.h /home/dushn/forthelove/project/client/include/

cp ./Client\ /*.c /home/dushn/forthelove/project/server/src/
cp ./Client\ /*.h /home/dushn/forthelove/project/server/include/
echo we did it !!!
