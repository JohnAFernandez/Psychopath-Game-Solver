
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>


struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2> &pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

enum class return_codes {
    NO_PROBLEMS = 0,
    NO_VALID_START,
    PLAYER_START_OUT_OF_PLAY_AREA,
    NO_EXIT,
    NUM_ENTIRES
};

enum class block_types {
    EMPTY,
    UNMOVABLE,
    MOVABLE,
    PLAYER_START,
    EXIT,
    DIRECTIONAL,
    INVALID,
    NUM_ENTIRES
};

enum class direction_list {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NUM_ENTIRES
};

typedef std::pair<int, int> movable;

typedef 

class grid {
    int width;
    int height;
    std::pair<int, int> player_start;
    std::vector<std::pair<int,int>> doubled;

    bool valid_width(int test){
        if (test < 0 || test >= width) {
            return false;
        }

        return true;
    }

    bool valid_height(int test){
        if (test < 0 || test >= height) {
            return false;
        }

        return true;
    }

    

public:
    std::vector<std::vector<block_types>> blocks;

    grid(int width_in, int height_in) {
        width = width_in;
        height = height_in;
    }

    int populate(char* stuff) { 

        // this is here because I don't know what the incoming
        // data would look like, and cannot write a parser for it yet.
        int temp = strlen(stuff);
        ++temp;

        bool found = false;
        // once stuffed
        for (size_t i = 0; i < width; i++) {
            for (size_t j = 0; j < height; j++) {
                if (blocks[i][j] == block_types::PLAYER_START) {
                    player_start.first = i;
                    player_start.second = j;
                    found = true;
                    break;
                }                
            }
            if (found) break;
        }
    
        if (!found) {
            // invalid input, no player start
        }

        return; 
    }

    block_types get_type(int x, int y) {
        if (!valid_width(x) || !valid_height(y)){
            return block_types::INVALID;
        }

        return blocks[x][y];
    }

    block_types get_type(std::pair<int, int> xy) {
        if (!valid_width(xy.first) || !valid_height(xy.second)){
            return block_types::INVALID;
        }

        return blocks[xy.first][xy.second];
    }

    block_types get_type(std::pair<int, int> xy) {
        if (!valid_width(xy.first) || !valid_height(xy.second)){
            return block_types::INVALID;
        }

        return blocks[xy.first][xy.second];
    }

    bool is_playable (block_types type){
        switch (type)
        {
        case block_types::EMPTY:
        case block_types::EXIT:
        case block_types::PLAYER_START:
        case block_types::MOVABLE:
        case block_types::DIRECTIONAL:
            return true;
            break;

        default:
            return false;
            break;
        }
    }

    std::pair<int, int> move(int x, int y, direction_list direction) {

        std::pair<int, int> out;
        out.first = x;
        out.second = y;

        switch(direction) {

            case direction_list::UP:
                if (valid_height(y - 1)){
                    --out.second;
                }
                break;
            case direction_list::DOWN:
                if (valid_height(y + 1)){
                    ++out.second;
                }
                break;
            case direction_list::LEFT:
                if (valid_width(x - 1)){
                    --out.first;
                }
                break;
            case direction_list::RIGHT:
                if (valid_width(x + 1)){
                    ++out.first;
                }
                break;
        }
        
        return out;
    }

    static direction_list next_direction(direction_list direction){
        switch(direction) {
            case direction_list::UP:
                return direction_list::RIGHT;
                break;
            case direction_list::RIGHT:
                return direction_list::DOWN;
                break;
            case direction_list::DOWN:
                return direction_list::LEFT;
                break;
            case direction_list::LEFT:
                return direction_list::UP;
                break;
        }
    }

    void populate_play_area() {

        if (!valid_width(player_start.first) || !valid_height(player_start.second));{

            return;
        }

        std::pair<int, int> current_position;
        std::pair<int, int> last_position;
        current_position.first = player_start.first;
        current_position.second = player_start.second;

        std::unordered_set<std::pair<int, int>, pair_hash> found_squares;
        std::queue<std::pair<int,int>> to_search;

        direction_list direction = direction_list::LEFT;

        do {
            last_position = current_position;
            current_position = to_search.front();
            to_search.pop();
            direction_list last_direction = direction;

            do {
                direction = next_direction(direction);
                current_position = move(last_position.first, last_position.second, direction);

                if (
                   !(last_position == current_position) 
                && found_squares.find(current_position) != found_squares.end()
                && is_playable(get_type(current_position))
                ) {
                    found_squares.insert(current_position);
                    to_search.push(current_position);
                    direction = next_direction(direction);
                }
            } while (direction != last_direction);

        } while (static_cast<int>(found_squares.size()) < width * height);

    }

};





int main (char* in)
{
    int width = 10;
    int height = 10;
    auto level = grid(width, height);

    level.populate(in);



}



