CPP = g++
CPP_FLAGS = -c
RM = rm

ifndef verbose
	SILENT = @
endif

DEFINES += -D_CRT_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_DEPRECATE -D_SCL_SECURE_NO_WARNINGS -DTIXML_USE_STL -DFREEGLUT_STATIC -DWIN32 -D_LIB -DFREEGLUT_LIB_PRAGMAS=0 -DDEBUG -D_DEBUG
INCLUDES = -I../../framework -I../../glsdk/glload/include -I../../glsdk/glimg/include -I../../glsdk/glm -I../../glsdk/glutil/include -I../../glsdk/glmesh/include -I../../glsdk/freeglut/include

CPP_FLAGS += $(DEFINES) $(INCLUDES) -g

LIB_DIR = -L../../glsdk/glload/lib -L../../glsdk/glimg/lib -L../../glsdk/glutil/lib -L../../glsdk/glmesh/lib -L../../glsdk/freeglut/lib -L../../framework/lib
LDDEPS = ../../framework/lib/libframeworkD.a
LIBS = $(LDDEPS) -lglloadD -lglimgD -lglutilD -lglmeshD -lfreeglutD -lglu32 -lopengl32 -lgdi32 -lwinmm -luser32

LDFLAGS = $(LIB_DIR) $(LIBS)

OBJS = main.o fx.o

all: fps.exe

fps.exe: $(OBJS)
	@echo Linking
	$(SILENT) $(CPP) $^ $(LDFLAGS) -o $@

%.o: %.cpp
	$(SILENT) $(CPP) $(CPP_FLAGS) $^ 

clean:
	@$(RM) *.o
	@$(RM) fps.exe