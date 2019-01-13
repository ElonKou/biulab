.PHONY:clean cleanall
CC = g++
EXE = genetic
LIBOBJ = imgui.o imgui_demo.o imgui_draw.o imgui_widgets.o imgui_impl_glfw.o imgui_impl_opengl3.o
MYOBJ = core_genetic.o lib.o main.o
LIBOBJS = $(addprefix imgui/, $(LIBOBJ))
MYOBJS = $(addprefix src/, $(MYOBJ))
OBJS = $(LIBOBJS) $(MYOBJS)
%.o:%.cpp
	$(CC) -I./imgui/ -I./src/ -c $< -o $@ -std=c++11
$(EXE):$(OBJS)
	$(CC) $(OBJS) -lglfw -lGLEW -lGL -o $(EXE)
cleanall:clean
	rm $(EXE)
clean:
	rm $(OBJS)
