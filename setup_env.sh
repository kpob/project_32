#!/bin/bash

if [ "$#" -lt 3 ]; 
then
	echo "Nieprawidłowe użycie. Składnia:"
	echo "$0  file/gdb pepper_version nazwa_projektu"
	echo "Na przykład $0 23 project_32"
else
	NACL_ROOT="$HOME/nacl_sdk/pepper_$2/examples"

	if [ -d "$NACL_ROOT" ];
	then
		LAST_LOC=$PWD
		cd $NACL_ROOT
		x-terminal-emulator -e "python httpd.py"
		cd $LAST_LOC

		export NACL_EXE_STDOUT="$HOME/nacl_stdout.log"
		export NACL_EXE_STDERR="$HOME/nacl_stderr.log"
		if [ "$1" = "file" ];
		then
			echo "file"
			google-chrome --incognito --enable-nacl --no-sandbox localhost:5103/$3
		elif [ "$1" = "gdb" ];
		then
			echo "gdb"
			google-chrome --incognito --enable-nacl --enable-nacl-debug --no-sandbox localhost:5103/$3
		else
			echo "nieznana opcja"
		fi
	else
		echo "Nie można odnaleźć folderu $NACL_ROOT. Sprawdź położenie nacl_sdk"
	fi
fi
