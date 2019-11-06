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

#ifndef GAMECUBE_HPP
#define GAMECUBE_HPP

#include <Core/Gen3/Profile3.hpp>
#include <QMenu>

namespace PokeFinderCore
{
    class Frame3;
}

namespace PokeFinderModels
{
    class Searcher3Model;
    class Stationary3Model;
}

namespace PokeFinderForms
{
    namespace Ui
    {
        class GameCube;
    }

    class GameCube : public QWidget
    {
        Q_OBJECT
    signals:
        void alertProfiles(int);

    public:
        explicit GameCube(QWidget *parent = nullptr);
        ~GameCube() override;
        void updateProfiles();

    private:
        Ui::GameCube *ui;
        PokeFinderModels::Searcher3Model *searcherModel {};
        PokeFinderModels::Stationary3Model *generatorModel {};
        QVector<PokeFinderCore::Profile3> profiles;
        QMenu *generatorMenu {};
        QMenu *searcherMenu {};

        void setupModels();

    private slots:
        void updateProgress(const QVector<PokeFinderCore::Frame3> &frames, int progress);
        void refreshProfiles();
        void generate();
        void search();
        void profilesIndexChanged(int index);
        void generatorMethodIndexChanged(int index);
        void generatorShadowIndexChanged(int index);
        void searcherMethodIndexChanged(int index);
        void tableViewGeneratorContextMenu(QPoint pos);
        void tableViewSearcherContextMenu(QPoint pos);
        void seedToTime();
        void copySeedToClipboard();
        void profileManager();
    };
}

#endif // GAMECUBE_HPP
