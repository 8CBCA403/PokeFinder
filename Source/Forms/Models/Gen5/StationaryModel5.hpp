/*
 * This file is part of PokéFinder
 * Copyright (C) 2017-2021 by Admiral_Fish, bumba, and EzPzStreamz
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

#ifndef STATIONARYMODEL5_HPP
#define STATIONARYMODEL5_HPP

#include <Core/Enum/Game.hpp>
#include <Core/Gen5/States/SearcherState5.hpp>
#include <Core/Gen5/States/StationaryState5.hpp>
#include <Forms/Models/TableModel.hpp>

enum Method : u8;

class StationaryGeneratorModel5 : public TableModel<StationaryState5>
{
    Q_OBJECT
public:
    explicit StationaryGeneratorModel5(QObject *parent, Method method);
    void setMethod(Method method);
    void setUseTime(bool useTime);
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

private:
    Method method;
    QStringList header = { tr("Advances"), tr("Time"), tr("Chatot"), tr("PID"), tr("Shiny"), tr("Nature"), tr("Ability"), tr("HP"),
                           tr("Atk"),      tr("Def"),  tr("SpA"),    tr("SpD"), tr("Spe"),   tr("Hidden"), tr("Power"),   tr("Gender") };

    bool time;
    int getColumn(int column) const;
};

class StationarySearcherModel5 : public TableModel<SearcherState5<StationaryState5>>
{
    Q_OBJECT
public:
    explicit StationarySearcherModel5(QObject *parent, Method method);
    void setMethod(Method method);
    void setVersion(Game game);
    void sort(int column, Qt::SortOrder order) override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

private:
    Method method;
    Game game;
    QStringList header = { tr("Seed"),  tr("Advances"), tr("Lead"),      tr("PID"),    tr("Shiny"),  tr("Nature"), tr("Ability"),
                           tr("HP"),    tr("Atk"),      tr("Def"),       tr("SpA"),    tr("SpD"),    tr("Spe"),    tr("Hidden"),
                           tr("Power"), tr("Gender"),   tr("Date/Time"), tr("Timer0"), tr("Buttons") };

    int getColumn(int column) const;
};

#endif // STATIONARYMODEL5_HPP
