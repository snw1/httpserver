/**
 * \file filetype.h
 * \brief File type
 * \author Andrew Sheetov <andrew.sheetov@gmail.com>
 * \date 2014
 * \version 0.0
 * \copyright GPL <http://www.gnu.org/licenses/gpl.txt>
 *
 * This file is part of HTTPServer.
 * HTTPServer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HTTPServer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HTTPServer. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef UTILS_FILETYPE_H
#define UTILS_FILETYPE_H

namespace Utils
{

namespace FileSystem
{

/**
 * \enum FileType
 * \brief File type
 */
enum FileType
{
    FileTypeBinary = 0,
    FileTypeImageBMP = 1,
    FileTypeImageJPEG = 2,
    FileTypeImagePNG = 3,
    FileTypeImageGIF = 4,
    FileTypeTextTXT = 5,
    FileTypeTextPDF = 6,
    FileTypeTextHTML = 7,
    FileTypeAudioMP3 = 8,
    FileTypeVideoMP4 = 9
};

}

}

#endif // UTILS_FILETYPE_H
