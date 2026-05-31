#pragma once

#include <Engine.h>
#include <string>

namespace BejeweledTwist
{
    extern Sexy::Piece::Skin GetSkinByName(std::string name);
    extern Sexy::Piece::SpecialType GetSpecialByName(std::string name);

    extern std::string GetPieceSkinName(Sexy::Piece::Skin skin);
    extern std::string GetPieceSpecialName(Sexy::Piece::SpecialType special);
    extern Sexy::Piece::Skin GetRandomSkin();
    extern void TwistGemsAt(bool fromScript, int x, int y);
    extern void GetHoverPos(int& x, int& y);
    extern void SetPieceSkin(int x, int y, Sexy::Piece::Skin skin);
    extern Sexy::Piece::Skin GetPieceSkin(int x, int y);
    extern void SetPieceSkinAtHover(Sexy::Piece::Skin skin);
    extern void SetPieceSpecial(int x, int y, Sexy::Piece::SpecialType special);
    extern void SetPieceSpecialAtHover(Sexy::Piece::SpecialType special);
    extern void ClearBoard();
    extern void FillBoard();
    extern bool CheckSpecial(int x, int y, Sexy::Piece::SpecialType special);
    extern Sexy::Piece::SpecialType GetSpecial(int x, int y);
    extern void SetCounter(int x, int y, int counter);
    extern int GetCounter(int x, int y);
    extern void SetPieceType(int x, int y, int type);
    extern int GetPieceType(int x, int y);
    extern void SetOldSkin(int x, int y, Sexy::Piece::Skin skin);
    extern Sexy::Piece::Skin GetOldSkin(int x, int y);
    extern void SetPieceMatchable(int x, int y, bool matchable);
    extern bool GetPieceMatchable(int x, int y);

    extern Sexy::Piece* GetPiece(int x, int y);

    extern bool hasGameManager();
    extern Sexy::GameManager* getGameManager();
};
