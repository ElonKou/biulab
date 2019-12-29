# BiuLab

## 1.BiuLab introduce

This is a platform for doing interesting experiments. 
The BiuLab was designed based on plugin architecture, you can create your own modules by c/c++/cuda, then controll it by your display window.

![text](./resources/images/biulab_show.png)

## 2.install
```bash
# 2.1 ubuntu install 
sudo apt-get install libglfw3 libglfw3-dev libglfw3-doc
sudo apt-get  install libglew-dev

# 2.2 build BiuLab (The default install path is install/bin on your source dir, you can change it in CMakeLists.txt)
cd biulab
mkdir build
cd build
cmake ..
make
make installl

# 2.3 build BiuLab (The default install path is install/bin on your source dir, you can change it in modules/CMakeLists.txt)
cd modules/
mkdir build
cd build
cmake ..
make
make installl

# 2.4 run biulab
cd install/bin
./biulab
```

## 3.TODO

Map:
- [x] display map panel.
- [x] add new map elem(OUT).
- [x] add robbie/map Selectable tab.
- [ ] display robbie and wall(Texture).
- [x] select gene & map function.
- [x] save map.
- [x] select map elem enevts.
- [x] create new map by mouse.
- [x] select save and load path.
- [ ] rebuild the Map class.
- [ ] Mapeditor history.
- [ ] redo/undo and so on.

Algorithm:
- [ ] add map/algorithm panel/tab.
- [ ] Robbie run on map.

Frame:
- [x] separate all the module from project.
- [ ] load the module by plugin.
- [x] test for build plugin frame.
- [ ] build Window/Map/Controller/Core/base class.
- [ ] create all the windows base class.
- [ ] create the simplest module.
- [ ] modified the Makefile of whole project.
- [ ] add submodule Makefile/CmakeLists.

Target:
- [ ] run the MapEditor module.
- [ ] run the LifeGame module.
- [ ] run the genetic module.

## architecture
- [x] Dynamics lib

### core class
- [x] biulab
- [x] Inspector
- [x] dockspace
- [x] window

- [ ] controller


