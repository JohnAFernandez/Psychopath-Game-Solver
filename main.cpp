
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

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
    NUM_ENTIRES
};

enum class direction_list {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NUM_ENTIRES
};

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

        std::unordered_set<std::pair<int, int>> found;

        direction_list direction = direction_list::LEFT;

        do {
            last_position = current_position;
            direction_list last_direction = direction;

            do {
                direction = next_direction(direction);
                current_position = move(current_position.first, current_position.second, direction);

                if (last_position == current_position) {
                    continue;
                }

                if (found.find(current_position) != found.end()){
                    continue;
                }

                found.insert(current_position);

                current_position = move(current_position.first, current_position.second, direction);
                direction = next_direction(direction);
            } while (direction != last_direction);

        } while (static_cast<int>(found.size()) < width * height);

    }

};





int main (char* in)
{
    int width = 10;
    int height = 10;
    auto level = grid(width, height);

    level.populate(in);



}



