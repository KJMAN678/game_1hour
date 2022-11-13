#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

#define FIELD_WIDTH (12)  // フィールドの幅
#define FIELD_HEIGHT (12) // フィールドの高さ

// フィールド
bool field[FIELD_HEIGHT][FIELD_WIDTH] = {
    {0, 1, 0},
    {0, 0, 1},
    {1, 1, 1}};

void DrawField()
{
    system("cls");
    for (int y = 0; y < FIELD_HEIGHT; y++)
    {
        for (int x = 0; x < FIELD_WIDTH; x++)
        {
            printf("%s", field[y][x] ? "o" : " ");
        }
        printf("\n");
    }
}

// 対象のセルと隣接する生きたセルの数を取得する
int GetLivingCellCount(int _x, int _y)
{
    // 生きているセルを数えるカウンター
    int count = 0;

    for (int y = _y - 1; y <= _y + 1; y++)
    {
        // 上下にループさせない場合は、行が範囲内かどうか判定する
        // if ((y < 0) || (y >= FIELD_HEIGHT))
        // {
        //     continue;
        // }

        // 上下にループした y座標
        int roopedY = (FIELD_HEIGHT + y) % FIELD_HEIGHT;

        for (int x = _x + -1; x <= _x + 1; x++)
        {
            // 左右にループさせない場合は、行が範囲内かどうかを判定する
            // if ((x < 0) || (x >= FIELD_WIDTH))
            // {
            //     continue;
            // }

            // 左右にループした x座標
            int roopedX = (FIELD_WIDTH + x) % FIELD_WIDTH;

            // 対象の座標が中心載せるかどうか判定
            if ((roopedX == _x) && (roopedY == _y))
            {
                continue;
            }
            count += field[roopedY][roopedX];
        }
    }

    return count;
}

int main(void)
{
    while (1)
    {
        getchar();
        DrawField();
    }

    return 0;
}