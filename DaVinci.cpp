#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

enum class TileColor { WHITE, BLACK };
enum class TileStatus { HIDDEN, REVEALED };

struct Tile {
    int number;
    TileColor color;
    TileStatus status;
};

class Player {
private:
    Tile tiles[13];
    int numTiles = 0;
public:
    void addTile(Tile tile) {
        tiles[numTiles] = tile;
        numTiles++;
    }

    Tile& getTile(int index) {
        if (index < numTiles) return tiles[index];
        else {
            cerr << "out of tile index!" << endl;
            exit(1);
        }
    }

    int getNumTiles() {
        return numTiles;
    }

    void displayTiles(ofstream& ofs) {

        /* DO NOT MODIFY the output format! */

        sortTiles();
        for (size_t i = 0; i < numTiles; i++) {
            ofs << tiles[i].number;
            ofs << (tiles[i].color == TileColor::WHITE ? "w" : "b") << "(";
            ofs << (tiles[i].status == TileStatus::HIDDEN ? "H" : "R") << ")";
            if (i != numTiles - 1) ofs << ", ";
        }
    }

    bool isTileRevealed(int index) {
        if (index < numTiles) return tiles[index].status == TileStatus::REVEALED;
        else {
            cerr << "Out of tile index!" << endl;
            exit(1);
        }
    }

    void sortTiles() {

        /* TODO */
        Tile temp;
        for (int i = 0; i < numTiles - 1; i++)
        {
            for (int j = 0; j < numTiles - i - 1; j++)
            {
                if (tiles[j].number > tiles[j + 1].number)
                {
                    temp = tiles[j];
                    tiles[j] = tiles[j + 1];
                    tiles[j + 1] = temp;
                }
                else if (tiles[j].number == tiles[j + 1].number)
                {
                    if (tiles[j].color == TileColor::WHITE)
                    {
                        temp = tiles[j];
                        tiles[j] = tiles[j + 1];
                        tiles[j + 1] = temp;
                    }
                }
            }
        }
    }
    bool allTilesRevealed() {

        /* TODO: return true if one's tiles are all revealed */
        for (int i = 0; i < numTiles; i++)
        {
            if (!isTileRevealed(i))
            {
                return false;
            }
        }
        return true;
    }
};

class DaVinciCodeGame {
private:
    Tile centerTiles[24];
    Player players[4];
    int numCenter = 24;
    int numPlayers;
    int currentPlayerIndex;

public:
    DaVinciCodeGame(int num) {
        numPlayers = num;
        currentPlayerIndex = 0;
        initialize();
        initializeTiles();
        initializePlayerTiles();
    }

    void initialize() {

        /* If you need, initialize any variables. */
        for (int i = 0; i < numCenter; i++)
        {
            centerTiles[i].status = TileStatus::HIDDEN;
        }
    }

    Tile popCenter() {
        if (numCenter < 0) {
            cerr << "Out of center tile index!" << endl;
            exit(1);
        }
        Tile temp;
        temp = centerTiles[24 - numCenter];
        return temp;
        /* TODO: draw one tile from center tiles */

    }

    void initializeTiles() {

        /* TODO: initialize tiles with input.txt file */
        ifstream ifs;
        char c[4];
        int i = 0;
        ifs.open("input.txt");
        if (!ifs.is_open()) {
            cerr << "Input File error!" << endl;
            exit(1);
        }
        while (ifs >> c)
        {
            if (strlen(c) == 3)
            {
                centerTiles[i].number = (c[0] - '0') * 10 + c[1] - '0';
                if (c[2] == 'b')
                {
                    centerTiles[i].color = TileColor::BLACK;
                }
                else
                {
                    centerTiles[i].color = TileColor::WHITE;
                }
                i++;
            }
            else if (strlen(c) == 2)
            {
                centerTiles[i].number = c[0] - '0';
                if (c[1] == 'b')
                {
                    centerTiles[i].color = TileColor::BLACK;
                }
                else
                {
                    centerTiles[i].color = TileColor::WHITE;
                }
                i++;
            }
        }
        ifs.close();
    }

