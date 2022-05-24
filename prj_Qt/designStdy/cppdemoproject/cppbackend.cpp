#include "cppbackend.h"

CppBackend::CppBackend(QObject *parent) : QObject(parent) {

    m_timer.setInterval(3);
    m_timer.setSingleShot(false);
    m_timer.start();

    connect(&m_timer, &QTimer::timeout, this, [this]() {
        if (m_steps >= 1010 || m_steps < 0)
            m_direction = m_direction * -1;
        m_steps += m_direction;

        waterActiveChanged();
        percentageChanged();
        timeChanged();
    });
}

int CppBackend::percentage() const { return m_steps / 10; }

QString CppBackend::time() const {
    return "00:" + QString::number(60 - (m_steps / 35));
}

bool CppBackend::waterActive() const { return m_steps > 200 && m_steps < 800; }
