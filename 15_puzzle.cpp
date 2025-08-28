#include "diy.h"
#include "random_mt.h"
#include <vector>
#include <array>
#include <iomanip>

// we created 3 classes and 1 namespace here to achieve the functions
// of 15-puzzle and each of them should be unique and focus on performing one task well
// so that our program will be reusable and maintainable

namespace Data
{
    enum Directions
    {
        up,
        down,
        left,
        right,
        max_dir
    };

    struct Point
    {
        int x{};
        int y{};

        explicit operator std::size_t() const {
            return static_cast<std::size_t>((x - 1) * 4 + (y - 1));
        }
    };

    std::ostream& operator<<(std::ostream& out, const Point& p)
    {
        return out << '(' << p.x << ',' << p.y << ')';
    }

    Point index2Point(const std::size_t index)
    {
        return {static_cast<int>(index) / 4 + 1, static_cast<int>(index) % 4 + 1};
    }

    std::vector<Point> generateLocations() // (1,1) ~ (4,4)
    {
        std::vector<Point> temp{};
        temp.reserve(16);
        for (int i{1}; i < 5; ++i)
        {
            for (int j{1}; j < 5; ++j)
                temp.emplace_back(Point{i, j});
        }
        // std::shuffle(temp.begin(), temp.end(), Random::mt);
        return temp;
    }
    std::vector<int> generateRandomSeq()
    {
        std::vector<int> temp{};
        temp.reserve(16);
        for (int i{0}; i < 16; ++i)
        {
            temp.emplace_back(i);
        }
        std::shuffle(temp.begin(), temp.end(), Random::mt);
        return temp;
    }
}

Data::Directions getDirection()
{
    for (;;)
    {
        std::cout << "Please Press One Button in <W>,<A>,<S>,<D> for choosing a Direction: ";
        char temp{getCharacter()};
        temp = static_cast<char>(tolower(static_cast<unsigned int>(temp)));
        if(temp != 'w' && temp != 'a' && temp != 's' && temp != 'd')
            std::cout << "Your Enter is Invalid.\n";
        else
        {
            switch(temp)
            {
            case 'w':
                return Data::up;
            case 'a':
                return Data::left;
            case 's':
                return Data::down;
            case 'd':
                return Data::right;
            default:
                std::cerr << "Fatal Error -2\n";
                std::exit(-2);
            }
        }
    }
}


class BoardManagement
{
private:
    // std::vector<int> m_tiles{Data::generateRandomSeq()}; // this may cause the problem has no answer
    static const int m_random_steps{5};
    std::vector<int> m_tiles{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};
    static constexpr std::array m_win{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};
public:
    const std::vector<int> &getBoard() const { return m_tiles; } // for viewing
    std::vector<int> &getBoard() { return m_tiles; } // for updating the board
    bool check_win() const; // The condition of Ending Game (Management)
    Data::Point getZeroPosition() const;
    void randomInitial(const int random_steps); // To get a Random Matrix, we just need to shuffle the array.
};

void BoardManagement::randomInitial(const int random_steps = m_random_steps)
{
    std::size_t cur_index{15};
    Data::Directions dir{};
    for (int i{0}; i < random_steps;)
    {
        dir = static_cast<Data::Directions>(Random::get<int>(0, Data::max_dir-1));
        switch (dir)
        {
        case Data::down:
            if(cur_index > 3)
            {
                ++i; // valid movement
                std::cout << "Random towards to Down.....\n";
                std::swap(m_tiles[cur_index], m_tiles[cur_index - 4]); // move
                cur_index -= 4; // update the index of 0
            }
            break;
        case Data::right:
            if(cur_index != 0 && cur_index != 4 && cur_index != 8 && cur_index != 12)
            {
                ++i;
                std::cout << "Random towards to Right.....\n";
                std::swap(m_tiles[cur_index], m_tiles[cur_index - 1]);
                cur_index -= 1;
            }
            break;
        case Data::up:
            if(cur_index < 12)
            {
                ++i;
                std::cout << "Random towards to Up.....\n";
                std::swap(m_tiles[cur_index], m_tiles[cur_index + 4]);
                cur_index += 4;
            }
            break;
        case Data::left:
            if(cur_index != 3 && cur_index != 7 && cur_index != 11 && cur_index != 15)
            {
                ++i;
                std::cout << "Random towards to Left.....\n";
                std::swap(m_tiles[cur_index], m_tiles[cur_index + 1]);
                cur_index += 1;
            }
            break;
        default:
            std::cerr << "Fatal Error -1\n";
            std::exit(-1);
        }
    }
}

