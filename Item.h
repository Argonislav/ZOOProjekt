//
// Created by Lukas Houska on 12.05.2024.
//

#ifndef ZOOPROJEKT_ITEM_H
#define ZOOPROJEKT_ITEM_H


#include <string>

enum class ItemType {
    Consumable, // Spotřebitelná položka
    Equipable  // Vybavitelná položka
};

enum class PotionType {
    Health,
    Attack,
    Defense
};

class Item {
protected:
    PotionType potionType; // Přidán atribut pro typ lektvaru
private:
    std::string m_name;
    std::string m_description;
    ItemType m_type;
    int m_attackBonus;
    int m_healthBonus;
    int m_defenseBonus;
    bool equipped;

public:
    Item(std::string name, std::string description, ItemType type, int attackBonus = 0, int healthBonus = 0, int defenseBonus = 0);

    std::string getName();
    void setName(std::string name);

    std::string getDescription();
    void setDescription(std::string description);

    ItemType getType();
    void setType(ItemType type);

    int getAttackBonus();
    void setAttackBonus(int attackBonus);

    int getHealthBonus();
    void setHealthBonus(int healthBonus);

    int getDefenseBonus();
    void setDefenseBonus(int defenseBonus);

    bool getEquipped(); // Přidána metoda pro získání stavu vybavení
    void setEquipped(bool equipped); // Přidána metoda pro nastavení stavu vybavení

    PotionType getPotionType(); // Přidána metoda pro získání typu lektvaru
    void setPotionType(PotionType type); // Přidána metoda pro nastavení typu lektvaru

    virtual void use() = 0;
};

#endif //ZOOPROJEKT_ITEM_H
