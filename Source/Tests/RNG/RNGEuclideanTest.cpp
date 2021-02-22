#include "RNGEuclideanTest.hpp"
#include <Core/RNG/RNGEuclidean.hpp>
#include <QTest>

void RNGEuclideanTest::ivs_data()
{
    QTest::addColumn<QVector<u8>>("ivs");
    QTest::addColumn<QVector<QPair<u32, u32>>>("results");

    QTest::newRow("6IV") << QVector<u8>({ 31, 31, 31, 31, 31, 31 })
                         << QVector<QPair<u32, u32>>({ qMakePair(0x7FFF14C6, 0x7FFFF871), qMakePair(0x7FFF8A5D, 0xFFFFB3AC),
                                                       qMakePair(0x7FFFFFF4, 0x7FFF6EE7) });
    QTest::newRow("Atk") << QVector<u8>({ 31, 31, 31, 0, 31, 31 })
                         << QVector<QPair<u32, u32>>({ qMakePair(0x7FFF1396, 0x7C1F3C01), qMakePair(0x7FFFD792, 0xFC1FE00D) });
    QTest::newRow("SpA") << QVector<u8>({ 31, 0, 31, 31, 31, 31 })
                         << QVector<QPair<u32, u32>>({ qMakePair(0x7C1F3869, 0x7FFFD988), qMakePair(0x7C1FAE00, 0xFFFF94C3) });
}

void RNGEuclideanTest::ivs()
{
    using Results = QVector<QPair<u32, u32>>;

    QFETCH(QVector<u8>, ivs);
    QFETCH(Results, results);

    std::vector<std::pair<u32, u32>> convert;
    for (const auto &result : results)
    {
        convert.emplace_back(result.first, result.second);
    }

    QCOMPARE(RNGEuclidean::recoverLower16BitsIV(ivs[0], ivs[1], ivs[2], ivs[3], ivs[4], ivs[5]), convert);
}

void RNGEuclideanTest::pid_data()
{
    QTest::addColumn<u32>("pid");
    QTest::addColumn<QVector<QPair<u32, u32>>>("results");

    QTest::newRow("Test 1") << 0x00000000U << QVector<QPair<u32, u32>>({ qMakePair(0x00004E59, 0x000057B8) });
    QTest::newRow("Test 2") << 0x80000000U << QVector<QPair<u32, u32>>({ qMakePair(0x8000C3F0, 0x000012F3) });
}

void RNGEuclideanTest::pid()
{
    using Results = QVector<QPair<u32, u32>>;

    QFETCH(u32, pid);
    QFETCH(Results, results);

    std::vector<std::pair<u32, u32>> convert;
    for (const auto &result : results)
    {
        convert.emplace_back(result.first, result.second);
    }

    QCOMPARE(RNGEuclidean::recoverLower16BitsPID(pid), convert);
}

void RNGEuclideanTest::ivsChannel_data()
{
    QTest::addColumn<QVector<u8>>("ivs");
    QTest::addColumn<QVector<u32>>("results");

    QTest::newRow("6IV") << QVector<u8>({ 31, 31, 31, 31, 31, 31 }) << QVector<u32>({ 0xFBA5085C, 0xFBCB9DE0, 0xFD156C92, 0xFD3C0216 });
    QTest::newRow("Atk") << QVector<u8>({ 31, 31, 31, 0, 31, 31 }) << QVector<u32>({ 0xFCC8418A, 0xFCEED70E, 0xFD560753, 0xFED2AC77 });
    QTest::newRow("SpA") << QVector<u8>({ 31, 0, 31, 31, 31, 31 }) << QVector<u32>({ 0xFC87A6C9, 0xFCAE3C4D, 0xFE9211B6 });
}

void RNGEuclideanTest::ivsChannel()
{
    QFETCH(QVector<u8>, ivs);
    QFETCH(QVector<u32>, results);

    QCOMPARE(RNGEuclidean::recoverLower27BitsChannel(ivs[0], ivs[1], ivs[2], ivs[3], ivs[4], ivs[5]),
             std::vector<u32>(results.begin(), results.end()));
}
