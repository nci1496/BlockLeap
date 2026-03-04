#include "Renderer.h"

void Renderer::draw(sf::RenderWindow& window, const Board& board, bool redTurn, bool gameOver, Piece winner, const std::vector<sf::Vector2i>& highlights,const bool &selected,const sf::Font&font)
{


    if (!gameOver)
        window.setTitle(redTurn ? "Red Turn" : "Blue Turn");
    else
        window.setTitle("Game Over");

    window.clear();



    if (gameOver)//这样处理，确保游戏结束后，不屏闪,（但还是状态转化更好）
    {
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(40);
        text.setFillColor(sf::Color::Yellow);
        text.setString(winner == RED ? "RED WINS" : "BLUE WINS");
        text.setPosition(150, 300);

        window.draw(text);
        window.display();
        return;
    }
    else {

        for (int i = 0; i < board.SIZE; i++)
        {
            for (int j = 0; j < board.SIZE; j++)
            {
                sf::RectangleShape cell(sf::Vector2f(board.CELL, board.CELL));
                cell.setPosition(j * board.CELL, i * board.CELL);

                if ((i + j) % 2 == 0)
                    cell.setFillColor(sf::Color(180, 180, 180));
                else
                    cell.setFillColor(sf::Color(120, 120, 120));

                window.draw(cell);





                // 画高亮
                for (auto& h : highlights)
                {
                    sf::CircleShape mark(board.CELL / 6);
                    mark.setFillColor(sf::Color::Green);
                    mark.setPosition(
                        h.y * board.CELL + board.CELL / 2 - board.CELL / 12,
                        h.x * board.CELL + board.CELL / 2 - board.CELL / 12
                    );
                    window.draw(mark);
                }

                if (board.grid[i][j] != EMPTY)
                {
                    sf::CircleShape piece(board.CELL / 2 - 10);
                    piece.setPosition(j * board.CELL + 10, i * board.CELL + 10);

                    if (board.grid[i][j] == RED)
                        piece.setFillColor(sf::Color::Red);
                    else if (board.grid[i][j] == BLUE)
                        piece.setFillColor(sf::Color::Blue);
                    else if (board.grid[i][j] == RED_TRACE)
                        piece.setFillColor(sf::Color(255, 150, 150));
                    else if (board.grid[i][j] == BLUE_TRACE)
                        piece.setFillColor(sf::Color(150, 150, 255));

                    window.draw(piece);
                    //画选中边框
                    if (selected && ((redTurn && board.grid[i][j] == RED) || (!redTurn && board.grid[i][j] == BLUE)))
                    {
                        sf::CircleShape outline(board.CELL / 2 - 4);
                        outline.setPosition(j * board.CELL + 4, i * board.CELL + 4);
                        outline.setFillColor(sf::Color::Transparent);
                        outline.setOutlineThickness(4);
                        outline.setOutlineColor(sf::Color::White);



                        window.draw(outline);
                    }
                }

            }
        }
    }

    window.display();



}
