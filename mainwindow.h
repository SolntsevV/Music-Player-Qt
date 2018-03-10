#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultimedia/QMediaPlayer>
#include <string>
#include <QMultiMedia>
#include <QFileDialog>
#include <QMediaPlaylist>
#include <QListWidgetItem>
#include <QKeyEvent>
#include <QTime>
#include <QListView>

namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class основной класс для обработки нажатий клавиш
*/

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:

    /**
     * @brief on_horizontalSlider_2_sliderMoved Этот метод реагирует на перетаскивание ползунка перемотки записи
     * @param position переменная, которая передает позицию в записи
     */

    void on_horizontalSlider_2_sliderMoved(int position);

    /**
     * @brief on_checkBox_toggled Этот метод реагирует на нажатие галочки в чекбоксе, если нажата, то звук заглушается
     * @param checked переменная, которая покахывает, что звук нужно выключить или включить
     */

    void on_checkBox_toggled(bool checked);

    /**
     * @brief on_actionOpen_File_triggered Метод, который отвечает за нажатие на кнопку открытие файла
     */

    void on_actionOpen_File_triggered();

    /**
     * @brief durationChanged Метод, для изменения позиции в аудио записи
     * @param duration Параметр для изменения положения
     */

    void durationChanged(qint64 duration);

    /**
     * @brief positionChanged Метод для автоматического изменения слайдера звука при проигрывании записи
     * @param progress Параметр для изменения положения
     */

    void positionChanged(qint64 progress);

    /**
     * @brief show_time Метод для отображения времени песни
     * @param currentInfo Параметр текущей позиции
     */

    void show_time(quint64 currentInfo);

    void on_songBar_sliderMoved(int position);

    /**
     * @brief openMediaFile Метод для открытие файла
     */

    void openMediaFile();
    /**
     * @brief on_playbutton_clicked Метод для обработки нажатия клавиши play
     */
    void on_playbutton_clicked();

    /**
     * @brief on_pausebutton_clicked Метод для обработки нажатия клавиши pause
     */

    void on_pausebutton_clicked();

    /**
     * @brief  on_pushButton_clicked Метод для обработки нажатия клавиши stop
     */

    void on_pushButton_clicked();

    /**
     * @brief  on_pushButton_clicked Метод для закрытия окна
     */

    void on_action_triggered(); // закрытие

    /**
     * @brief on_listWidget_activated Метод для обработки плейлиста
     */

    void on_listWidget_activated();

private:
    Ui::MainWindow *ui;

   QMediaPlayer *player; //!< Указатель на проигрыватель
   QStringList fileNames; //!< Указатель на переменную, в которую записывается путь файла
   QMediaPlaylist *playlist; //!< Указатель на плейлист, который принимает значения из WidgetList и записывает туда
   int total; //!< Переменная для отображения конечного значения времени в записи
   int playPauseCounter; //!< Переменная для определения состояния плеера (1- играет, 2 - на паузе)
   int defaultVolume; //!< Переменная, которая содержит громкость по умолчанию
   quint64 duration; //!< Переменная, соержащая позицию в мелодии
};

#endif // MAINWINDOW_H
