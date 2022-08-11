# include "conio.h"


// 戦闘シーンの関数
void Battle()
{
    // キーボード入力を待つ
    _getch();
}

// キャラクターの構造体を宣言する
typedef struct {
    int hp;                 // HP
    int maxHp;              // 最大HP
    int mp;                 // MP
    int maxMp;              // 最大MP
    char name[4 * 2 + 1];   // 名前
} CHARACTER;

// モンスターの種類を定義する
enum
{
    MONSTER_PLAYER, // プレイヤー
    MONSTER_MAX     // モンスターの種類の数
};

CHARACTER monster[MONSTER_MAX] = 
{
    // プレイヤー
    {
        15,        // HP
        15,        // 最大HP
        15,        // MP
        15,        // 最大MP
        "ゆうしゃ", // 名前
    },
};

// キャラクターの種類を定義する
enum
{
    CHARACTER_PLAYER,   // プレイヤー
    CHARACTER_MONSTER,  // モンスター
    CHARACTER_MAX       // キャラクターの種類の数
};

// キャラクターの配列を宣言する
CHARACTER characters[CHARACTER_MAX];

// ゲームを初期化する関数を宣言する
void Init()
{
    characters[CHARACTER_PLAYER] = monsters[MONSTER_PLAYER];
}

// 戦闘シーンの画面を描画する関数を宣言する
void DrawBattleScreen()
{

}

int main()
{
    Init(); // ゲームを初期化
    Battle(); // バトルの宣言
}

