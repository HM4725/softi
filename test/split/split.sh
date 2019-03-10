#!/bin/bash
split -b 1000 hello_world spfiles_
cat spfiles_* > hw_recovery
chmod 744 hw_recovery
rm spfiles_*
./hw_recovery
