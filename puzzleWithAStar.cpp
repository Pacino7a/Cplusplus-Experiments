#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <iomanip>
#include <unordered_set>
#include <memory>
#include "random_mt.h"
// A* Algorithm for 8-Puzzle

namespace std
{
    template<>
    struct hash<std::pair<std::size_t,std::size_t>> // <<<----- for hash
    {
        std::size_t operator()(const std::pair<std::size_t,std::size_t>& p) const noexcept
        {
            return std::hash<std::size_t>{}(p.first) ^ (std::hash<std::size_t>{}(p.second) << 1);
        }
    };
}

// struct pair_hash 
// {
//     template<typename T1, typename T2>
//     std::size_t operator()(const std::pair<T1, T2>& p) const {
//         return std::hash<T1>{}(p.first) ^ (std::hash<T2>{}(p.second) << 1);
//     }
// };

namespace Data
{
    enum Directions
    {
        up,
        down,
        left,
        right,
        maxType
    };
}

class Board
{
public:
    explicit Board(std::size_t size)
     : m_size{size}, m_valueMap{}
    {
        for(std::size_t i{1}; i <= size; ++i)
        {
            for(std::size_t j{1}; j <= size; ++j)
            {
                if(i ==size && j == size) break;
                m_valueMap[{i,j}] = static_cast<int>((i - 1) * size + j);
            }
        }
        m_valueMap[{m_size, m_size}] = 0;
        m_blank = shuffle_board();
    }
    std::size_t getSize() const { return m_size; }
    const std::unordered_map<std::pair<std::size_t, std::size_t>, int> &getMap() const { return m_valueMap; }
    std::unordered_map<std::pair<std::size_t, std::size_t>, int> &getMap() { return m_valueMap; }
    std::pair<std::size_t, std::size_t>& getBlankPosition() { return m_blank; }
    const std::pair<std::size_t, std::size_t>& getBlankPosition() const { return m_blank; }


private:
    constexpr static int m_randomSteps{50};
    std::size_t m_size{};
    std::unordered_map<std::pair<std::size_t,std::size_t>, int> m_valueMap;
    std::pair<std::size_t, std::size_t> m_blank{};
    std::pair<std::size_t, std::size_t> shuffle_board();
};

class BoardStatus
{
public:
    explicit BoardStatus(const Board& board)
        : m_board{board}, m_size{board.getSize()}, m_blank{board.getBlankPosition()}
    {}
    void display() const;
    bool isWin() const;
    std::vector<Board> getNeighbors() const;

private:
    const Board& m_board;
    const std::size_t m_size{};
    const std::pair<std::size_t, std::size_t>& m_blank;
};

class UpdateBoard
{
public:
    explicit UpdateBoard(Board& board)
        : m_board{board}
    {}
    bool activate(Data::Directions dir);

private:
    Board &m_board;
    Data::Directions m_dirction{};
};

std::pair<std::size_t, std::size_t> Board::shuffle_board()
{
    std::pair blankPosition{m_size, m_size};
    std::pair<std::size_t, std::size_t> toMove{blankPosition};
    for (int i{}; i < m_randomSteps;)
    {
        int randomGen{Random::get(1, 100)};
        if(randomGen <= 25 && blankPosition.second != 1) // left (make sure blank is not on the edge)
        {
            toMove = {blankPosition.first, blankPosition.second - 1};
            // std::cout << "Goes left\n";
            ++i;
        }
        else if(randomGen <= 50 && blankPosition.second != m_size) // right
        {
            toMove = {blankPosition.first, blankPosition.second + 1};
            // std::cout << "Goes right\n";
            ++i;
        }
        else if(randomGen <= 75 && blankPosition.first != 1) // up
        {
            toMove = {blankPosition.first - 1, blankPosition.second};
            // std::cout << "Goes up\n";
            ++i;
        }
        else if(randomGen <= 100 && blankPosition.first != m_size) // down
        {
            toMove = {blankPosition.first + 1, blankPosition.second};
            // std::cout << "Goes Down\n";
            ++i;
        }
        if(toMove == blankPosition) continue;
        std::swap(m_valueMap[toMove], m_valueMap[blankPosition]);
        blankPosition = toMove;
    }
    return blankPosition;
}

