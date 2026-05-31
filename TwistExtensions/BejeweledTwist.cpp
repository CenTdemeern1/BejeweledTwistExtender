#include "BejeweledTwist.h"

#include <Engine.h>
#include <string>
#include "Extender/util.h"

namespace BejeweledTwist {
    Sexy::Piece::Skin GetSkinByName(std::string name)
    {
        for (auto& c : name) c = toupper(c);

        if (name == "RED")
            return Sexy::Piece::Skin::RED;
        else if (name == "WHITE")
            return Sexy::Piece::Skin::WHITE;
        else if (name == "GREEN")
            return Sexy::Piece::Skin::GREEN;
        else if (name == "YELLOW")
            return Sexy::Piece::Skin::YELLOW;
        else if (name == "PURPLE")
            return Sexy::Piece::Skin::PURPLE;
        else if (name == "ORANGE")
            return Sexy::Piece::Skin::ORANGE;
        else if (name == "BLUE")
            return Sexy::Piece::Skin::BLUE;
        else if (name == "UNMATCHABLE")
            return Sexy::Piece::Skin::UNMATCHABLE;
        else
            return static_cast<Sexy::Piece::Skin>(-1);
    }

    Sexy::Piece::SpecialType GetSpecialByName(std::string name)
    {
        for (auto& c : name) c = toupper(c);

        if (name == "NONE")
            return Sexy::Piece::NONE;
        else if (name == "FRUIT")
            return Sexy::Piece::FRUIT;
        else if (name == "SKULL")
            return Sexy::Piece::SKULL;
        else if (name == "LOCK")
            return Sexy::Piece::LOCK;
        else if (name == "LIGHTNING")
            return Sexy::Piece::LIGHTNING;
        else if (name == "FLAME")
            return Sexy::Piece::FLAME;
        else if (name == "SUPERNOVA")
            return Sexy::Piece::SUPERNOVA;
        else if (name == "ICE")
            return Sexy::Piece::ICE;
        else if (name == "ANGEL")
            return Sexy::Piece::ANGEL;
        else if (name == "DOOM")
            return Sexy::Piece::DOOM;
        else if (name == "BOMB")
            return Sexy::Piece::BOMB;
        else if (name == "COAL")
            return Sexy::Piece::COAL;
        else
            return static_cast<Sexy::Piece::SpecialType>(-1);
    }

    std::string GetPieceSkinName(Sexy::Piece::Skin skin)
    {
        switch (skin)
        {
        case Sexy::Piece::Skin::RED:
            return "Red";
        case Sexy::Piece::Skin::WHITE:
            return "White";
        case Sexy::Piece::Skin::GREEN:
            return "Green";
        case Sexy::Piece::Skin::YELLOW:
            return "Yellow";
        case Sexy::Piece::Skin::PURPLE:
            return "Purple";
        case Sexy::Piece::Skin::ORANGE:
            return "Orange";
        case Sexy::Piece::Skin::BLUE:
            return "Blue";
        case Sexy::Piece::Skin::UNMATCHABLE:
            return "Unmatchable";
        default:
            return "Invalid";
        }
    }

    std::string GetPieceSpecialName(Sexy::Piece::SpecialType special)
    {
        switch (special)
        {
        case Sexy::Piece::NONE:
            return "None";
        case Sexy::Piece::FRUIT:
            return "Fruit";
        case Sexy::Piece::SKULL:
            return "Skull";
        case Sexy::Piece::LOCK:
            return "Lock";
        case Sexy::Piece::LIGHTNING:
            return "Lightning";
        case Sexy::Piece::FLAME:
            return "Flame";
        case Sexy::Piece::SUPERNOVA:
            return "SuperNova";
        case Sexy::Piece::ICE:
            return "Ice";
        case Sexy::Piece::ANGEL:
            return "Angel";
        case Sexy::Piece::DOOM:
            return "Doom";
        case Sexy::Piece::BOMB:
            return "Bomb";
        case Sexy::Piece::COAL:
            return "Coal";
        default:
            return "Unknown";
        }
    }

    Sexy::Piece::Skin GetRandomSkin()
    {
        int r = random(0, 6);

        return static_cast<Sexy::Piece::Skin>(r);
    }

    void TwistGemsAt(bool fromScript, int x, int y)
    {
        if (!hasGameManager())
            return;

        Sexy::GameManager* gameManager = getGameManager();
        if (fromScript)
        {
            int xPos = gameManager->GetBoardGemPosX(x);
            int yPos = gameManager->GetBoardGemPosY(y);
            gameManager->TwistGems(true, yPos, xPos);
        }
        else
        {
            gameManager->SetMousePositionOnBoard(x, y);
            gameManager->TwistGems(false, -1, -1);
        }
    }

    void GetHoverPos(int& x, int& y)
    {
        if (!hasGameManager())
            return;

        Sexy::GameManager* gameManager = getGameManager();
        int _x = (gameManager->mouseX - gameManager->GetBoardPosX()) / Sexy::gGridWidth;
        int _y = (gameManager->mouseY - gameManager->GetBoardPosY()) / Sexy::gGridHeight;

        if (_x >= 8 || _x < 0 || _y >= 8 || _y < 0)
        {
            _x = -1;
            _y = -1;
        }

        x = _x;
        y = _y;
    }

    void SetPieceSkin(int x, int y, Sexy::Piece::Skin skin)
    {
        if (!hasGameManager())
            return;

        Sexy::GameManager* gameManager = getGameManager();
        if (x >= gameManager->boardWidth || x < 0 || y >= gameManager->boardHeight || y < 0)
            return;

        Sexy::Piece* piece = GetPiece(x, y);
        if (piece == nullptr)
            return;

        printf_s("Setting Gem at [%d,%d] to %s\n", x, y, GetPieceSkinName(skin).c_str());
        piece->skin = skin;
    }

