.PHONY:clean cleanall
CC = g++
EXE = genetic

GUIOBJ = imgui.o imgui_demo.o imgui_draw.o imgui_widgets.o imgui_impl_glfw.o imgui_impl_opengl3.o
LIBOBJ = lib.o
COREOBJ = core.o frame.o editor_map.o editor_robbie.o
MAINOBJ = main.o

GUIOBJS = $(addprefix imgui/, $(GUIOBJ))
LIBOBJS = $(addprefix lib/, $(LIBOBJ))
COREOBJS = $(addprefix core/, $(COREOBJ))
MAINOBJS = $(addprefix src/, $(MAINOBJ))

OBJS = $(GUIOBJS) $(LIBOBJS) $(COREOBJS) $(MAINOBJS)

# $(CC) -I./ -I./imgui/ -I./src/ -I./lib/ -I./core/ -c $< -o $@ -std=c++11
# /usr/include/x86_64-linux-gnu/sys/io.h
%.o:%.cc
	$(CC) -I./lib/ -I./core/ -I./imgui/ -I./src/ -c $< -o $@ -std=c++11
$(EXE):$(OBJS)
	$(CC) $(OBJS) -lglfw -lGLEW -lGL -o $(EXE)
clean:
	rm $(OBJS)
