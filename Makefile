.PHONY:clean cleanall
CC = g++
EXE = biulab

GUIOBJ = imgui.o imgui_demo.o imgui_draw.o imgui_widgets.o imgui_impl_glfw.o imgui_impl_opengl3.o
COREOBJ = WindowView.o Main.o Vec.o Lib.o ControllerBase.o MapBase.o ModulesManager.o Lab.o
MODULES_ROBBIE_OBJ = Robbie.o RobbieController.o RobbieMap.o RobbieConfig.o
MODULES_MAPEDITOR_OBJ = MapEditor.o MapView.o


GUIOBJS = $(addprefix imgui/, $(GUIOBJ))
COREOBJS = $(addprefix core/, $(COREOBJ))
MODULES_ROBBIE_OBJS = $(addprefix modules/Robbie/, $(MODULES_ROBBIE_OBJ))
MODULES_MAPEDITOR_OBJS = $(addprefix modules/MapEditor/, $(MODULES_MAPEDITOR_OBJ))

OBJS = $(GUIOBJS) $(COREOBJS) $(MODULES_ROBBIE_OBJS) ${MODULES_MAPEDITOR_OBJS}

%.o:%.cc
	$(CC) -I./include/ -I./core/ -I./imgui/ -I./modules/MapEditor/ -I./modules/Robbie/ -c $< -o $@ -std=c++11
$(EXE):$(OBJS)
	$(CC) $(OBJS) -lglfw -lGLEW -lGL -o $(EXE)
clean:
	rm $(OBJS)
