#!/bin/bash

rm   -f client.o id_validation.o reg_user_validation.o svc_reg_validation.o validation_ser_reg.o get_svc_list_validation.o subscribe_validation.o  libuid.a client 
gcc -c client.c
gcc -c id_validation.c reg_user_validation.c svc_reg_validation.c validation_ser_reg.c get_svc_list_validation.c subscribe_validation.c 
ar rs libuid.a id_validation.o reg_user_validation.o svc_reg_validation.o validation_ser_reg.o get_svc_list_validation.o subscribe_validation.o 
gcc -o client -L. client.o -luid

