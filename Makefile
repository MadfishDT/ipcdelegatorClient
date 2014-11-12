###############################
# Makefile ver 0.1 by greenfish
###############################
#
# make                          : debug ����
# make debug                    : debug ���� 
# make release                  : release ����
# make clean [debug, release]   : �ش� ���� ��� ���� ����
# make rebuild [debug, release] : rebuild ����

# ������ �⺻���� debug�̸�,
# �̰� section������ debug�� release�� ���� �κ��� �����Ѵ�.
# CFLAGS�� CPPFLAGS�� -c �ɼ��� �����Ѵ�. rule���� ���� -c�� �־�� �Ѵ�.
# LFLAGS�� Link �ɼ����� �ʿ�� �߰��Ѵ�.
# config�� configuration���� debug/release�� �����ϸ�, ���� ��ΰ��� ������ �ش�.
# BUILD_DIR�� ���忡 ���� ��θ� �����Ѵ�.
# TARGET�� ���� ������ ���⹰�� �����Ѵ�. ���� ��� ��θ� ���Խ�Ų��.
CC        = g++
CFLAGS    = -I/usr/local/include
CPPFLAGS  = -I/usr/local/include
LFLAGS    = 
LDFLAGS   =  -lm -lpthread
CONFIG    = debug
BUILD_DIR = ./Build/$(CONFIG)
TARGET    = $(BUILD_DIR)/IpcDelegator

##################################
# makefile�� ���� argument�� ���Ѵ�.
ifneq "$(findstring clean, $(MAKECMDGOALS))" ""
    ARG.CLEAN  = 1
endif

ifneq "$(findstring release, $(MAKECMDGOALS))" ""
    ARG.RELEASE = 1
endif

ifneq "$(findstring debug, $(MAKECMDGOALS))" ""
    ARG.DEBUG = 1
endif

ifneq "$(findstring rebuild, $(MAKECMDGOALS))" ""
    ARG.REBUILD = 1
endif

##################################
# DEBUG / RELEASE ���带 �����Ѵ�.
ifeq ($(ARG.RELEASE),1)
    # ------------------------------
    # release�� Ưȭ�� ������ �Ѵ�.
    # ------------------------------
    CFLAGS    += -O -DNDEBUG
    CPPFLAGS  += -O -DNDEBUG
    CONFIG    = release
else
    # ------------------------------
    # debug�� Ưȭ�� ������ �Ѵ�.
    # ------------------------------
    CFLAGS    += -DDEBUG -g
    CPPFLAGS  += -DDEBUG -g
    CONFIG    = debug
endif

##################################
# makefile ���� ó��

.PHONY: debug release build clean rebuild PRE_BUILD POST_BUILD all

# �Ϲ����� Build�� ������ �����Ѵ�.
BUILD_STEP = PRE_BUILD $(TARGET) POST_BUILD

# Makefile�� ���� Target�� Depend�� �����Ѵ�.
ifeq ($(ARG.REBUILD),1)
    # rebuild�� ���,...
    # ���� ������ clean�� �����Ѵ�.
    rebuild: | clean $(BUILD_STEP)
    debug: ; @true
    release: ; @true
else ifeq ($(ARG.CLEAN),1)
    # clean�� ���,...
    # clean target�� rule part�� ���ǵǾ� �ִ�.
    release: ; @true
    debug: ; @true
else
    # clean/rebuild�� �Բ� ������ ���� ���,...
    # �̰����� ���尡 �̷�����.
    # release, debug�� �ܵ� ����� �� �־� @true���� �ʴ´�.
    build: | $(BUILD_STEP)
    release: build
    debug: build
endif

# release, debug�� ��ɿ� ���ԵǾ� ���յǸ�,
# release, debug target�� ã�� �Ǵµ�,
# �ǵ����� ����
#    "make: Nothing to be done for 'release'"
#    "make: Nothing to be done for 'debug'"
# �� �����ϱ� ���� @true�� ����Ͽ���.

# ------------------------------
# Other macro
# ------------------------------
# .o�� .d�� �ٲ��ش�.
DEPEND_FILE = $(patsubst %.o,%.d,$@)

##################################
# ���� �׸� ����
##################################

# Group�� ���� ȯ�� ����(������ �ɼ�, ���� ���, �ҽ� Ȯ����, ...)�� ���� ���� ���� ���� ���Ѵ�.

#--------------------------------
# ���� : ../../ �� ���� ���� directory�� �Ѿ�� source�� �������� �ȵȴ�.
# �ֳ��ϸ�, ./Build/ ������ ��� ���� ������ ���� �ϴµ�,
# ../../���� ���ԵǸ� ./Build/ ������ ���� ������ �� �� �ֱ� ������, �����ϴ�.
# ��, ������ �⺻ ������ ���Ѿ� �Ѵ�.
# `makefile�� ��ġ�� ��� ����Ǵ� source�� �ֻ��� ��ο� �־�� �Ѵ�.'

