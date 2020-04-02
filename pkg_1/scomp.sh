#!/bin/bash

rm   -f ci.o uim.o server.o itoa.o backup_svcreg.o uid_retrive.o sseek.o get_svc_list.o  subscribe.o id_validation.o start_session.o session_retrive.o  server libuim.a  
gcc -c server_new.c
gcc -c ci.c uim.c itoa.c backup_svcreg.c uid_retrive.c sseek.c get_svc_list.c subscribe.c id_validation.c  session_retrive.c
ar rs libuim.a ci.o uim.o itoa.o backup_svcreg.o uid_retrive.o sseek.o get_svc_list.o subscribe.o id_validation.o session_retrive.o
gcc -o server -L. server_new.o -luim -lpthread

