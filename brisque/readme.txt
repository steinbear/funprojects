BRISQUE C++ Software release.

========================================================================

-----------COPYRIGHT NOTICE STARTS WITH THIS LINE------------
Copyright (c) 2011 The University of Texas at Austin
All rights reserved.

Permission is hereby granted, without written agreement and without license or royalty fees, to use, copy, 
modify, and distribute this code (the source files) and its documentation for
any purpose, provided that the copyright notice in its entirety appear in all copies of this code, and the 
original source of this code, Laboratory for Image and Video Engineering (LIVE, http://live.ece.utexas.edu)
and Center for Perceptual Systems (CPS, http://www.cps.utexas.edu) at the University of Texas at Austin (UT Austin, 
http://www.utexas.edu), is acknowledged in any publication that reports research using this code. The research
is to be cited in the bibliography as:

1) A. Mittal, A. K. Moorthy and A. C. Bovik, "No Reference Image Quality Assessment in the Spatial Domain"
IEEE Transactions on Image Processing, Volume 21, Issue 12, 2012.
2) http://live.ece.utexas.edu/research/quality/BRISQUE_C++release.zip

IN NO EVENT SHALL THE UNIVERSITY OF TEXAS AT AUSTIN BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, 
OR CONSEQUENTIAL DAMAGES ARISING OUT OF THE USE OF THIS DATABASE AND ITS DOCUMENTATION, EVEN IF THE UNIVERSITY OF TEXAS
AT AUSTIN HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

THE UNIVERSITY OF TEXAS AT AUSTIN SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE DATABASE PROVIDED HEREUNDER IS ON AN "AS IS" BASIS,
AND THE UNIVERSITY OF TEXAS AT AUSTIN HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

-----------COPYRIGHT NOTICE ENDS WITH THIS LINE------------%

Author  : Anish Mittal 
Version : 1.0

The authors are with the Laboratory for Image and Video Engineering
(LIVE), Department of Electrical and Computer Engineering, The
University of Texas at Austin, Austin, TX.

Kindly report any suggestions or corrections to mittal.anish@gmail.com

========================================================================

This is a demonstration of the Blind/Referenceless Image Spatial Quality Evaluator (BRISQUE) index.
The algorithm is described in:

A. Mittal, A. K. Moorthy and A. C. Bovik, "No Reference Image Quality Assessment in the Spatial Domain"
IEEE Transactions on Image Processing, Volume 21, Issue 12, 2012.

You can change this program as you like and use it anywhere, but please
refer to its original source (cite our paper and our web page at
http://live.ece.utexas.edu/research/quality/BRISQUE_C++release.zip).

========================================================================

Input : A test image name

Output: A quality score of the image. The score typically has a value
           between 0 and 100 (0 represents the best quality, 100 the worst).
  
Usage:

./brisquequality -im "imagename" 

The code also allows you to retrain the model. It can be acheived by setting -t flag to 1.
We have provided the code to retrain the model using LIVE database. However, after suitable changes to the code, any image quality database with images and corresponding human judgments can be used for training.

Dependencies: 

Binaries: svm-predict, svm-scale (from LibSVM)
svm-train (in case of retraining). 
Provided with release (libsvm folder)

The above binaries are provided for linux. However, we are including the source files as well in the folder. User can generate the binaries depending on their environment.

Packages: cmake, opencv

This link is pretty helpful to install opencv using cmake: http://docs.opencv.org/doc/tutorials/introduction/linux_gcc_cmake/linux_gcc_cmake.html
CMake makes it easy to port code across LINUX and windows. More information about cmake can be obtained at:http://www.cmake.org/cmake/resources/software.html

Additional files provided with release:

Binaries: brisquequality 
This binary is provided for LINUX distribution. However, the code can be recompiled on a windows environment to generate a windows executable.

C++ Files:  main.cpp trainModel.cpp  computescore.cpp brisque.cpp (provided with release)
H Files: brisque.h
Data Files: range_all, model_all (provided with release)

Test Image Files: testimage1.bmp, testimage2.bmp img3.jpg ( images folder)

If you need to retrain the model, please download the LIVE Image Quality Database from http://live.ece.utexas.edu/research/quality/subjective.htm.
We are providing the auxiliary data files associated with live database in text format in livedbfiles folder.


Note: The code has been written to work on LINUX OS. However, with the suggested changes, it can be changed to work with Windows environment as well.
========================================================================

Note on training: 
This release version of BRISQUE was trained on the entire LIVE database.


This program uses LibSVM binaries.
Below is the requried copyright notice for the binaries distributed with this release.

====================================================================
LibSVM tools: svm-predict, svm-scale, svm-predict (binaries)
--------------------------------------------------------------------

Copyright (c) 2000-2009 Chih-Chung Chang and Chih-Jen Lin
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

1. Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.

3. Neither name of copyright holders nor the names of its contributors
may be used to endorse or promote products derived from this software
without specific prior written permission.


THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
====================================================================
