//===========================================
//  Lumina-desktop source code
//  Copyright (c) 2018, Ken Moore
//  Available under the 3-clause BSD license
//  See the LICENSE file for full details
//===========================================
#include <global-objects.h>
#include "QMLImageProvider.h"

QMLImageProvider::QMLImageProvider() : QQuickImageProvider(QQmlImageProviderBase::Image, 0){

}

QMLImageProvider::~QMLImageProvider(){

}

/*QMLImageProvider* QMLImageProvider::instance(){
  static QMLImageProvider *_prov = 0;
  if(_prov==0){ _prov = new QMLImageProvider(); }
  return _prov;
}*/

QImage QMLImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize){
  NativeWindowObject *win = Lumina::NWS->findWindow( id.section(":",1,1).toInt(), false);
  qDebug() << "Request Image:" << id << win << requestedSize;
  QImage img(requestedSize,QImage::Format_RGB32);
  if(win==0){ img.fill("black"); } //invalid window ID (should never happen)
  else if(id.startsWith("image:")){ img = Lumina::NWS->GetWindowImage(win); }
  //else if(id.startsWith("icon:")){ img = Lumina::NWS->GetWindowIcon(win); }
  qDebug() << "Got Window Image:" << img.size();
  if(img.size().isNull()){
    if(requestedSize.isValid()){ img = QImage(requestedSize,QImage::Format_RGB32); }
    else{ img = QImage(QSize(64,64), QImage::Format_RGB32); }
    img.fill("black");
  }
  qDebug() << "Final Window Image:" << img.size();
  if(size!=0){
    size->setHeight(img.height());
    size->setWidth( img.width() );
  }
  if(requestedSize.isValid() && !requestedSize.isNull() && img.size()!=requestedSize){
    img = img.scaled(requestedSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
  }
  return img;
}
