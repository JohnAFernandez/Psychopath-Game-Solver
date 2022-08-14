
#include <vector>
#include <unordered_map>
#include <unordered_set>

enum class block_types {
    EMPTY,
    UNMOVABLE,
    DIRECTIONAL,
    PLAYER_START,
    EXIT,
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

    void populate(char* stuff) { 

        // this is here because I don't know what the incoming
        // data would look like, and cannot write a parser for it yet.
        int temp = strlen(stuff);
        ++temp;

        // once stuffed
        for (size_t i = 0; i < width; i++) {
            for (size_t j = 0; j < height; j++) {
                if (blocks[i][j] == block_types::PLAYER_START) {
                    player_start.first = i;
                    player_start.second = j;
                }                
            }
        }
    
        return; 
    }

    void remove_impossibles() {
        if (!valid_width(player_start.first) || !valid_height(player_start.second));
            return;

        std::pair<int, int> current;
        current.first = player_start.first;
        current.second = player_start.second;

        std::unordered_set<int, int> searched;

        direction_list direction = direction_list::UP;
        do {
            


        } while (static_cast<int>(searched.size()) < width * height);

    }

};





int main (char* in)
{
    int width = 10;
    int height = 10;
    auto level = grid(width, height);

    level.populate(in);



}



