#ifndef MCPSP_WORLD_ITEM_FOOD_ITEM_H
#define MCPSP_WORLD_ITEM_FOOD_ITEM_H

#include "world/item/item.h"
#include "world/item/digger_item.h"
#include "world/level/tile/material.h"

class FoodItem : public virtual Item {
public:

    static const int EAT_TICKS = 32;

    FoodItem(short id, int nutrition, bool isMeat, int icon)
        : Item(id), nutrition(nutrition), icon(icon), meat(isMeat) {}
    virtual bool isFood() const { return true; }
    virtual int  getIcon(short data) const { return icon; }

    virtual void use(ItemInstance* item, Player* player, World* world);
    virtual int  getMaxUseDuration() const { return EAT_TICKS; }
    virtual void useTimeDepleted(ItemInstance* item, Player* player);
    virtual int  getUseAnimation() const { return 1; }
    int  getNutrition() const { return nutrition; }
    bool isMeat() const { return meat; }
protected:
    int  nutrition;
    int  icon;
    bool meat;
};

class BowlFoodItem : public FoodItem {
public:
    BowlFoodItem(short id, int nutrition, int icon) : Item(id), FoodItem(id, nutrition, false, icon) {
        maxStackSize = 1;
    }
    virtual void useTimeDepleted(ItemInstance* item, Player* player);
};

class SeedFoodItem : public FoodItem {
public:
    short plantTile;

    SeedFoodItem(short id, int nutrition, short plantTile, int icon)
        : Item(id), FoodItem(id, nutrition, false, icon), plantTile(plantTile) {}
    virtual bool useOn(ItemInstance* item, Player* player, World* world, int x, int y, int z, int face, float, float, float);

    virtual bool placesTile() const { return true; }
    virtual short plantedTileId() const { return plantTile; }
};

class MultiItem : public DiggerItem, public BowlFoodItem {
public:
    virtual float getDestroySpeed(int blockId) const {
        if (blockId >= 0 && blockId < 256) {
            const Material& m = materialOf((unsigned char)blockId);
            if (&m == &Material::stone || &m == &Material::metal || &m == &Material::dirt) return speed;
        }
        return DiggerItem::getDestroySpeed(blockId);
    }
public:
    MultiItem(short id, const Tier& tier, int nutrition, int icon) : Item(id), DiggerItem(id, 4, tier, icon), BowlFoodItem(id, nutrition, icon){
        addTile(BLOCK_GRASS); addTile(BLOCK_DIRT); addTile(BLOCK_SAND); addTile(BLOCK_GRAVEL);
        addTile(BLOCK_TOPSNOW); addTile(BLOCK_SNOW_BLOCK); addTile(BLOCK_CLAY); addTile(BLOCK_FARMLAND);

        addTile(BLOCK_COBBLESTONE);

        addTile(BLOCK_DOUBLE_SLAB); addTile(BLOCK_SLAB);
        addTile(BLOCK_STONE);
        addTile(BLOCK_SANDSTONE); addTile(BLOCK_MOSSY_COBBLE);
        addTile(BLOCK_ORE_IRON); addTile(BLOCK_IRON_BLOCK);
        addTile(BLOCK_ORE_COAL);
        addTile(BLOCK_GOLD_BLOCK); addTile(BLOCK_ORE_GOLD);
        addTile(BLOCK_ORE_DIAMOND);
        addTile(BLOCK_DIAMOND_BLOCK);
        addTile(BLOCK_ICE);
        addTile(BLOCK_ORE_LAPIS); addTile(BLOCK_LAPIS_BLOCK);
        addTile(BLOCK_ORE_REDSTONE); addTile(BLOCK_ORE_REDSTONE_LIT);
    }
    int getIcon(short data) const override {
        return DiggerItem::getIcon(data);
    }
    virtual bool canDestroySpecial(int b) const { //without this block, the tool couldnt fast break stone and metals

        if (b == BLOCK_OBSIDIAN || b == BLOCK_GLOWING_OBSIDIAN) return level == 3;
        if (b == BLOCK_DIAMOND_BLOCK || b == BLOCK_ORE_DIAMOND) return level >= 2;
        if (b == BLOCK_GOLD_BLOCK || b == BLOCK_ORE_GOLD)       return level >= 2;
        if (b == BLOCK_IRON_BLOCK || b == BLOCK_ORE_IRON)       return level >= 1;
        if (b == BLOCK_LAPIS_BLOCK || b == BLOCK_ORE_LAPIS)     return level >= 1;
        if (b == BLOCK_ORE_REDSTONE || b == BLOCK_ORE_REDSTONE_LIT) return level >= 2;

        if (b >= 0 && b < 256) {
            const Material& m = materialOf((unsigned char)b);
            if (&m == &Material::stone || &m == &Material::metal) return true;
        }
        return mineable[b >= 0 && b < 256 ? b : 0];
    }
};

#endif
