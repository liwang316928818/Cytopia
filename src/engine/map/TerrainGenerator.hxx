#ifndef TERRAIN_GEN_HXX_
#define TERRAIN_GEN_HXX_

#include "../GameObjects/mapNode.hxx"

#include <map>
#include <vector>

struct BiomeData
{
  std::vector<std::string> terrain;         // Terrain IDs
  std::vector<std::string> water;           // Water IDs
  std::vector<std::string> waterDecoration; // WaterDecoration IDs
  std::vector<std::string> terrainRocks;    // TerrainRocks IDs
  std::vector<std::string> terrainFlowers;  // terrainFlowers IDs
  std::vector<std::string> treesDense;      // terrainFlowers IDs
  std::vector<std::string> treesSmall;      // terrainFlowers IDs
  std::vector<std::string> treesNormal;     // terrainFlowers IDs
};

struct TerrainSettings
{
  int mapSize = 128;
  int seed = 1234;
  int seaLevel = 2;				// All tiles with elevation below this will be set as water.
  int treeDensity = 50;			// 0% no trees, 100% All trees everywhere all the time.
  int mountainAmplitude = 10;   // Both amplifies the mountain noise source, as well as biasing the mountain/plains blend. Expects 0-100.
  int waterAmount = 5;			// Density of freshwater in addition to coastlines and rivers. Expects 0-100.
  int coasts = 1;				// 4 least significant bits are bitmasked, where 0 is a land border and 1 is a coastline. Remaining bits reserved for future use.
  int rivers = 1;				// Number of rivers to attempt generating.
  std::string biomes = "{}";	// JSON string of biomes to attempt using, plus any options associated with them.
  std::string advanced = "{}";	// JSON string of arbitrary advanced option data for future use or mods.
};

class TerrainGenerator
{
public:
  TerrainGenerator() = default;
  ~TerrainGenerator() = default;

  typedef std::vector<MapNode *> MapNodeVector;
  typedef std::vector<std::unique_ptr<MapNode>> MapNodeUniquePtrVector;

  void generateTerrain(MapNodeUniquePtrVector &mapNodes, MapNodeVector &mapNodesInDrawingOrder);

  void loadTerrainDataFromJSON();

private:
  TerrainSettings terrainSettings;

  std::map<std::string, BiomeData> biomeInformation; // key: biome
};

#endif