 gcc -c email.c svc_reg.c
 ar rc libvalidation.a email.o svc_reg.o
 gcc -Wall validation_ser_reg.c libvalidation.a -o valid

