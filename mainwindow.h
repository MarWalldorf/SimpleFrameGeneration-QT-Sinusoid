#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QCheckBox>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void updateWave();
    void toggleFrameGeneration(bool enabled);

private:
    float timeOffset;
    float frameMultiplier;
    QTimer *timer;
    QCheckBox *frameGenerationCheckBox;
};

#endif // MAINWINDOW_H