void BoardStatus::display() const
{
    auto& map{m_board.getMap()};
    auto size{m_board.getSize()};
    std::cout << "----- " << size*size-1 << " Puzzle -----\n";
    for(std::size_t i{1}; i <= size; ++i)
    {
        for(std::size_t j{1}; j <= size; ++j)
            std::cout << std::right << std::setw(4) << map.at({i,j}) << ' ';
        std::cout << '\n';
    }
    std::cout << "--------------------\n";
}

bool BoardStatus::isWin() const
{
    auto& map{m_board.getMap()};
    auto size{m_board.getSize()};
    int expect{};
    for(std::size_t i{1}; i <= size; ++i)
    {
        for(std::size_t j{1}; j <= size; ++j)
        {
            if(i != size || j!= size)
                expect = static_cast<int>((i - 1) * size + j);
            else
                expect = 0;
            if(expect != map.at({i,j}))
                return false;
        }
    }
    return true;
}

std::vector<Board> BoardStatus::getNeighbors() const
{
    std::vector<Board> neighbors{};
    auto [b_first, b_second] = m_blank;
    // const int dirs[4][2]{{0, -1}, {0, 1}, {-1, 0}, {1, 0}}; // left, right, down, up
    constexpr std::array<std::pair<int, int>, 4> stlDirs{{{0, -1}, {0, 1}, {-1, 0}, {1, 0}}};
    // for(auto [delta_first, delta_second]:dirs)
    for(auto [deltaFirst, deltaSecond]:stlDirs)
    {
        auto next_first  = static_cast<std::size_t>(static_cast<int>(b_first) + deltaFirst);
        auto next_second = static_cast<std::size_t>(static_cast<int>(b_second) + deltaSecond);
        if(next_first >= 1 && next_first <= m_size && next_second >= 1 && next_second <= m_size) // make sure all movements are valid
        {
            Board copy{m_board}; // create a copy and refresh each loop to find neighbor states
            std::swap(copy.getMap()[m_blank], copy.getMap()[{next_first, next_second}]); // make the movement
            copy.getBlankPosition() = {next_first, next_second}; // update the blank's position
            neighbors.emplace_back(copy);
        }
    }

    return neighbors;
}

bool UpdateBoard::activate(Data::Directions dir)
{
    auto& map{m_board.getMap()};
    auto& blank{m_board.getBlankPosition()};
    auto toMove{blank};
    switch (dir)
    {
    case Data::left:
        if(blank.second != 1)
            toMove = {blank.first, blank.second - 1};
        break;
    case Data::right:
        if(blank.second != m_board.getSize())
            toMove = {blank.first, blank.second + 1};
        break;
    case Data::up:
        if(blank.first != 1)
            toMove = {blank.first-1, blank.second};
        break;
    case Data::down:
        if(blank.first != m_board.getSize())
            toMove = {blank.first + 1, blank.second};
        break;
    default:
        std::cerr << "Fatal Error -1!\n";
        std::exit(-1);
    }
    if(toMove != blank)
    {
        std::swap(map[blank], map[toMove]);
        blank = toMove;
        return true;
    }
    return false;
}

