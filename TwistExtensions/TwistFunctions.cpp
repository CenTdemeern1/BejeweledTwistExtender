#include "BejeweledTwist.h"
#include "TwistFunctions.h"

using namespace BejeweledTwist;

TwistFunctions gTwistFunctions = {
    &GetSkinByName,
    &GetSpecialByName,

    &GetPieceSkinName,
    &GetPieceSpecialName,
    &GetRandomSkin,
    &TwistGemsAt,
    &GetHoverPos,
    &SetPieceSkin,
    &GetPieceSkin,
    &SetPieceSkinAtHover,
    &SetPieceSpecial,
    &SetPieceSpecialAtHover,
    &ClearBoard,
    &FillBoard,
    &CheckSpecial,
    &GetSpecial,
    &SetCounter,
    &GetCounter,
    &SetPieceType,
    &GetPieceType,
    &SetOldSkin,
    &GetOldSkin,
    &SetPieceMatchable,
    &GetPieceMatchable,

    &GetPiece,

    &hasGameManager,
    &getGameManager,
};
