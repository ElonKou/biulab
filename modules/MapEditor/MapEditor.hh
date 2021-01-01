#pragma once
#ifndef EDITOR_MAP_HH_
#define EDITOR_MAP_HH_

#include "Lib.hh"
#include "MapEditorBase.hh"
#include "MapBase.hh"

class MapEditor : public MapEditorBase {
  private:
    int         selectPosCnt;
    vec_2i      selectPos[2];
    HistoryType histories[10];

  public:
    int width;
    int height;

    MapEditor();
    ~MapEditor();
    void CheckAndSetElem(MapBase& mp, vec_2i pos);

    void DrawLine(MapBase& mp, vec_2i pos_x, vec_2i pos_y);
    void DrawRect(MapBase& mp, vec_2i pos_x, vec_2i pos_y);
    void DrawPoint(MapBase& mp, vec_2i pos);
    void DrawBlock(MapBase& mp, vec_2i pos);
    void DrawAll(MapBase& mp, vec_2i pos);

    void UpdateMap(MapBase& mp);
    void SetTools(ToolsType tool);
    void SetSelection(SelectionsType slect);
    void Resize(MapBase& mp);
    void ModifiedMap(MapBase& mp, vec_2i pos);
};

#endif