    void initializePlayerTiles() {

        /* TODO: make each player draw 4 tiles */
        for (int i = 0; i < numPlayers; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                players[i].addTile(popCenter());
                numCenter--;
            }
            players[i].sortTiles();
        }
    }

    void displayPlayersTiles(ofstream& ofs) {

        /* DO NOT MODIFY the output format! */

        for (int i = 0; i < numPlayers; ++i) {
            ofs << "Player " << i + 1 << "'s Tile : [ ";
            players[i].displayTiles(ofs);
            ofs << " ]";
            ofs << endl;
        }
    }

    bool makeGuess( /* TODO */int targetplayerindex, int& targettileindex, int& guessednumber) {
        /* TODO: check and return if the guess was correct */
        if (players[targetplayerindex].getTile(targettileindex).number == guessednumber)
        {
            players[targetplayerindex].getTile(targettileindex).status = TileStatus::REVEALED;
            return true;
        }
        else
        {
            return false;
        }
        /* if the guess was correct, target tile should be revealed */
    }
    
    void play() {
        ofstream ofs;
        TileColor clue_color;
        int clue_number;
        bool turnContinue = false;
        Tile memory[4];
        int guessmemory[4];
        int cnt[4] = { 0 };

        ofs.open("output.txt");
        if (!ofs.is_open()) {
            cerr << "Outout File error!" << endl;
            exit(1);
        }

        /* DO NOT MODIFY the output format! */
        ofs << "Game Start!" << endl;
        Tile drawtile = popCenter();

        while (true) {
            displayPlayersTiles(ofs);

            // Do not modify the output format
            ofs << "--------------------------------------------------------------------------------------------------" << endl;
            ofs << "Player " << currentPlayerIndex + 1 << "'s Turn: " << endl;
            Player& currentPlayer = players[currentPlayerIndex];

            if (!currentPlayer.allTilesRevealed() && !turnContinue) {
                /* TODO: make currentPlayer recieve one clue tile */
                drawtile = popCenter();
                currentPlayer.addTile(drawtile);
                clue_color = drawtile.color;
                clue_number = drawtile.number;
                numCenter--;
                /* DO NOT MODIFY the output format! */

                ofs << "Clue tile received: " << clue_number << (clue_color == TileColor::WHITE ? "w" : "b") << endl;
            }

            int targetPlayerIndex, targetTileIndex, guessedNumber = 0;
            targetPlayerIndex = (currentPlayerIndex + 1) % numPlayers;
            Player& targetPlayer = players[targetPlayerIndex];
            /* TODO: guess number of target tile */
            targetTileIndex = 0;
            while (1)
            {
                if (targetPlayer.isTileRevealed(targetTileIndex))
                {
                    targetTileIndex++;
                }
                else break;
            }
            if (cnt[targetPlayerIndex] != 0)
            {
                guessedNumber = guessmemory[targetPlayerIndex];
            }
            if (targetTileIndex > 0 && targetPlayer.getTile(targetTileIndex).color == TileColor::BLACK)
            {
                guessedNumber = targetPlayer.getTile(targetTileIndex - 1).number + 1;
            }
            else if (targetTileIndex > 0 && targetPlayer.getTile(targetTileIndex).color == TileColor::WHITE)
            {
                if (targetPlayer.getTile(targetTileIndex - 1).color == TileColor::BLACK)
                {
                    guessedNumber = targetPlayer.getTile(targetTileIndex - 1).number;
                }
                else
                {
                    guessedNumber = targetPlayer.getTile(targetTileIndex - 1).number + 1;
                }
            }
            for (int i = 0; i < currentPlayer.getNumTiles(); i++)
            {
                if (guessedNumber == currentPlayer.getTile(i).number && targetPlayer.getTile(targetTileIndex).color == currentPlayer.getTile(i).color)
                {
                    guessedNumber++;
                }
            }
            // 동일한 타일을 동일한 숫자로 예측하면 +1 해야한다
            if (cnt[targetPlayerIndex] != 0)
            {
                if (memory[targetPlayerIndex].number == targetPlayer.getTile(targetTileIndex).number
                    && memory[targetPlayerIndex].color == targetPlayer.getTile(targetTileIndex).color) // 이전 예측과 지금 예측 대상이 같다면
                {
                    if (guessmemory[targetPlayerIndex] == guessedNumber) // 이전 예측과 지금 예측 숫자가 같다면
                    {
                        guessedNumber++;
                    }
                }
            }
            memory[targetPlayerIndex] = targetPlayer.getTile(targetTileIndex);
            guessmemory[targetPlayerIndex] = guessedNumber;
            cnt[targetPlayerIndex]++;
            /* DO NOT MODIFY the output format! */

            ofs << endl << "Target index is: " << targetTileIndex + 1 << ", Guessed number is: " << guessedNumber << endl;

            if (makeGuess( /* TODO */targetPlayerIndex, targetTileIndex, guessedNumber)) {

                // Do not modify the output format
                if (targetPlayer.allTilesRevealed()) {
                    ofs << "\nCorrect guess!\n";
                    ofs << "Player " << targetPlayerIndex + 1 << " has lost!" << endl;
                    ofs << "Player " << currentPlayerIndex + 1 << " is the winner!" << endl;
                    return;
                }
                ofs << "Correct guess! Player " << currentPlayerIndex + 1 << " gets another turn. \n" << endl;
                turnContinue = true;
            }
            else {

                /* DO NOT MODIFY the output format! */

                ofs << "Incorrect guess! Player " << currentPlayerIndex + 1 << " reveals a clue tile. \n" << endl;
                if (!currentPlayer.allTilesRevealed()) {

                    /* TODO: reveal one tile of currentPlayer */
                    for (int i = 0; i < currentPlayer.getNumTiles(); i++)
                    {
                        if (currentPlayer.getTile(i).number == drawtile.number && currentPlayer.getTile(i).color == drawtile.color)
                        {
                            currentPlayer.getTile(i).status = TileStatus::REVEALED;
                        }
                    }
                }
                turnContinue = false;
            }

            if (targetPlayer.allTilesRevealed()) {

                /* DO NOT MODIFY the output format! */

                ofs << "Player " << targetPlayerIndex + 1 << " has lost!" << endl;
                ofs << "Player " << currentPlayerIndex + 1 << " is the winner!" << endl;
                return;
            }

            if (!turnContinue) {
                currentPlayerIndex = (currentPlayerIndex + 1) % numPlayers;
            }
        }
        ofs.close();
    }
};

int main() {
    DaVinciCodeGame game(2);
    game.play();
    return 0;
}