    Sexy::Piece::Skin GetPieceSkin(int x, int y)
    {
        if (!hasGameManager())
            return Sexy::Piece::Skin::RED;

        Sexy::Piece* piece = GetPiece(x, y);
        if (piece == nullptr)
            return Sexy::Piece::Skin::RED;

        return piece->skin;
    }

    void SetPieceSkinAtHover(Sexy::Piece::Skin skin)
    {
        if (!hasGameManager())
            return;

        int x;
        int y;
        GetHoverPos(x, y);

        SetPieceSkin(x, y, skin);
    }

    void SetPieceSpecial(int x, int y, Sexy::Piece::SpecialType special)
    {
        if (!hasGameManager())
            return;

        Sexy::GameManager* gameManager = getGameManager();
        if (x >= gameManager->boardWidth || x < 0 || y >= gameManager->boardHeight || y < 0)
            return;

        Sexy::Piece* piece = GetPiece(x, y);
        if (piece == nullptr)
            return;

        if (piece->skin == Sexy::Piece::Skin::UNMATCHABLE)
        {
            SetPieceSkin(x, y, Sexy::Piece::Skin::RED);
            SetOldSkin(x, y, Sexy::Piece::Skin::RED);
        }

        printf_s("Setting Gem Special at [%d,%d] to %s\n", x, y, GetPieceSpecialName(special).c_str());
        piece->special = special;
    }

    void SetPieceSpecialAtHover(Sexy::Piece::SpecialType special)
    {
        if (!hasGameManager())
            return;

        int x;
        int y;
        GetHoverPos(x, y);

        Sexy::Piece* piece = GetPiece(x, y);
        if (piece == nullptr)
            return;

        if (piece->skin == Sexy::Piece::Skin::UNMATCHABLE)
        {
            SetPieceSkin(x, y, Sexy::Piece::Skin::RED);
            SetOldSkin(x, y, Sexy::Piece::Skin::RED);
        }

        SetPieceSpecial(x, y, special);
    }

    void ClearBoard()
    {
        if (!hasGameManager())
            return;
        getGameManager()->ClearBoard();
    }

    void FillBoard()
    {
        if (!hasGameManager())
            return;
        getGameManager()->FillInGems(false);
    }

    bool hasGameManager()
    {
        return getGameManager() != nullptr;
    }

    Sexy::GameManager* getGameManager()
    {
        return Sexy::gGameManager;
    }

    bool CheckSpecial(int x, int y, Sexy::Piece::SpecialType special)
    {
        if (!hasGameManager())
            return false;

        Sexy::Piece* piece = GetPiece(x, y);
        if (piece == nullptr)
            return false;

        return piece->CheckSpecial(special);
    }

    Sexy::Piece::SpecialType GetSpecial(int x, int y)
    {
        if (!hasGameManager())
            return Sexy::Piece::NONE;

        Sexy::Piece* piece = GetPiece(x, y);
        if (piece == nullptr)
            return Sexy::Piece::NONE;

        int special = piece->special;

        return static_cast<Sexy::Piece::SpecialType>(special);
    }

    void SetCounter(int x, int y, int counter)
    {
        if (!hasGameManager())
            return;

        Sexy::Piece* piece = GetPiece(x, y);
        if (piece == nullptr)
            return;

        piece->counter = counter;
    }

    int GetCounter(int x, int y)
    {
        if (!hasGameManager())
            return -1;

        Sexy::Piece* piece = GetPiece(x, y);
        if (piece == nullptr)
            return -1;

        return piece->counter;
    }

    void SetPieceType(int x, int y, int type)
    {
        if (!hasGameManager())
            return;

        Sexy::Piece* piece = GetPiece(x, y);
        if (piece == nullptr)
            return;

        piece->pieceType = type;
    }

    int GetPieceType(int x, int y)
    {
        if (!hasGameManager())
            return -1;

        Sexy::Piece* piece = GetPiece(x, y);
        if (piece == nullptr)
            return -1;

        return piece->pieceType;
    }

    void SetOldSkin(int x, int y, Sexy::Piece::Skin skin)
    {
        if (!hasGameManager())
            return;

        Sexy::Piece* piece = GetPiece(x, y);
        if (piece == nullptr)
            return;

        piece->oldSkin = skin;
    }

    Sexy::Piece::Skin GetOldSkin(int x, int y)
    {
        if (!hasGameManager())
            return Sexy::Piece::Skin::RED;

        Sexy::Piece* piece = GetPiece(x, y);
        if (piece == nullptr)
            return Sexy::Piece::Skin::RED;

        return piece->oldSkin;
    }

    void SetPieceMatchable(int x, int y, bool matchable)
    {
        if (!hasGameManager())
            return;

        Sexy::Piece* piece = GetPiece(x, y);
        if (piece == nullptr)
            return;

        piece->matchable = matchable;
    }

    bool GetPieceMatchable(int x, int y)
    {
        if (!hasGameManager())
            return false;

        Sexy::Piece* piece = GetPiece(x, y);
        if (piece == nullptr)
            return false;

        return piece->matchable;
    }

    Sexy::Piece* GetPiece(int x, int y)
    {
        if (!hasGameManager())
            return nullptr;
        if (x >= getGameManager()->boardWidth || x < 0 || y >= getGameManager()->boardHeight || y < 0)
            return nullptr;
        return getGameManager()->boardPieces[x + y * getGameManager()->boardHeight];
    }
}
