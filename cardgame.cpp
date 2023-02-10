#include <iostream>
#include <vector>
#include <math.h>
#include <map>
#include "includes/entities.h"

using namespace std;

class Scene
// Scenes are locations in the game world which may have
// Enemies or Items.
{
protected:
    string area_description;
    vector<Entity *> enemies;
    vector<Item *> items;
    string describe_enemies()
    {
        string temp = "There ";
        if (this->enemies.size() == 1)
        {
            temp.append("is ");
            temp.append(this->enemies[0]->description);
            if (this->enemies[0]->bloodied)
            {
                temp.append(this->enemies[0]->bloodied_description);
            }
        }
        else if (this->enemies.size() == 2)
        {
            temp.append("are ");
            temp.append(this->enemies[0]->description);
            temp.append(" and ");
            temp.append(this->enemies[1]->description);
        }
        else if (this->enemies.size()>2)
        {
            temp.append("are ");
            for (auto i = enemies.begin(); i != enemies.end(); i++)
            {
                if (i == enemies.end())
                {
                    temp.append(" and ");
                }
                temp.append((*i)->description);
                if (i != enemies.end() - 1)
                {
                    temp.append(", ");
                }
            }
        }
        
        temp.append(" nearby.\n");
        for (auto i = enemies.begin(); i != enemies.end(); i++){
            if ((*i)->bloodied){
                temp = temp + (*i)->bloodied_description;
            }
        }
        return temp;
    }

public:
    void stock_enemies(Entity *entity)
    // Adds entities to the scene
    {
        this->enemies.push_back(entity);
    }
    void stock_items(Item *item)
    // Adds items to the scene
    {
        this->items.push_back(item);
    }
    void describe_scene()
    // Describes scene visually including background, objects, and enemies.
    {

        cout << area_description;
        cout << describe_enemies();
    }

};
class Area_One : public Scene
{
public:
    Area_One()
    {
        this->area_description = "The wide boulevard you woke up on passes between the mammoth buildings around you and strikes out deeper into the city.\n\nToward the center of this great dome the buildings spiral upward and grow grander and more magnificent as they reach for the sky. \n\nWhether those buildings are organic in origin or attempts at replicating the aesthetic of nature is unclear from this far away, but something that's certain is that you've never known any plant or other building material which could hold such massive structures on such spindly legs as some of those central buildings.\n\n\n";
    }
};

class Game_Master
{
private:
    Entity *player;
    vector<Entity *> enemy;
    Scene scene;
    static map<string, int> effects_map;

public:
    void referee_effects(vector<effect_struct> effects, Entity* target){
        for (auto i = effects.begin(); i != effects.end(); i++){
            switch (effects_map[i->effect_type])
            {
            case 0://Damage
                /* code */
                cout << "Referee declares "+i->effect_type << endl;
                target->decrease_hp(i->effect_magnitude);
                break;
            case 1://Stun
                break;
            default:
                break;
            }
        }

    }
    void load_scene(Scene *location)
    {
        location->describe_scene();
    }
};

void test_basic_functions()
{
    Vampire v = Vampire();
    Vampire *vp = &v;
    Game_Master gm = Game_Master();
    Scene a = Area_One();
    a.stock_enemies(vp);
    gm.load_scene(&a);
    Human_Fighter hf = Human_Fighter("Finn");
    a.stock_enemies(&hf);
    gm.load_scene(&a);
    hf.get_deck();
    gm.referee_effects(hf.deck.cards[0]->cast_spell(), &v);

    //smash->cast_spell(vp);
    a.describe_scene();
    hf.deck.remove_card(0);
    hf.get_deck();
}

map<string,int> Game_Master::effects_map = {
   {"Damage", 0},
   {"Stun", 1},
   {"Empower", 2}
};


int main()
{
    test_basic_functions();
}
