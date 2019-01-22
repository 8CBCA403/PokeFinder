/*
 * This file is part of PokéFinder
 * Copyright (C) 2017 by Admiral_Fish, bumba, and EzPzStreamz
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

#ifndef PROFILE5_HPP
#define PROFILE5_HPP

#include <Core/Objects/DSType.hpp>
#include <Core/Objects/Profile.hpp>

class Profile5 : public Profile
{

public:
    Profile5(const QString &profileName, Game version, u16 tid, u16 sid, u32 mac, const QVector<bool> &keypresses, u8 vcount,
             u8 gxstat, u8 vframe, bool skipLR, u16 timer0Min, u16 timer0Max, bool softReset, DSType dsType, int language = 0);
    Profile5(QJsonObject data);
    Profile5();
    u32 getMac() const;
    QVector<bool> getKeypresses() const;
    u8 getVCount() const;
    u8 getGxStat() const;
    u8 getVFrame() const;
    bool getSkipLR() const;
    u16 getTimer0Min() const;
    u16 getTimer0Max() const;
    bool getSoftReset() const;
    DSType getDsType() const;
    QJsonObject getJson() const;
    static QVector<Profile5> loadProfileList();
    void saveProfile() const;
    void deleteProfile() const;
    void updateProfile(const Profile5 &original) const;
    friend bool operator==(const Profile5 &left, const Profile5 &right);

private:
    u32 mac;
    QVector<bool> keypresses; // 4 index; 0: None, 1: One, 2: Two, 3: Three
    u8 vcount;
    u8 gxstat;
    u8 vframe;
    bool skipLR;
    u16 timer0Min;
    u16 timer0Max;
    bool softReset;
    DSType dsType;

};

bool operator==(const Profile5 &left, const Profile5 &right);

#endif // PROFILE5_HPP
