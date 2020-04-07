#!/bin/bash

rm   -f client_1.o id_validation.o reg_user_validation.o svc_reg_validation.o validation_ser_reg.o get_svc_list_validation.o subscribe_validation.o start_session_validation.o libuid.a client configfile.o service_interpret.o 
gcc -c client_1.c
gcc -c id_validation.c reg_user_validation.c svc_reg_validation.c validation_ser_reg.c get_svc_list_validation.c subscribe_validation.c start_session_validation.c configfile.c service_interpret.c 
ar rs libuid.a id_validation.o reg_user_validation.o svc_reg_validation.o validation_ser_reg.o get_svc_list_validation.o subscribe_validation.o start_session_validation.o configfile.o service_interpret.o 
gcc -o client -L. client_1.o -luid

