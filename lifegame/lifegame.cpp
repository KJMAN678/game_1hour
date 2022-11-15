#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <curses.h>

#define FIELD_WIDTH (160)     // フィールドの幅
#define FIELD_HEIGHT (60)     // フィールドの高さ
#define FPS (10)              // 1秒あたりの更新回数
#define INTERVAL (1000 / FPS) // 更新間隔(ミリ秒)

// フィールド
bool field[FIELD_HEIGHT][FIELD_WIDTH] = {
    /*
    {0, 1, 0},
    {0, 0, 1},
    {1, 1, 1}
    */
};

void DrawField()
{
    system("clear");
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

// 1ステップ分のシミュレーションを実行する関数
void StepSimulation()
{
    // 次世代のフィールドを宣言する
    bool nextField[FIELD_HEIGHT][FIELD_WIDTH] = {};

    for (int y = 0; y < FIELD_HEIGHT; y++)
    {
        for (int x = 0; x < FIELD_WIDTH; x++)
        {
            // 対象のセルと隣接する、生きているセルの数を宣言する
            int livingCellCount = GetLivingCellCount(x, y);

            if (livingCellCount <= 1)
            {
                // 対象のセルを死滅させる
                nextField[y][x] = false;
            }
            else if (livingCellCount == 2)
            {
                // 現状維持
                nextField[y][x] = field[y][x];
            }
            else if (livingCellCount == 3)
            {
                // 対象のセルを誕生/生存させる
                nextField[y][x] = true;
            }
            else
            {
                // 対象載せるを死滅させる
                nextField[y][x] = false;
            }
        }
    }
    memcpy(field, nextField, sizeof field);
}

// パターンをフィールドにコピーする関数
void PatternTransfer(
    int _destX, int _destY,        // コピー先の座標
    int _srcWidth, int _srcHeight, // 書き込むパターンのサイズ
    bool *_pPattern                // 書き込むパターンのアドレス
)
{
    for (int y = 0; y < _srcHeight; y++)
    {
        for (int x = 0; x < _srcWidth; x++)
        {
            field[_destY + y][_destX + x] = _pPattern[y * _srcWidth + x];
            printf("%d", _pPattern[y * _srcWidth + x]);
        }
    }
}

int main(void)
{
    const int patternWidth = 10; // パターン幅を宣言する
    const int patternHeight = 8; // パターンの高さを宣言する
    bool pattern[patternHeight][patternWidth] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 1, 1, 0},
        {0, 0, 0, 0, 0, 1, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    // パターンをフィールドの中心にコピーする
    PatternTransfer(FIELD_WIDTH / 2 - patternWidth / 2, FIELD_HEIGHT / 2 - patternHeight / 2, patternWidth, patternHeight, (bool *)pattern);

    clock_t lastClock = clock(); // 前回の経過時間を宣言する

    // while (1)
    // {
    //     clock_t newClock = clock(); // 現在の経過時間を宣言する
    //     if (newClock < lastClock + INTERVAL)
    //     {
    //         continue;
    //     }

    //     lastClock = newClock;

    //     // getchar();
    //     DrawField();
    //     StepSimulation();
    // }

    // return 0;
}