/**
 * \file exceptions.h
 * \brief Exception defines
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

#ifndef UTILS_EXCEPTIONS_H
#define UTILS_EXCEPTIONS_H

#include <errno.h>
#include <utils/exception.h>

DEFINE_EXCEPTION(InvalidOptionsException, Utils::Exception);
DEFINE_EXCEPTION(InvalidFileDescriptorException, Utils::Exception);
DEFINE_EXCEPTION(InvalidHexStringException, Utils::Exception);
DEFINE_EXCEPTION(FileControlException, Utils::Exception);
DEFINE_EXCEPTION(IOControlException, Utils::Exception);
DEFINE_EXCEPTION(InvalidDirectoryException, Utils::Exception);
DEFINE_EXCEPTION(StatException, Utils::Exception);
DEFINE_EXCEPTION(NetworkException, Utils::Exception);
DEFINE_EXCEPTION(WSAStartupException, Utils::Exception);
DEFINE_EXCEPTION(HostResolveException, NetworkException);
DEFINE_EXCEPTION(SocketCreateException, NetworkException);
DEFINE_EXCEPTION(SocketConnectException, NetworkException);
DEFINE_EXCEPTION(SocketNotConnectedException, NetworkException);
DEFINE_EXCEPTION(SocketAlreadyBindedException, NetworkException);
DEFINE_EXCEPTION(SocketAlreadyConnectedException, NetworkException);
DEFINE_EXCEPTION(SocketSendException, NetworkException);
DEFINE_EXCEPTION(SocketReceiveException, NetworkException);
DEFINE_EXCEPTION(SocketDisconnectedException, NetworkException);
DEFINE_EXCEPTION(SocketNotBoundException, NetworkException);
DEFINE_EXCEPTION(SocketBindException, NetworkException);
DEFINE_EXCEPTION(SocketNotListenException, NetworkException);
DEFINE_EXCEPTION(SocketAcceptException, NetworkException);
DEFINE_EXCEPTION(SocketListenException, NetworkException);
DEFINE_EXCEPTION(SocketSelectException, NetworkException);
DEFINE_EXCEPTION(SocketSetOptionException, NetworkException);
DEFINE_EXCEPTION(HTTPException, Utils::Exception);
DEFINE_EXCEPTION(HTTPIncompleteRequest, HTTPException);
DEFINE_EXCEPTION(HTTPInvalidMethod, HTTPException);
DEFINE_EXCEPTION(HTTPUnsupportedMethod, HTTPException);
DEFINE_EXCEPTION(HTTPUnsupportedVersion, HTTPException);

#endif // UTILS_EXCEPTIONS_H
