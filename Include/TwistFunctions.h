#ifndef __TWISTFUNCTIONS_H_
#define __TWISTFUNCTIONS_H_

#include <Engine.h>
#include <string>

typedef struct {
    Sexy::Piece::Skin (*GetSkinByName)(std::string name);
    Sexy::Piece::SpecialType (*GetSpecialByName)(std::string name);

    std::string (*GetPieceSkinName)(Sexy::Piece::Skin skin);
    std::string (*GetPieceSpecialName)(Sexy::Piece::SpecialType special);
    Sexy::Piece::Skin (*GetRandomSkin)();
    void (*TwistGemsAt)(bool fromScript, int x, int y);
    void (*GetHoverPos)(int& x, int& y);
    void (*SetPieceSkin)(int x, int y, Sexy::Piece::Skin skin);
    Sexy::Piece::Skin (*GetPieceSkin)(int x, int y);
    void (*SetPieceSkinAtHover)(Sexy::Piece::Skin skin);
    void (*SetPieceSpecial)(int x, int y, Sexy::Piece::SpecialType special);
    void (*SetPieceSpecialAtHover)(Sexy::Piece::SpecialType special);
    void (*ClearBoard)();
    void (*FillBoard)();
    bool (*CheckSpecial)(int x, int y, Sexy::Piece::SpecialType special);
    Sexy::Piece::SpecialType (*GetSpecial)(int x, int y);
    void (*SetCounter)(int x, int y, int counter);
    int (*GetCounter)(int x, int y);
    void (*SetPieceType)(int x, int y, int type);
    int (*GetPieceType)(int x, int y);
    void (*SetOldSkin)(int x, int y, Sexy::Piece::Skin skin);
    Sexy::Piece::Skin (*GetOldSkin)(int x, int y);
    void (*SetPieceMatchable)(int x, int y, bool matchable);
    bool (*GetPieceMatchable)(int x, int y);

    Sexy::Piece* (*GetPiece)(int x, int y);

    bool (*hasGameManager)();
    Sexy::GameManager* (*getGameManager)();
} TwistFunctions;

#endif // __TWISTFUNCTIONS_H_