##################################
# Group 01
GROUP.01.SRC = ClArg.cpp\
          ClArgList.cpp\
          iObject_glue.cpp\
          MathodDelegator.cpp\
          MethodCaller.cpp\
          ./IPCS/IPCCom.cpp\
          ./IPCS/Linux/NamedPipe.cpp\
          ./IPCS/Linux/MessageQue.cpp\
          IPCRepresent.cpp\
          ObjectBinderFactory.cpp\
          ObjectMathodMap.cpp\
          ObjectMethodFilter.cpp\
          IPCDelegatorCore.cpp\
          ProcDataAdapter.cpp\
          ProcPackage.cpp\
          ProcParser.cpp\
          RootComm.cpp\
          RPCObjectBinder.cpp\
          ThreadRepresent.cpp\
          main.cpp
GROUP.01.OBJ = $(addprefix $(BUILD_DIR)/,$(GROUP.01.SRC:.cpp=.o))
GROUP.01.DEP = $(GROUP.01.OBJ:.o=.d)


##################################
# [Link] Link Part
# ����� .o ���� ��ũ�Ͽ� TARGET�� �����Ѵ�. 
$(TARGET): $(GROUP.01.OBJ)
	@echo ----------------------------------------
	@echo Link : $(TARGET)
	@echo ----------------------------------------
	$(CC) $(LFLAGS) $(GROUP.01.OBJ) -o $(TARGET) $(LDFLAGS)
	@echo

##################################
# [Compile] Compile Part
# Group1 �ҽ�(*.cpp)�鿡 ����, �����($(@D))�� �����ϰ�, dependency ������ �����ѵ� ������ �Ѵ�.
$(GROUP.01.OBJ): $(BUILD_DIR)/%.o: %.cpp
	@echo ----------------------------------------
	@echo Compile : [GROUP.01] $<
	@echo ----------------------------------------
	@test -d $(@D) || mkdir -p $(@D)
	$(CC) -MM -MF $(DEPEND_FILE) -MT"$(DEPEND_FILE:.d=.o)" $(CFLAGS) $<
	$(CC) $(CFLAGS) -c -o $@ $<
	@echo
	
##################################
# Build�� ���۵Ǿ���.
# �ʿ��� ��ó���� �ִٸ� �����Ѵ�.
PRE_BUILD:
	@echo ========================================
	@echo Make file started [config =\> $(CONFIG)]
	@echo ========================================
	@echo 

##################################
# Build�� ����Ǿ���.
# �ʿ��� ��ó���� �ִٸ� �����Ѵ�.
POST_BUILD:
	@echo ========================================
	@echo Make file finished [config =\> $(CONFIG)]
	@echo ========================================

##################################
# Clean up �Ѵ�.
clean:
	rm -f $(GROUP.01.OBJ)
	rm -f $(GROUP.01.DEP)
	rm -f $(TARGET)
	@echo ----------------------------------------
	@echo Clean work finished [config =\> $(CONFIG)]
	@echo ----------------------------------------

##################################
# �� �κп� dependency ���ϵ��� include�Ѵ�.
-include $(GROUP.01.DEP)

##########################################################
# document
##########################################################
#
# Group �߰� ���
#   - �߰��Ѵٴ� ���� �ٸ� Group�� ���Ͽ� ���ΰ���,
#       ; ���� ȯ���� �ٸ� ��� (������ �ɼ�, ���� ���, �ҽ� Ȯ����, ...) 
# �� �߻��Ͽ��� �����̴�.
#
# 1. Group ���� �߰�
#
# Group ����ο� �Ʒ� �κ��� �߰��Ѵ�.
# ���� ���� ������ ������ sub directory�� �ִ� ��� addprefix�� �̿��� �� �ִ�.
#
# ##################################
# # Group 03
# GROUP.03.SRC = G1.cpp G2.cpp
# GROUP.03.SRC.TMP = G3.cpp G4.cpp G5.cpp G6.cpp G7.cpp
# GROUP.03.SRC += $(addprefix ./some_group/, $(GROUP.03.SRC.TMP))
# GROUP.03.OBJ = $(addprefix $(BUILD_DIR)/,$(GROUP.03.SRC:.cpp=.o))
# GROUP.03.DEP = $(GROUP.03.OBJ:.o=.d)
#
# 2. Link �߰�
#
# Target�� �Ʒ��� ���� GROUP.03.OBJ�� depend�Ͽ� Link�ǵ��� �Ѵ�.
#
# $(TARGET): $(GROUP.01.OBJ) $(GROUP.02.OBJ) $(GROUP.03.OBJ)
#
# 3. Compile �߰�
#
# �Ʒ��� ���� ��Ģ�� �߰��Ѵ�. Ȯ���ڳ� ������ �ɼǵ��� ���� ������ �� �ִ�.
#
# $(GROUP.03.DEP): $(BUILD_DIR)/%.d: %.cpp
#	@echo ----------------------------------------
#	@echo Depend : $<
#	@echo ----------------------------------------
#	@test -d $(@D) || mkdir -p $(@D)
#	$(CC) -MM -MF $(DEPEND_FILE) -MT"$(DEPEND_FILE:.d=.o)" $<
#	$(CC) $(CFLAGS) -c -o $@ $<
#	@echo 
#
# 4. clean �߰�
#
#  	rm -f $(GROUP.03.OBJ)
# 	rm -f $(GROUP.03.DEP)
#
# 5. include �߰�
#
# -include $(GROUP.02.DEP)
#
# * ����
# make
# make debug
# make release
# make clean [release, debug]
# make rebuild [release, debug]
# (EOF)
