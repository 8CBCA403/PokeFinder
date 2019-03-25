/*
 * This file is part of PokéFinder
 * Copyright (C) 2017-2019 by Admiral_Fish, bumba, and EzPzStreamz
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef ENCOUNTERAREA_HPP
#define ENCOUNTERAREA_HPP

#include <QFile>
#include <QVector>
#include <Core/Util/Encounter.hpp>
#include <Core/Util/Global.hpp>
#include <Core/Util/Translator.hpp>

class Slot;

class EncounterArea
{

public:
    EncounterArea() = default;
    EncounterArea(int location, Encounter type, const QVector<Slot> &pokemon);
    Encounter getType() const;
    u8 getLocation() const;
    QVector<u16> getUniqueSpecies() const;
    QVector<bool> getSlots(u16 num) const;
    QStringList getSpecieNames() const;
    void setSlot(u8 index, u8 specie);

protected:
    QVector<Slot> pokemon;
    u8 location;
    Encounter type;

};

class Slot
{

public:
    Slot() = default;
    Slot(u16 specie, u8 minLevel, u8 maxLevel);
    Slot(u16 specie, u8 level);

    u8 getMinLevel() const { return minLevel; }
    u8 getMaxLevel() const { return maxLevel; }
    u16 getSpecie() const { return specie; }
    void setSpecie(int specie) { this->specie = specie; }

private:
    u8 minLevel;
    u8 maxLevel;
    u16 specie;

};

#endif // ENCOUNTERAREA_HPP
