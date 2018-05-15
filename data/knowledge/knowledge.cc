INM1 attribute@xmlFile@name main.xml peppher:component peppher:implementation peppher:requiredInterfaces
IN1 attribute@name peppher:component peppher:interface
INFM1 attribute@xmlFile peppher:component peppher:implementation peppher:requiredInterfaces
IPL1 params attribute@type@name peppher:component peppher:interface peppher:parameters
ROPD1 peppher:component peppher:interface peppher:parameters
IMNP1 attribute@name peppher:component peppher:implementation
IMD1 attribute@disable peppher:component peppher:implementation
IMNWP1 add $IMNP1 _wrapper
IMND1 attribute@name peppher:component peppher:implementation
IMNWD1 add $IMND1 _wrapper
INW2  add $IN1 _wrapper
INWC2 cap $INW2
ROCN2 add readOnlyArgs_ $IN1
ROCNR2 add $ROCNR0 $IN1
ROCNR3 add $ROCNR2 " arg;"
INWQ2 add " $INW2 .h"
INWH2 add $INW2 .h
PGB2 peppher:component peppher:interface peppher:parameters
ROAA2 peppher:component peppher:interface peppher:parameters
IWVN2 peppher:component peppher:interface peppher:parameters
HD2 peppher:component peppher:interface peppher:parameters
DRS2 peppher:component peppher:interface peppher:parameters
THBS2 peppher:component peppher:interface peppher:parameters
URDS2 peppher:component peppher:interface peppher:parameters
PARAM1 peppher:component peppher:interface peppher:parameters
IMNO1 attribute@name peppher:component peppher:implementation
IMNWO1 add $IMNO1 _wrapper
LCLS2 attribute@name peppher:component peppher:implementation peppher:sourceFiles
LKS2 attribute@name@kernel peppher:component peppher:implementation peppher:sourceFiles
SOPN2 attribute@name@starpu_opencl_program peppher:component peppher:implementation peppher:sourceFiles
CCQN2 attribute@name@cl_command_queue peppher:component peppher:implementation peppher:sourceFiles
CKN2 attribute@name@cl_kernel peppher:component peppher:implementation peppher:sourceFiles
OBJ attribute@name peppher:component peppher:implementation peppher:sourceFiles peppher:sourceFile
CMP content peppher:compilation peppher:compiler peppher:name
FLG content peppher:compilation peppher:compiler peppher:flags
CTP attribute@type peppher:compilation peppher:compiler
OPT content peppher:compilation peppher:compiler peppher:output
OCR peppher:component peppher:implementation peppher:sourceFiles
OBJO attribute@name
CMPO content peppher:compilation peppher:compiler peppher:name
FLGO content peppher:compilation peppher:compiler peppher:flags
TYPE1 attribute@name peppher:component peppher:implementation peppher:targetPlatform
RIN1 attribute@name@xmlFile peppher:component peppher:implementation peppher:requiredInterfaces
INFM2 attribute@file peppher:component peppher:interface peppher:xmlFiles
PIFN1 attribute@name peppher:component peppher:implementation peppher:providedInterfaces peppher:providedInterface
CSR peppher:component peppher:implementation peppher:sourceFiles
IMPA1 attribute@impPath peppher:component peppher:interface
TMTYPS1 attribute@templateTypes peppher:component peppher:interface
UHBPM1 attribute@useHistoryModels peppher:component peppher:interface
URBPM1 attribute@useRegressionModels peppher:component peppher:interface
UNLRBPM1 attribute@useNLRegressionModels peppher:component peppher:interface
DCPU1 attribute@disableCPU peppher:component peppher:interface
DCUDA1 attribute@disableCUDA peppher:component peppher:interface
DOPENCL1 attribute@disableOpenCL peppher:component peppher:interface
TPLT attribute@type peppher:component peppher:implementation peppher:sourceFiles peppher:sourceFile
SN1 attribute@name peppher:component peppher:implementation peppher:sourceFiles peppher:sourceFile
CONSTRAINTS attribute@type@expr peppher:component peppher:implementation peppher:constraints
