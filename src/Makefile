

TARGET_EXT=cpp

#---------------------------------------------------------------------#
TYPE=bin
#---------------------------------------------------------------------#
#TYPE=static
#LIB_NAME=hello
#LIB_HEADER=x.h
#LIB_HEADER_INSTALL_ROOT_DIR=/home/lu/Downloads
#LIB_BIN_INSTALL_ROOT_DIR=/home/lu/Downloads
#---------------------------------------------------------------------#

#MACHINE_NAME=EXCESS
#MODULE_LOAD=CLANG NVML PCM CUPTI OPENCL OPENMP OPENGL PTHREAD CXX_PTHREAD R RCPP RINSIDE
#make cool EC=-DDEBUG #make allclean cool EC="-DVERBOSE=1"

USR_INC_SEARCH_PATH=common/ error/ infoHolder/ infoHolder/cg_helpers/ init/ main/ stringBuild/ xmlParse/ static_constraint_eval/

#EC=-I ./common/ -I ./error/ -I ./infoHolder/ -I ./infoHolder/cg_helpers/ -I ./init/ -I ./main/ -I  ./stringBuild/ -I ./xmlParse/ -I ./static_constraint_eval/
#EC+=-I /home/lu/Documents/Research/research_original_data/YearlyData/2016/001.HipeacConference/2.Demo/1.CompositionTool/1.dependency/install/include
#EL=-L/home/lu/Documents/Research/research_original_data/YearlyData/2016/001.HipeacConference/2.Demo/1.CompositionTool/1.dependency/install/lib -lxerces-c


#Please change your xercesc path here
EC+=-I /home/lu/Documents/Xerces/install/include
EL=-L/home/lu/Documents/Xerces/install/lib -lxerces-c
#RP=sudo #Running Prefix
#EF=$(PCM_SRC)/cpucounters.cpp #Extra Files
#EXCLUDE_SRC_FILES=funcallsample.cpp
#ERP:=1 2

#DEBUG=BATCH
DEBUG=INTERACTIVE
#DEBUG=BACK_TRACE

#PROFILE=true

NO_STRIP=true

NO_CPPCHECK=true

TARGET=compose

#NO_WARNINGS:=true


#If App generate some file, put it here, allclean target wil delete it.
#APP_FILES=idlist
#Separete app files, such that you can view the source and execute the binary
#APP_FILE1=idlist
#APP_FILE2=idlist

#If you want to see the app generated files, put it here, it will be executed after app runs.
#APP_VIEW_RESULT=vi $(APP_FILES)

include MakefileCommon
include Makefile.depend
