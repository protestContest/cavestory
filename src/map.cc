#include "map.h"
#include "sprite.h"
#include "graphics.h"
#include "game.h"
#include "rectangle.h"

using boost::shared_ptr;
using std::vector;

Map* Map::createTestMap(Graphics& graphics) {
    Map* map = new Map();

    const int num_rows = 15;
    const int num_cols = 20;
    map->tiles_ = vector<vector<Tile> >(
            num_rows, vector<Tile>(
                num_cols, Tile()));

    shared_ptr<Sprite> sprite(new Sprite(
                graphics,
                "content/PrtCave.bmp",
                Game::kTileSize, 0,
                Game::kTileSize, Game::kTileSize));

    Tile tile(WALL_TILE, sprite);
    const int row = 11;
    for (int col = 0; col < num_cols; ++col) {
        map->tiles_[row][col] = tile;
    }
    map->tiles_[10][5] = tile;
    map->tiles_[9][4] = tile;
    map->tiles_[8][3] = tile;
    map->tiles_[7][2] = tile;
    map->tiles_[10][1] = tile;

    return map;
}

void Map::update(int elapsed_time_ms) {
    for (size_t row = 0; row < tiles_.size(); ++row) {
        for (size_t col = 0; col < tiles_[row].size(); ++col) {
            if (tiles_[row][col].sprite) {
                tiles_[row][col].sprite->update(elapsed_time_ms);
            }
        }
    }
}

std::vector<Map::CollisionTile> Map::getCollidingTiles(const Rectangle& rectangle) const {
    vector<CollisionTile> collision_tiles;

    return collision_tiles;
}

void Map::draw(Graphics& graphics) const {
    for (size_t row = 0; row < tiles_.size(); ++row) {
        for (size_t col = 0; col < tiles_[row].size(); ++col) {
            if (tiles_[row][col].sprite) {
                tiles_[row][col].sprite->draw(
                        graphics, col * Game::kTileSize, row * Game::kTileSize);
            }
        }
    }
}
