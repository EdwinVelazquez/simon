/*
 *   Copyright (C) 2012 Yash Shah <mail@yashshah.com>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License version 2,
 *   or (at your option) any later version, as published by the Free
 *   Software Foundation
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef FACEANALYZER_H
#define FACEANALYZER_H
#include "simonvision_export.h"
#include "imageanalyzer.h"

class SIMONVISION_EXPORT FaceAnalyzer : public ImageAnalyzer
{
  Q_OBJECT

public:

  FaceAnalyzer();
  virtual ~FaceAnalyzer();
  void analyze(const IplImage* currentImage);


signals:
  void facePresenceChanged(bool hasFaceNew);

private:
  int      initFaceDetection(const QString& haarCascadePath);
  void     closeFaceDetection();
  void isChanged(bool hasFace);
  
  IplImage  * liveVideoFrameCopy;
  
  // Cascade for detecting face
  CvHaarClassifierCascade * cascade;
  
  // Memory that will needed to perform detection
  CvMemStorage * memoryStorage;
};

#endif // FACEANALYZER_H
