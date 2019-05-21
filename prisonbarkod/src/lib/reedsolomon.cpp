/*
    Copyright (c) 2017 Volker Krause <vkrause@kde.org>

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.

*/

#include "reedsolomon_p.h"
#include "bitvector_p.h"

#include <QDebug>

#include <memory>

using namespace Prison;

// See https://en.wikiversity.org/wiki/Reed%E2%80%93Solomon_codes_for_coders

static int highestBit(int n)
{
    int i = 0;
    while (n >= (1 << i))
        ++i;
    return i - 1;
}

ReedSolomon::ReedSolomon(int polynom, int symbolCount)
    : m_symCount(symbolCount)
{
    m_symSize = highestBit(polynom);

    // calculate the log/alog tables
    const auto logmod = (1 << m_symSize) - 1;
    m_logTable.reset(new int[logmod + 1]);
    m_antiLogTable.reset(new int [logmod]);

    for (int p = 1, v = 0; v < logmod; v++) {
        m_antiLogTable[v] = p;
        m_logTable[p] = v;
        p <<= 1;
        if (p & (1 << m_symSize)) {
            p ^= polynom;
        }
    }

    // compute the encoding polynom
    m_polynom.reset(new int[m_symCount + 1]);
    m_polynom[0] = 1;
    for (int i = 1; i <= m_symCount; ++i) {
        m_polynom[i] = 1;
        for (int k = i - 1; k > 0; --k) {
            if (m_polynom[k]) {
                m_polynom[k] = m_antiLogTable[(m_logTable[m_polynom[k]] + i) % logmod];
            }
            m_polynom[k] ^= m_polynom[k - 1];
        }
        m_polynom[0] = m_antiLogTable[(m_logTable[m_polynom[0]] + i) % logmod];
    }
}

ReedSolomon::~ReedSolomon() = default;

BitVector ReedSolomon::encode(const BitVector& input) const
{
    std::unique_ptr<int[]> result(new int[m_symCount]);
    for (int i = 0; i < m_symCount; ++i) {
        result[i] = 0;
    }

    const auto logmod = (1 << m_symSize) - 1;
    for (int i = 0; i < input.size() / m_symSize; i++) {
        auto m = result[m_symCount - 1] ^ input.valueAtMSB(i * m_symSize, m_symSize);
        for (int k = m_symCount - 1; k > 0; --k) {
            if (m && m_polynom[k]) {
                result[k] = result[k - 1] ^ m_antiLogTable[(m_logTable[m] + m_logTable[m_polynom[k]]) % logmod];
            } else {
                result[k] = result[k - 1];
            }
        }
        if (m && m_polynom[0]) {
            result[0] = m_antiLogTable[(m_logTable[m] + m_logTable[m_polynom[0]]) % logmod];
        } else {
            result[0] = 0;
        }
    }

    BitVector v;
    for (int i = m_symCount - 1; i >= 0; --i) {
        v.appendMSB(result[i], m_symSize);
    }
    return v;
}
