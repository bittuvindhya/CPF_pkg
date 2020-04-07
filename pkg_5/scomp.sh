#!/bin/bash

rm   -f ci.o uim.o uid_exist.o server_new.o service_exist.o request_validation.o itoa.o svc_field.o cpf_provider.o backup_svcreg.o uid_retrive.o sseek.o get_svc_list.o  subscribe.o id_validation.o start_session.o session_retrive.o  server libuim.a  
gcc -c server_new.c
gcc -c ci.c uim.c uid_exist.c itoa.c svc_field.c backup_svcreg.c service_exist.c request_validation.c uid_retrive.c cpf_provider.c sseek.c get_svc_list.c subscribe.c id_validation.c start_session.c session_retrive.c
ar rs libuim.a ci.o uim.o itoa.o uid_exist.o  backup_svcreg.o svc_field.o uid_retrive.o service_exist.o sseek.o get_svc_list.o cpf_provider.o request_validation.o subscribe.o id_validation.o start_session.o session_retrive.o 
gcc -o server -L. server_new.o -luim -lpthread -ldl

