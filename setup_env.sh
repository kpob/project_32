#!/bin/bash
function run {
	if [ -d "$NACL_ROOT" ];
	then
		cd $NACL_ROOT/examples
		x-terminal-emulator -e "python httpd.py"
		cd $OLDPWD
		export NACL_EXE_STDOUT="$HOME/nacl_stdout.log"
		export NACL_EXE_STDERR="$HOME/nacl_stderr.log"
		if [ "$1" = "file" ];
		then
			google-chrome --incognito --enable-nacl --no-sandbox localhost:5103/$2
		elif [ "$1" = "gdb" ];
		then
			google-chrome --incognito --enable-nacl --enable-nacl-debug --no-sandbox localhost:5103/$2
		else
			echo "nieznana opcja"
		fi
	else
		echo "Nie można odnaleźć folderu $NACL_ROOT. Sprawdź położenie nacl_sdk"
	fi
} 


if [ "$#" -lt 2 ]; 
then
	echo "Nieprawidłowe użycie. Składnia:"
	echo ". setup_env file/gdb nazwa_projektu"
	echo "Na przykład . setup_env project_32"
else
	if [ "${#NACL_ROOT}" -gt 0 ] ;
	then
		run $1 $2
	else
		echo "Brak NACL_ROOT. Podaj ścieżkę"
		read NACL_ROOT
		cd $HOME
		echo "export NACL_ROOT=$NACL_ROOT" >> .bashrc
		source .bashrc 
		cd $OLDPWD
		run $1 $2
	fi
fi
