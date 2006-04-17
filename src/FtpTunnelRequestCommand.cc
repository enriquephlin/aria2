/* <!-- copyright */
/*
 * aria2 - a simple utility for downloading files faster
 *
 * Copyright (C) 2006 Tatsuhiro Tsujikawa
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
/* copyright --> */
#include "FtpTunnelRequestCommand.h"
#include "FtpTunnelResponseCommand.h"
#include "HttpConnection.h"

FtpTunnelRequestCommand::FtpTunnelRequestCommand(int cuid, Request* req, DownloadEngine* e, const Socket* s):AbstractCommand(cuid, req, e, s) {
  setReadCheckSocket(NULL);
  setWriteCheckSocket(NULL);
}

FtpTunnelRequestCommand::~FtpTunnelRequestCommand() {}

bool FtpTunnelRequestCommand::executeInternal(Segment segment) {
  socket->setBlockingMode();
  HttpConnection httpConnection(cuid, socket, req, e->option);
  httpConnection.sendProxyRequest();

  FtpTunnelResponseCommand* command = new FtpTunnelResponseCommand(cuid, req, e, socket);
  e->commands.push(command);
  return true;
}
