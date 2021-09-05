#include "TileMap.h"
#include "../system/Window.h"
#include "../graphic/Sprite.h"
#include "../graphic/Shader.h"
#include "../graphic/Camera.h"
#include "../gameobject/TextureManager.h"
#include "../imgui/SBGui.h"
#include "../imgui/SBGuiWindow.h"

static Sprite** tilemap;
int** colmap;

static const int row = 20;
static const int col = 30;

void TileMapOneInit()
{
  tilemap = new Sprite * [row];

  for (int i = 0; i < row; ++i)
    tilemap[i] = new Sprite[col];


  colmap = new int * [row];

  for (int i = 0; i < row; ++i)
    colmap[i] = new int[col];

  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < col; j++)
    {
      if (i == 0 || j == 0 || i == (row - 1) || j == (col - 1))
      {
        colmap[i][j] = 1;
      }
      else if (i == 9 || j == 9 || i == 10 || j == 10 ||
               i == 19 || j == 19 || i == 20 || j == 20)
      {
        colmap[i][j] = 1;
      }
      else
      {
        colmap[i][j] = 0;
      }
    }
  }
  //lava and mud
  colmap[9][4] = 0;
  colmap[9][5] = 0;
  colmap[10][4] = 0;
  colmap[10][5] = 0;

  colmap[4][9] = 4;
  colmap[5][9] = 4;
  colmap[4][10] = 4;
  colmap[5][10] = 4;

  for (int i = 2; i < 8; i++)
  {
    colmap[12][i] = 1;
  }
  for (int i = 12; i < 18; i++)
  {
    colmap[i][7] = 1;
  }
  for (int i = 14; i < 19; i++)
  {
    colmap[i][5] = 1;
  }
  for (int i = 13; i < 16; i++)
  {
    colmap[i][2] = 1;
  }
  for (int i = 12; i < 19; i++)
  {
    colmap[i][8] = 2;
  }
  for (int i = 13; i < 19; i++)
  {
    colmap[i][6] = 2;
  }
  colmap[18][7] = 2;
  colmap[13][5] = 2;
  colmap[15][3] = 1;
  colmap[15][1] = 4;

  colmap[4][19] = 5;
  colmap[5][19] = 5;
  colmap[4][20] = 5;
  colmap[5][20] = 5;

  colmap[9][14] = 0;
  colmap[9][15] = 0;
  colmap[10][14] = 0;
  colmap[10][15] = 0;

  for (int i = 12; i <= 17; i++)
  {
    for (int j = 12; j <= 17; j++)
    {
      colmap[i][j] = 3;
    }
  }

  colmap[12][18] = 0;
  colmap[12][11] = 0;
  colmap[17][11] = 0;
  colmap[17][18] = 0;

  colmap[4][29] = 0;
  colmap[5][29] = 0;

  for (int i = 2; i <= 7; i++)
  {
    colmap[i][22] = 1;
  }
  colmap[3][23] = 1;
  colmap[5][23] = 1;

  colmap[1][24] = 1;
  colmap[3][24] = 1;
  colmap[5][24] = 1;
  colmap[7][24] = 1;

  colmap[3][25] = 1;
  colmap[7][25] = 1;

  for (int i = 2; i <= 8; i++)
  {
    colmap[i][26] = 1;
  }

  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < col; j++)
    {
      tilemap[i][j].Init(Shader_BasicTexture);
      if (colmap[i][j] == 1)
      {
        tilemap[i][j].SetTexture(Tex_Wall);
      }
      else if (colmap[i][j] == 2)
      {
        tilemap[i][j].SetTexture(Tex_Lava);
      }
      else if (colmap[i][j] == 3)
      {
        tilemap[i][j].SetTexture(Tex_Mud);
      }
      else if (colmap[i][j] == 4)
      {
        tilemap[i][j].SetTexture(Tex_DoorA);
      }
      else if (colmap[i][j] == 5)
      {
        tilemap[i][j].SetTexture(Tex_DoorB);
      }
      else
      {
        tilemap[i][j].SetTexture(Tex_Grass);
      }
      tilemap[i][j].SetPosition(i*50+25, j*50+25);
      tilemap[i][j].SetSize(50.0f, 50.0f);
      tilemap[i][j].SetCamera(mainCam);
      tilemap[i][j].setAlpha(1.0f);

    }
  }
}
void TileMapOneUpdate(const double deltaTime)
{
  if (colmap[4][9] == 0)
  {
    tilemap[4][9].SetTexture(Tex_Grass);
    tilemap[5][9].SetTexture(Tex_Grass);
    tilemap[4][10].SetTexture(Tex_Grass);
    tilemap[5][10].SetTexture(Tex_Grass);
    tilemap[15][1].SetTexture(Tex_Grass);
  }
  if (colmap[4][19] == 0)
  {
    tilemap[4][19].SetTexture(Tex_Grass);
    tilemap[5][19].SetTexture(Tex_Grass);
    tilemap[4][20].SetTexture(Tex_Grass);
    tilemap[5][20].SetTexture(Tex_Grass);
  }
  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < col; j++)
    {
      tilemap[i][j].Update(deltaTime);
    }
  }

}
void TileMapOneShutdown()
{
  for (int i = 0; i < row; ++i) {
    delete[] tilemap[i];
    delete[] colmap[i];
  }
  delete[] tilemap;
  delete[] colmap;
}