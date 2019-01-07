.PHONY:clean cleanall
CC = g++
EXE = genetic
OBJ = imgui.o imgui_demo.o imgui_draw.o imgui_widgets.o imgui_impl_glfw.o imgui_impl_opengl3.o
OBJS = $(addprefix imgui/, $(OBJ))
OBJS += src/run.o
%.o:%.cpp
	$(CC) -I./imgui -c $< -o $@
$(EXE):$(OBJS)
	$(CC) $(OBJS) -lglfw -lGLEW -lGL -o $(EXE)
cleanall:clean
	rm $(EXE)
clean:
	rm $(OBJS)
