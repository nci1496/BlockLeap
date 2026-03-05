#include "Renderer.h"

void Renderer::draw(sf::RenderWindow& window,const RenderState& state)
{


    if (!state.gameOver)
        window.setTitle(state.redTurn ? "Red Turn" : "Blue Turn");
    else
        window.setTitle("Game Over");

    window.clear();

    if (state.gameOver)//这样处理，确保游戏结束后，不屏闪,（但还是状态转化更好）
    {
        sf::Text text;
        text.setFont(*state.font);
        text.setCharacterSize(40);
        text.setFillColor(sf::Color::Yellow);
        text.setString(state.winner == RED_SIDE ? "RED WINS" : "BLUE WINS");
        text.setPosition(150, 300);

        window.draw(text);
        window.display();
        return;
    }
    else {
        //画血条
        for (int i = 0; i < state.redHP; i++)
        {
            sf::RectangleShape hpBar(sf::Vector2f(20.f, 20.f));
            hpBar.setFillColor(sf::Color::Red);
            hpBar.setPosition(10.f + i * 25.f, 15.f);
            window.draw(hpBar);
        }

        for (int i = 0; i < state.blueHP; i++)
        {
            sf::RectangleShape hpBar(sf::Vector2f(20.f, 20.f));
            hpBar.setFillColor(sf::Color::Blue);
            hpBar.setPosition(300.f + i * 25.f, 15.f);
            window.draw(hpBar);
        }


        for (int i = 0; i < state.board->SIZE; i++)
        {
            for (int j = 0; j < state.board->SIZE; j++)
            {
                sf::RectangleShape cell(sf::Vector2f(state.board->CELL, state.board->CELL));
                cell.setPosition(j * state.board->CELL, i * state.board->CELL+ state.board->topOffset);

                if ((i + j) % 2 == 0)
                    cell.setFillColor(sf::Color(180, 180, 180));
                else
                    cell.setFillColor(sf::Color(120, 120, 120));

                window.draw(cell);



                if (state.board->grid[i][j] != EMPTY)
                {
                    sf::CircleShape piece(state.board->CELL / 2 - 10);
                    piece.setPosition(j * state.board->CELL + 10, i * state.board->CELL + 10+state.board->topOffset);

                    if (state.board->grid[i][j] == RED)
                        piece.setFillColor(sf::Color::Red);
                    else if (state.board->grid[i][j] == BLUE)
                        piece.setFillColor(sf::Color::Blue);
                    else if (state.board->grid[i][j] == RED_TRACE)
                        piece.setFillColor(sf::Color(255, 150, 150));
                    else if (state.board->grid[i][j] == BLUE_TRACE)
                        piece.setFillColor(sf::Color(150, 150, 255));

                    window.draw(piece);
                    //画选中边框
                    if (state.selected && ((state.redTurn && state.board->grid[i][j] == RED) || (!state.redTurn && state.board->grid[i][j] == BLUE)))
                    {
                        sf::CircleShape outline(state.board->CELL / 2 - 4);
                        outline.setPosition(j * state.board->CELL + 4, i * state.board->CELL + 4+state.board->topOffset);
                        outline.setFillColor(sf::Color::Transparent);
                        outline.setOutlineThickness(4);
                        outline.setOutlineColor(sf::Color::White);

                        window.draw(outline);
                    }
                }

            }
        }
        // 画高亮
        for (auto& h : *state.highlights)
        {
            sf::CircleShape mark(state.board->CELL / 6);
            mark.setFillColor(sf::Color::White);
            mark.setPosition(
                h.y * state.board->CELL + state.board->CELL / 2 - state.board->CELL / 12,
                h.x * state.board->CELL + state.board->CELL / 2 - state.board->CELL / 12 + state.board->topOffset
            );
            window.draw(mark);
        }
    }

    window.display();
}