char getCharacter()
{
    for (char user_char{};;)
    {
        std::cin >> user_char;

        if (!std::cin) // fail to extract a character
        {
            if(std::cin.eof())
                std::exit(0);

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Oops! your input is invalid, Please try again.\n";
            continue;
        }
        if(!std::cin.eof() && std::cin.peek() != '\n')
        {
            std::string drop{};
            std::cin >> drop;
            std::cout << "What does " << user_char << drop << " means? Please Try again: ";
            continue;
        }
        return user_char;
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

void gameLoop(Board& board)
{
    std::size_t moves{};
    BoardStatus status{board};
    UpdateBoard update{board};
    for (;!status.isWin();)
    {
        status.display();
        if(update.activate(getDirection()))
            ++moves;
    }
    status.display();
    std::cout << "Congratulations! You have beat the Game!\n"
              << "Total Moves: " << moves << '\n';
}

struct Node 
{
    Board board;   // 当前拼图状态
    int g;         // 起点到当前状态的路径长度
    int h;         // 启发式估价
    std::shared_ptr<Node> parent; // 回溯路径用

    int f() const { return g + h; } // cost
    
    // 重载比较符 用于 priority_queue（小顶堆）
    bool operator>(const Node &other) const { return f() > other.f(); }
};

int manhattanDistance(const Board& board) // total distance of every valid block to reach its correct position
{
    int dist = 0;
    auto& map = board.getMap();
    std::size_t size = board.getSize();

    for (const auto& [pos, val] : map)
    {
        if (val == 0) continue; // blank is not a valid block, so we ignore it
        std::size_t correctRow = static_cast<std::size_t>((val - 1)) / size + 1; // value -> position (Inverse Solution)
        std::size_t correctCol = static_cast<std::size_t>((val - 1)) % size + 1;
        dist += std::abs((int)pos.first - (int)correctRow) +
                std::abs((int)pos.second - (int)correctCol);
    }

    return dist;
}

int misplacedTilesDistance(const Board& board)
{
    int misplaced = 0;
    auto& map = board.getMap();
    std::size_t size = board.getSize();

    for (const auto& [pos, val] : map)
    {
        if (val == 0) continue;
        std::size_t correctRow = static_cast<std::size_t>((val - 1)) / size + 1; // value -> position (Inverse Solution)
        std::size_t correctCol = static_cast<std::size_t>((val - 1)) % size + 1;
        if(pos.first != correctRow || pos.second != correctCol)
            ++misplaced;
    }

    return misplaced;
}

std::string serialize(const Board& board)
{
    std::string s;
    auto& map = board.getMap();
    const auto size{board.getSize()};
    for (std::size_t i = 1; i <= size; ++i)
        for (std::size_t j = 1; j <= size; ++j)
            s += std::to_string(map.at({i, j})) + ",";
    return s;
}

std::vector<Board> algorithm_AStar(const Board& initialBoard)
{
    using NodePtr = std::shared_ptr<Node>;
    auto cmp = [](const NodePtr &a, const NodePtr &b)
    {
        return *a > *b;// put `a` to the LAST then `b` to the TOP. 
        //        ^(Judgement Basis)      // In this case, override of std::greater,
                                          // the greater one will be put on the LASTThis basis will form a minHeap

        // (Reversed)
        // when you override a SORT, you may also write a lambda. put `a` front then `b` behind
        // when you write a > b, Judgement Basis is `>`, you will put the greater one ahead and the smaller one behind
        // at the end, we get a Descending Array
    };
    // openSet is a minHeap (the bigger ones are sinked to the bottom)
    std::priority_queue<NodePtr, std::vector<NodePtr>, decltype(cmp)> openSet(cmp); // we use lambda to sink the costy movements (replace the std::greater())
    std::unordered_set<std::string> visited{};

    NodePtr startNode{std::make_shared<Node>(Node{initialBoard, 0, manhattanDistance(initialBoard), nullptr})};
    openSet.push(startNode);

    for (;!openSet.empty();)
    {
        NodePtr currentNode{openSet.top()}; // Pop the Node with the minimum cost
        openSet.pop();

        BoardStatus currentStatus{currentNode->board}; // initial the Status
        if(currentStatus.isWin()) // if we have reached the END
        {
            std::vector<Board> path{};
            while(currentNode)
            {
                path.emplace_back(currentNode->board); // save the result (compeleted status)
                currentNode = currentNode->parent; // and Backtracking
            }
            std::reverse(path.begin(), path.end()); // restore the right order of the path
            return path;
        }

        // if not win, mark this status
        std::string boardKey{serialize(currentNode->board)}; // serialize the board for specification (marking visited)
        if(visited.contains(boardKey)) continue; // we don't Backward
        visited.insert(boardKey);

        // and make the possible next movements and push their package(Node) of cost and state into the Priority Queue
        for(const auto& neighbor : currentStatus.getNeighbors())
        {
            std::string neighborKey{serialize(neighbor)}; // No turning back (May Redundancy)
            if(visited.contains(neighborKey)) continue;

            // insert all next possible movements into the queue and increase g() for one(one step from current to neighbor),
            // and calculate h() (future cost stands on this neighbor),
            // make `currentNode` as their `parent`
            NodePtr next{std::make_shared<Node>(Node{neighbor, (currentNode->g + 1), manhattanDistance(neighbor), currentNode})};
            openSet.push(next);
        }
    }
    return {}; // if there is no path to return, this problem has NO SOLUTION.
}


int main()
{
    Board board{4};
    // gameLoop(board); // manually

    const std::vector path{algorithm_AStar(board)}; // automatically
    if(!path.empty())
        for(const auto& step:path)
        {
            BoardStatus status{step};
            status.display();
        }
    else
        std::cout << "Sorry, We can't find fit solution for this problem.\n";

    return 0;
}
