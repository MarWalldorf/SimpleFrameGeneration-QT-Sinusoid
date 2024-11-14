#include "MainWindow.h"
#include <QPainter>
#include <QVBoxLayout>
#include <cmath>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), timeOffset(0.0f), frameMultiplier(1.0f) {
    // Ustawienia okna
    setFixedSize(800, 600);

    // Ustawienie timera dla generacji klatek
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateWave);

    // Utworzenie przełącznika "Frame Generation"
    frameGenerationCheckBox = new QCheckBox("Frame Generation", this);
    frameGenerationCheckBox->setChecked(true); // Domyślnie włączony (60 FPS)
    connect(frameGenerationCheckBox, &QCheckBox::toggled, this, &MainWindow::toggleFrameGeneration);

    // Ustawienie układu, aby przycisk znajdował się w górnym rogu
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(frameGenerationCheckBox);
    layout->addStretch();
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    toggleFrameGeneration(true); // Uruchomienie z domyślnym 60 FPS
}

MainWindow::~MainWindow() {
    delete timer;
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.fillRect(rect(), Qt::black); // Ustawienie tła na czarne

    QPen pen(Qt::green);
    painter.setPen(pen);

    // Rysowanie sinusoidy
    for (int x = 0; x < width(); x++) {
        int y = height() / 2 + static_cast<int>(100 * sin((x + timeOffset) * 0.05));
        painter.drawPoint(x, y);
    }
}

void MainWindow::updateWave() {
    timeOffset += frameMultiplier * 1.0f; // Aktualizacja przesunięcia dla sinusoidy, dostosowana do FPS
    update(); // Odświeżenie okna, wywołanie paintEvent
}

void MainWindow::toggleFrameGeneration(bool enabled) {
    if (enabled) {
        timer->start(16);       // 60 FPS
        frameMultiplier = 1.0f; // Mnożnik dla 60 FPS
    } else {
        timer->start(33);       // 30 FPS
        frameMultiplier = 2.0f; // Mnożnik dla 30 FPS, aby zachować tę samą prędkość animacji
    }
}
