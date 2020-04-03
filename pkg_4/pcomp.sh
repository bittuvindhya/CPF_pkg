#!/bin/bash
rm  -f provider1.o svc_provider.o cpf_provider.o svc_reg_validation.o libprovider.a prov sample.o
gcc -c provider1.c 
gcc -c svc_reg_validation.c sample.c svc_provider.c cpf_provider.c
ar rs libprovider.a svc_reg_validation.o sample.o svc_provider.o cpf_provider.o
gcc -o prov -L. provider1.o -lprovider -ldl -lpthread


 #gcc -c svc_reg_validation.o
 #ar rc libprovider.a svc_reg_validation.o
 #gcc -Wall provider1.c libprovider.a -o pro -ldl
