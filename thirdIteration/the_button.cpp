//
// Created by twak on 11/11/2019.
//

#include "the_button.h"
#include <QDebug>
#include <QImageReader>

void TheButton::init(TheButtonInfo* i) {
    setIcon( *(i->icon) );
    info =  i;
}


void TheButton::clicked() {
    emit jumpTo(info);
}

void LoadButton::clicked(){
    QString f = QFileDialog::getOpenFileName(this,
          tr("Load Video"), "../", tr("Video Files (*.mov *.MOV *.mp4 *.wmv)"));
    qDebug() << f;
    if(f.length()==0){
        qDebug() << "No file choosed";
        return;
    }
    QString thumb = f.left(f.length() - 4) +".png";
    if (QFile(thumb).exists()) { // if a png thumbnail exists
        QImageReader *imageReader = new QImageReader(thumb);
            QImage sprite = imageReader->read(); // read the thumbnail
            if (!sprite.isNull()) {
                QIcon* ico = new QIcon(QPixmap::fromImage(sprite)); // voodoo to create an icon for the button
                QUrl* url = new QUrl(QUrl::fromLocalFile( f )); // convert the file location to a generic url
                this->info = new TheButtonInfo( url , ico  );
            }
            else{
                qDebug() << "warning: skipping video because I couldn't process thumbnail " << thumb << endl;
                return;
            }
    }
    emit jumpTo(info);

}
