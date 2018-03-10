#include "mainwindow.h"
#include "ui_mainwindow.h"

bool checked;

/**
 * @brief MainWindow::MainWindow Конструктор основного класса, создает интерфейс пользователя и задает начальные значения переменных
 */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    total=0;
    player = new QMediaPlayer;
    playlist = new QMediaPlaylist;
    duration = 0;
    playPauseCounter = 1;

    player->setVolume(50);
    defaultVolume = ui->horizontalSlider_2->value();
    player->setPlaylist(playlist);

   connect(player, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));
   connect(player, SIGNAL(positionChanged(qint64)), this,SLOT(positionChanged(qint64)));
}

/**
 * @brief MainWindow::~MainWindow Деструктор класса
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::openMediaFile Считывает название файла после выбора его из диалогового окна
 */

void MainWindow::openMediaFile(){
    fileNames = QFileDialog::getOpenFileNames(this, "Open Song");

    foreach (QString argument, fileNames) {
            QUrl url(argument);
            if (url.isValid()) {
                playlist->addMedia(url);
        }

        QFileInfo file(argument);
        ui->listWidget->addItem(file.baseName());
        }
    total = playlist->mediaCount();
}

/**
 * @brief MainWindow::on_horizontalSlider_2_sliderMoved Устанавливает звук, получает позицию
 * @param position Позиция ползунка звука
 */

void MainWindow::on_horizontalSlider_2_sliderMoved(int position)
{
     player->setVolume(position);
     defaultVolume = position;

     if(ui->checkBox->isChecked()){
         ui->checkBox->setChecked(false);
     }

}


/**
 * @brief MainWindow::on_checkBox_toggled Выключает или включает звук
 * @param checked Переменная, которая передает значение true или false
 */

void MainWindow::on_checkBox_toggled(bool checked)
{
    if(checked==true)
        player->setVolume(0);
    else
        player->setVolume(defaultVolume);
}

/**
 * @brief MainWindow::on_actionOpen_File_triggered Открывает диалоговое окно для выборав файла, при нажатии на кнопку
 */

void MainWindow::on_actionOpen_File_triggered()
{
    openMediaFile();
}

/**
 * @brief MainWindow::positionChanged Изменение положения SongBar автоматически, для отображения прогресса
 * @param progress Переменная с текущим прогрессом записи
 */

void MainWindow::positionChanged(qint64 progress)
{
    ui->songBar->setValue(progress / 1000);
    show_time(progress/1000);
}

/**
 * @brief MainWindow::durationChanged Изменение положения SongBar вручную чтобы перемотать запись
 * @param duration Измененная позиция
 */

void MainWindow::durationChanged(qint64 duration)
{
    this->duration = duration/1000;
    ui->songBar->setMaximum(duration / 1000);
}

/**
 * @brief MainWindow::show_time Изменяет датчик времени
 * @param currentInfo Переменная с текущим временем
 */

void MainWindow::show_time(quint64 currentInfo){

    QString tStr;
    QTime currentTime(0,(currentInfo/60)%60, currentInfo%60);
    QTime totalTime(0,(duration/60)%60, duration%60);
    QString format = "mm:ss";
    tStr = currentTime.toString(format) + " / " + totalTime.toString(format);
    ui->label->setText(tStr);
}

/**
 * @brief MainWindow::on_songBar_sliderMoved  Изменяет позицию при нажатии на Songbar
 * @param position Переменная позиции координат, куда нажали на SongBar
 */

void MainWindow::on_songBar_sliderMoved(int position)
{
    player->setPosition(position*1000);
}

/**
 * @brief MainWindow::on_playbutton_clicked обработка нажатия на клавишу play
 */

void MainWindow::on_playbutton_clicked()
{
    if(playPauseCounter == 1){
        player->play();
        playPauseCounter = 2;
     }
}

/**
 * @brief MainWindow::on_pausebutton_clicked обработка нажатия на клавишу pause
 */

void MainWindow::on_pausebutton_clicked()
{
    player->pause();
    playPauseCounter =1;
}

/**
 * @brief MainWindow::on_pushbutton_clicked обработка нажатия на клавишу stop
 */

void MainWindow::on_pushButton_clicked()
{
     player->stop();
     playPauseCounter =1;
}
/**
 * @brief MainWindow::on_action_triggered обрабатывает нажатие на кнопку закрытия окна
 */

void MainWindow::on_action_triggered()
{
    close();
}

/**
 * @brief MainWindow::on_listWidget_activated обрабатывает добавление в плейлист
 */


void MainWindow::on_listWidget_activated()
{
    ui->songBar->setRange(0, player->duration() / 1000);
        playlist->setCurrentIndex(ui->listWidget->currentRow());
        playPauseCounter =2;
        player->play();
}