Data::Point BoardManagement::getZeroPosition() const // find where the `0` is
{
    for (size_t i = 0; i < 16; ++i)
    {
        if(m_tiles[i] == 0)
            return Data::index2Point(i);
    }
    return {};
}

bool BoardManagement::check_win() const
{
    for (size_t i = 0; i < 16; ++i)
    {
        if(m_tiles[i] != m_win[i])
            return false;
    }
    return true;
}

class BoardDisplay
{
private:
    std::vector<Data::Point> m_locations{Data::generateLocations()}; // generate coordinates
public:
    void display(const BoardManagement& board) const; // display the matrix
};

void BoardDisplay::display(const BoardManagement& board) const//tiles[static_cast<std::size_t>((coordnate.x - 1) * 4 + (coordnate.y - 1))]
{
    auto& tiles{board.getBoard()}; // read the board data
    for(const auto& coordnate:m_locations)
    {
        std::cout << std::left << std::setw(4) << tiles[static_cast<std::size_t>(coordnate)]; // print the matrix from (1,1) left top to (4,4) right bottom
        if(coordnate.y == 4)                                                                  // based on the data we just read
            std::cout << '\n'; // 4x4
    }
}

class BoardUpdate // handle the user's input
{
private:
    Data::Point m_currentPositon{};
    std::size_t m_cur_index{};
    Data::Directions m_user_cmd{};
public:
    BoardUpdate(const BoardManagement &board)
        : m_currentPositon{board.getZeroPosition()}, // get the blank's current position (coordiante)
          m_cur_index{static_cast<std::size_t>(m_currentPositon)}, // the blank's index in the board data
          m_user_cmd{getDirection()} // get user's input for updating the board (enumerator)
    {}
    void update(BoardManagement& board); // execution of update the board
    void getCurrentPosition() const { std::cout << m_currentPositon; } // print the blank's current position
};

void BoardUpdate::update(BoardManagement& board)
{
    std::vector<int>& manipulate{board.getBoard()};
    switch (m_user_cmd)
    {
    case Data::down: // blank goes up, pull the number down
        if(m_cur_index > 3) // not at the top
            std::swap(manipulate[m_cur_index], manipulate[m_cur_index - 4]);
        // otherwise, we just do noting
        break;
    case Data::right: // goes left, pull the number right
        if(m_cur_index != 0 && m_cur_index != 4 && m_cur_index != 8 && m_cur_index != 12)
            std::swap(manipulate[m_cur_index], manipulate[m_cur_index - 1]);
        break;
    case Data::up: // goes down, lift the number(below)
        if(m_cur_index < 12)
            std::swap(manipulate[m_cur_index], manipulate[m_cur_index + 4]);
        break;
    case Data::left: // goes right, pull the number left
        if(m_cur_index != 3 && m_cur_index != 7 && m_cur_index != 11 && m_cur_index != 15)
            std::swap(manipulate[m_cur_index], manipulate[m_cur_index + 1]);
        break;
    default:
        std::cerr << "Fatal Error -1\n";
        std::exit(-1);
    }
}

void gameLoop(BoardManagement& board)
{
    std::cout << "Welcome to 15-Puzzle, you just need to move the `0` to the bottom right corner\n"
              << "The remaining numbers are sorted in ascending order from top left to bottom right.\n";
    BoardDisplay display{};
    for (;!board.check_win();)
    {
        std::cout << "+-------------------+\n";
        display.display(board);
        std::cout << "+-------------------+\n";
        BoardUpdate status{board};
        status.update(board);
    }
    std::cout << "***********************\n";
    display.display(board);
    std::cout << "***********************\n";
    std::cout << "Congratulations! You beat the Game!\n";
}

int main()
{
    BoardManagement board{};
    board.randomInitial();
    gameLoop(board);


    return 0;
}
